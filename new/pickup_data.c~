/*
 * pickup_data.c
 *
 *  Created on: Nov 17, 2016
 *      Author: adan
 */

#include "static_val.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

//打包回发数据并执行回发
int pickup_data(struct static_val *s_val, int sock_tmp, struct data_frame* pdata_frame)
{ encode_pickup(pdata_frame);//加密数据
  //执行回发操作--这里MSG_DONTWAIT 可以提高性能，但是发送错误的话，回没有提示，服务器并不知道发送错误
  //收发操作同样需要控制异步，epoll 最多只能让recv 肯定异步，但是不能让send 也肯定异步
  //所以send 肯定需要MSG_DONTWAIT
  //回发不能完全保证无错误，因为回发过程是异步的，但又没有错误事件通知～～
  //回发的时候，socket 已经被踢出了epoll...要保证回发安全，直接用非异步发送
  int tmp;
  tmp = send(sock_tmp, pdata_frame, sizeof(struct data_frame), MSG_DONTWAIT);
  if(tmp < 0){
    printf("socket %d send an data to client fail, errno:%d\n",sock_tmp,errno);
    return -1;
  }
  if(tmp == 0){
    printf("socket %d send an data to client fail, client has closed, errno:%d\n",sock_tmp,errno);
    return -1;
  }

  //usleep(100);//0.1ms
  //usleep(1000);//1ms
  //usleep(10000);//10ms
  return 0;//正确返回
}

