/*
 * static_val.h
 *
 *  Created on: Nov 3, 2016
 *      Author: adan
 */

#include <pthread.h>
#include "comm_list.h"

#include "hiredis-master/hiredis.h"
#include "hiredis-master/net.h"

#define pool_max 4		//最多4条io 线程
//全局变量
struct static_val{
  unsigned int exit_sig;	//退出标志
	       int test_count;	//互交次数总累加
	       int err_count;	//互交错误总累加
	 short int srv_sig;	    //服务器状态标志--启动/停止
  //监听模块
	       int sfd_li;		//监听socket
  unsigned int pid_li;		//监听线程PID
  unsigned int err_li;		//监听线程错误
  //epoll 模块
	       int epoll_fd;
	       int cur_fds;		//epoll 中的fd 计数
  //recv任务队列
  void* pm_recv;
  //
  //IO 线程池模块
  unsigned int pid_io[pool_max];		//线程的PID
  unsigned int test_io[pool_max];		//线程的服务次数累加
  unsigned int err_io[pool_max];		//线程的错误次数累加
  pthread_cond_t cond_io[pool_max];	    //线程的同步条件变量
  pthread_mutex_t mutex_io[pool_max];	//线程的同步锁
     short int sig_io[pool_max];		//线程的状态表示-正在使用=+1 | 闲=0(减少冲突)
  //创建线程组时用到的临时变量
  int pid_tmp;
  pthread_cond_t tmp_cond;
  pthread_mutex_t tmp_mutex;
  //********************************************************************
  //redis 模块
  //********************************************************************
  redisContext *c;
  pthread_mutex_t redis_mutex;
};
//
//数据帧
#define BUF_SIZE 400
struct data_frame{
  unsigned int encode;		//4
  unsigned int comm;		//4
  unsigned int uid;		//4
  char uname[16];		//16
  char upw[16];			//16
  unsigned int ip;		//4
  unsigned int port;		//4
  unsigned int age;		//4
  unsigned int sex;		//4
  unsigned int u_backup;	//4
  char s_backup[32];		//32
  char buf[BUF_SIZE];		//BUF_SIZE
};
//
//#define SRV_IP "192.168.56.1"
#define SRV_IP "127.0.0.1"
#define SRV_PORT 9213
