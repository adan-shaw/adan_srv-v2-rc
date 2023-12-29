/*
 * array_stack.h
 *
 *  Created on: Nov 13, 2016
 *      Author: adan
 */

#define element_type int//int： 4个字节(固定)
//#define element_type void*//*(即指针变量): 32-4/64-8  个字节
//#define as_pbuf_max 4096*sizeof(element_type)
#define as_buf_max 4096
#define as_pbuf_max 128
//*********************
//运行变量
//*********************
struct as_info{
  element_type as_buf[as_buf_max];
  element_type as_pbuf[as_pbuf_max];
  int as_cur_size;
  //*********************
  //运行常量
  //*********************
  int as_buf_empty;
  int as_buf_full;
  int as_full;
  int as_empty;
  int as_push_ok;
};

//附：栈中没有负值

