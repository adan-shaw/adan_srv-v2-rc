/*
 * main_func.c
 *
 *  Created on: Nov 3, 2016
 *      Author: adan
 */

#include <errno.h>
#include "main_func.h"
#include "array_queue.h"
//
//服务器--初始化全局变量
void init_s_val(struct static_val* s_val)
{ //初始化全局变量
  s_val->exit_sig = 0;
  s_val->test_count = 0;
  s_val->err_count = 0;
  s_val->srv_sig = 0;
  //初始化listen 线程计数
  s_val->sfd_li = 0;
  s_val->pid_li = 0;
  s_val->err_li = 0;
  //初始化precv 线程池模块
  int tmp;
  for(tmp = 0;tmp < pool_max;tmp++){
    s_val->pid_io[tmp] = 0;
    s_val->test_io[tmp] = 0;
    s_val->err_io[tmp] = 0;
    s_val->sig_io[tmp] = 0;
    pthread_cond_init(&s_val->cond_io[tmp],NULL);	//io 线程事件锁
    pthread_mutex_init(&s_val->mutex_io[tmp],NULL);
  }
  s_val->pid_tmp = 0;
  pthread_cond_init(&s_val->tmp_cond,NULL);			//tmp 同步模块
  pthread_mutex_init(&s_val->tmp_mutex,NULL);

  pthread_mutex_init(&s_val->redis_mutex,NULL); 	//redis 同步模块
  return;//直接返回, 一般不会出错
}
//
//服务器--程序初始化
int init_main(struct static_val* s_val)
{ //更改进程拥有的fd 数量极限--jdk 里面不能使用--调用失败也无相干, 反正一般机器也不能跑上fd 极限
  struct rlimit	rlt;
  rlt.rlim_max = rlt.rlim_cur = MAXEPOLL;
  if(setrlimit(RLIMIT_NOFILE, &rlt) == -1){
    printf("setrlimit fail, errno: %d\n", errno);
    /*return -1;//这个函数不重要, 失败不用返回-1*/
  }
  //
  //创建IO任务队列
  s_val->pm_recv = malloc(sizeof(struct aq_info));
  if(s_val->pm_recv == NULL) return -1;
  aq_init(s_val->pm_recv);//初始化IO任务队列

  printf("the server init_main() success\n");
  return 0;
}
//
//服务器--命令列表
void echo_comm(void)
{ printf("command list:\n");
  printf("No.1: start services\n");
  printf("No.2: stop services and quit\n");
  printf("No.3: about us\n");
  printf("No.4: show the server info\n");
  printf("No.0: show command list\n");
  return;
}
//
//服务器--开始服务
int start_srv(struct static_val* s_val)
{ //初始化redis 模块--redis 不支持异机启动->不像mysql, 所以本机启动, 默认端口6379
  s_val->c = redisConnect("127.0.0.1", 6379);
  if (s_val->c != NULL && s_val->c->err){
    printf("Error: %sn", s_val->c->errstr); // 显示错误信息
	return -1;
  }
  //测试链接是否正常
  redisReply *reply;
  reply = redisCommand(s_val->c, "SELECT 18");
  //如果初始化redis 成功并且链接正常, 则开始初始化工作线程
  if(reply != NULL){
	//开始listen pthread
	if(start_plisten(s_val) == -1){
	  redisFree(s_val->c);//启动监听线程失败, 回收redis db 资源
	  return -1;
	}
  	//开始 recv pthread
  	if(start_precv(s_val) == -1){
  	  redisFree(s_val->c);//启动监听线程失败, 回收redis db 资源
  	  return -1;
  	}
  }
  else{
    freeReplyObject(reply);
    return -1;
  }
  freeReplyObject(reply);//无论如何释放测试链接
  return 0;//启动服务成功
}
//
//服务器--退出函数
void quit_main(struct static_val* s_val)
{ s_val->exit_sig++;	//拉高退出标志,明确退出决心,同时命令各个线程自己回收部分模块
  sleep(2);				//等待所有线程回收资源完毕
  printf("all pthread has quit,go on clean program\n");
  //
  //开始回收全局资源
  redisFree(s_val->c);  //回收redis
  free(s_val->pm_recv);	//回收任务队列
  free(s_val);			//删除全局变量实体
  printf("*********\n");
  printf("～good bye~\n");
  printf("*********\n");
  return;
}
//
//服务器--服务器信息统计显示
void show_srv_info(struct static_val* s_val)
{ printf("*************************************************\n");
  //显示全局统计
  printf("the server ip:%s, port: %d \naccept client times count: %d, error client times count: %d\n",SRV_IP,SRV_PORT,s_val->test_count,s_val->err_count);
  //显示listen 模块信息
  if(s_val->pid_li != 0)
    printf("listen pthread is still working--");
  else
    printf("listen pthread is down--");
  printf("error count is: %d\n",s_val->err_li);
  //
  //IO 线程池 模块信息
  int tmp;
  for(tmp = 0;tmp < pool_max;tmp++)
    if(s_val->pid_io[tmp] != 0)
     { printf("io pthread-%d is still working-*-",tmp);
       printf("io pthread-%d test count: %d--|--",tmp,s_val->test_io[tmp]);
       printf("io pthread-%d error count is: %d\n",tmp,s_val->err_io[tmp]); }
    else
     { printf("io pthread-%d is down|||",tmp);
       printf("io pthread-%d test count: %d--|--",tmp,s_val->test_io[tmp]);
       printf("io pthread-%d error count is: %d\n",tmp,s_val->err_io[tmp]); }
  //
  printf("*************************************************\n");
  return;//成功返回
}

