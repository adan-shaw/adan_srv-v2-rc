/*
 * array_queue.h
 *
 *  Created on: Nov 13, 2016
 *      Author: adan
 */

//*********************
//运行宏
//*********************
#define element_type int//int： 4个字节(固定)
//#define element_type void*//*(即指针变量): 32-4/64-8  个字节
//#define aq_pbuf_max 4096*sizeof(element_type)
#define aq_buf_max 40960
#define AS_buf_max 4096
#include <pthread.h>

//*********************
//运行变量
//*********************
struct aq_info{
  element_type aq_buf[aq_buf_max];
  int front_sig;//2个字节(固定)
  int rear_sig;
  int aq_cur_size;
  pthread_mutex_t tmp_mutex;		//自带锁--唯一
  element_type AS_push[AS_buf_max];	//压入临时缓冲区-功能：载体--唯一
					//压入只有epoll_listen 线程
  element_type AS_pop[AS_buf_max];	//pop出临时缓冲区-功能：载体--唯一
					//弹出却是多个IO 线程共享
  //*********************
  //运行常量
  //*********************
  int aq_turn_num;
  short int aq_full;
  short int aq_empty;
  short int aq_push_ok;
};


