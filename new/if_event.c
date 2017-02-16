/*
 * if_event.c
 *
 *  Created on: Oct 29, 2016
 *      Author: adan
 */

#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include "static_val.h"
#include "epoll_head.h"
#include "array_queue.h"
#include "array_stack.h"

#define EPOLL_RUN_TIMEOUT 1000//epoll timeout 1s
//
//判断epoll 中触发的fd事件类型, 是IO 任务则返回触发集合
void if_event(struct static_val *s_val,struct as_info *pas)
{ //继承IO 任务队列
  struct aq_info* pm_recv;pm_recv = s_val->pm_recv;
  //
  struct epoll_event ev_tmp;		//epoll 事件临时变量
  struct epoll_event evs[MAXEPOLL];	//30W 个epoll 感兴趣事件
  int wait_fds;						//!> epoll_wait 返回的,已发生事件的fd 计数
  //
  int sfd_acc;
  int tmp;
  //获取epoll 中被触发的fd,返回到evs 事件数组容器中
  wait_fds = epoll_wait(s_val->epoll_fd, evs, s_val->cur_fds, EPOLL_RUN_TIMEOUT);//阻塞方式:第四参数为-1
  if(wait_fds > 0){ //判断触发fd 数量是否 > 0
    for(tmp = 0;tmp < wait_fds;tmp++){ //用循环体-处理-所有被触发的fd
      //如果是listen fd 发生事件
      if(evs[tmp].data.fd == s_val->sfd_li && s_val->cur_fds < MAXEPOLL){ //!> 监听fd 被触发
    	//接受客户端
    	if((sfd_acc = accept(s_val->sfd_li, NULL, NULL)) == -1){
	      s_val->err_li++;
	      printf("listen pthread accept client error, errno: %d|||error count: %d\n", errno,s_val->err_li);
	      continue;
    	}
        //添加client 到epoll 中
	    if(add_epoll(s_val,sfd_acc) == 0){
	      //成功accept 客户端
	      ++s_val->cur_fds;	 //epoll 句柄计数+1
	      s_val->test_count++;//服务器次数+1
	      continue;
	    }
	    else{//添加client 到epoll失败, 错误次数+1
	     s_val->err_li++; printf("listen pthread add_epoll() fail, error count: %d",s_val->err_li);
	    }
      }
      else{//如果是client fd 事件触发-->有io 数据
        //直接从epoll 中移除client
	    if(epoll_ctl(s_val->epoll_fd, EPOLL_CTL_DEL, evs[tmp].data.fd, NULL) < 0 ){
	      s_val->err_li++;
	      printf("listen pthread sfd_acc epoll_ctl EPOLL_CTL_DEL error, errno: %d, error count: %d\n", errno,s_val->err_li);
	      continue;
	    }
	    --s_val->cur_fds; //维系 cur_fds的正确性
	    as_push(pas,evs[tmp].data.fd);//将client sfd压入栈
      }
    }
    //获取堆栈中的所有io 任务计数
    int as_size = as_cur_size(pas);	//int as_pos = as_size -1;//保持先进后出

    //整改队列--

    //直接将数据推出任务队列？

    //for(tmp = 0;tmp < as_size;tmp++)
      //pm_recv->AS_push[tmp] = pas->as_buf[tmp];//保持先进先出

    //执行批量压入队列
    if(aq_push(pm_recv, pas->as_buf, as_size) != pm_recv->aq_push_ok){
       s_val->err_li += as_size; printf("listen pthread aq_push in queue error, errno: %d\n", errno); printf("listen pthread error count: %d",s_val->err_li);
    }
    pas->as_cur_size = -1;//复原栈

  }//if epoll_wait end
  else{//epoll_wait timeout
    if(wait_fds == 0)
      return;
    //epoll_wait 异常错误
    printf("listen pthread epoll_wait fail, errno: %d\n", errno);
    s_val->exit_sig++;
    printf("listen pthread error count: %d",s_val->err_li);
  }
  return;
}
//
//添加进epoll
int add_epoll(struct static_val *s_val, int sfd_acc)
{ //设置重用本地地址和端口--SO_REUSEADDR 重用地址
  int nREUSEADDR = 1;
  if(setsockopt(sfd_acc,SOL_SOCKET,SO_REUSEADDR,(const char*)&nREUSEADDR,sizeof(int)) == -1)
    { printf("setsockopt = nREUSEADDR = 1 fail, errno: %d\n",errno);return -1; }
  //
  //设置:如果服务器主动关闭剔除客户端,客户端强制关闭
  struct linger m_sLinger;
  m_sLinger.l_onoff = 1; // (在closesocket()调用,但是还有数据没发送完毕的时候容许逗留)
  m_sLinger.l_linger = 0; // (容许逗留的时间为0秒)
  if(setsockopt(sfd_acc,SOL_SOCKET,SO_LINGER,(const char*)&m_sLinger,sizeof(struct linger)) == -1)
    { printf("setsockopt = l_linger = 0 fail, errno: %d\n",errno);return -1; }
  //
  //通用ctl 设置 socket nonblocking
  if(fcntl(sfd_acc, F_SETFL, fcntl(s_val->epoll_fd, F_GETFD, 0) &~ O_NONBLOCK) == -1)
    { printf("listen pthread sfd_acc fcntl() error, errno: %d\n",errno);return -1; }
  //
  //加入epoll 中
  struct epoll_event ev_tmp;
  ev_tmp.events = EPOLLIN | EPOLLET;
  ev_tmp.data.fd = sfd_acc;
  if(epoll_ctl(s_val->epoll_fd, EPOLL_CTL_ADD, sfd_acc, &ev_tmp) < 0 )
    { printf("listen pthread sfd_acc epoll_ctl() EPOLL_CTL_ADD error, errno: %d\n", errno);return -1; }
  return 0;
}
