/*
 * array_queue.c
 *
 *  Created on: Nov 13, 2016
 *      Author: adan
 */

#include "array_queue.h"
//
//初始化array queue
void aq_init(struct aq_info* paq)
{ paq->front_sig = 0;
  paq->rear_sig = 0;
  paq->aq_cur_size = 0;
  pthread_mutex_init(&paq->tmp_mutex,NULL);//初始化队列锁
  //初始化队列标志
  paq->aq_turn_num = aq_buf_max - 1;
  paq->aq_full = -10000;
  paq->aq_empty = -10001;
  paq->aq_push_ok = -10002;
  return;
}
//
//压入数据push
int aq_push(struct aq_info* paq, element_type* pdata, int N)
{
  int tmp;
  int D_val;
  pthread_mutex_lock(&paq->tmp_mutex);
  if(paq->aq_cur_size >= aq_buf_max){//判断队列是否满栈
	if(paq->aq_cur_size > aq_buf_max){
	  printf("array queue is messing,now fix it...aq_cur_size > aq_buf_max\n");
	  paq->aq_cur_size = aq_buf_max;//防止队列损坏
	}
    pthread_mutex_unlock(&paq->tmp_mutex);
    return paq->aq_full;//返回队列已满
  }
  else{//队列未满--判断是否能装下N 个元素
	if(paq->aq_cur_size + N > aq_buf_max){//队列+N 后溢出
	  pthread_mutex_unlock(&paq->tmp_mutex);
	  return paq->aq_full;//同样返回队列已满
	}
  }
  //队列未满且能装下N 个元素
  D_val = paq->rear_sig + N;//队列+N 个元素后的游标是否溢出??
  if(D_val >= aq_buf_max)
    {//调头
      D_val = D_val - aq_buf_max;//求得溢出容量差
      for(tmp = 0;paq->rear_sig <= paq->aq_turn_num;paq->rear_sig++)//未溢出部分继续加
      	{
      	  paq->aq_buf[paq->rear_sig] = *(pdata + tmp);
      	  tmp++;
      	}
      for(paq->rear_sig = 0;paq->rear_sig < D_val;paq->rear_sig++)//溢出移到队首
      	{
      	  paq->aq_buf[paq->rear_sig] = *(pdata + tmp);
      	  tmp++;
      	}
      paq->aq_cur_size = paq->aq_cur_size + N;//总数+N
    }
  else
    {//不用调头
      for(tmp = 0;paq->rear_sig < D_val;paq->rear_sig++)//直接插入
	{
	  paq->aq_buf[paq->rear_sig] = *(pdata + tmp);
	  tmp++;
	}
      paq->aq_cur_size = paq->aq_cur_size + N;;//总数+N
    }
  //执行插入操作--不能离开缓冲区，因为当你push 内存操作时，内存还没写入，但是就已经pop 出的时候
  //就会发生错误，所以这点性能还是不能省
  pthread_mutex_unlock(&paq->tmp_mutex);
  return paq->aq_push_ok;
}
//
//弹出数据，尽量弹出全部，但是最多弹出4096，返回弹出的数量
//需要手动释放锁--详情请看头文件
//还要传入一个缓冲区
int aq_pop(struct aq_info* paq, element_type* pdata)
{ int tmp;
  int D_val;
  int pop_count;
  pthread_mutex_lock(&paq->tmp_mutex);
  if(paq->aq_cur_size <= 0){
    if(paq->aq_cur_size == 0)
	  printf("array queue is empty\n");
    else{
      printf("array queue is messing,now fix it...aq_cur_size < 0\n");
      paq->aq_cur_size = 0;//防止队列损坏
    }
    pthread_mutex_unlock(&paq->tmp_mutex);
    return paq->aq_empty;
  }
  pop_count = paq->aq_cur_size;	//获取当前队列容量
  if(pop_count > AP_buf_max)	//队列当前任务的数量大于缓冲区大小时
    pop_count = AP_buf_max;
  //POP 入之后的游标是否溢出
  D_val = paq->front_sig + pop_count;
  if(D_val >= aq_buf_max)
  {//调头
    D_val = D_val - aq_buf_max;	//求得溢出容量差
    for(tmp = 0;paq->front_sig <= paq->aq_turn_num;paq->front_sig++)//未溢出部分继续加
      {
    	pdata[tmp] = paq->aq_buf[paq->front_sig];
    	tmp++;
      }
    for(paq->front_sig = 0;paq->front_sig < D_val;paq->front_sig++) //溢出移到队首
      {
    	pdata[tmp] = paq->aq_buf[paq->front_sig];
    	tmp++;
      }
    paq->aq_cur_size = paq->aq_cur_size - pop_count;	//总数-pop_count
  }
  else
  {//不用调头
    for(tmp = 0;paq->front_sig < D_val;paq->front_sig++)//直接弹出
      {
    	pdata[tmp] = paq->aq_buf[paq->front_sig];
    	tmp++;
      }
    paq->aq_cur_size = paq->aq_cur_size - pop_count;	//总数-pop_count
  }
  return pop_count;
}
//
//获取array queue 的cur_size
int aq_cur_size(struct aq_info* paq)
{ int tmp;
  pthread_mutex_lock(&paq->tmp_mutex);
  tmp = paq->aq_cur_size;
  pthread_mutex_unlock(&paq->tmp_mutex);
  return tmp;
}
//
//判断aq 是否为空，是空返回1,非空返回0
int aq_is_empty(struct aq_info* paq)
{ int tmp;
  pthread_mutex_lock(&paq->tmp_mutex);
  if(paq->aq_cur_size == 0)
    tmp = 1;
  else
    tmp = 0;
  pthread_mutex_unlock(&paq->tmp_mutex);
  return tmp;
}
//
//判断aq 是否队满，是空返回1,非空返回0
int aq_is_full(struct aq_info* paq)
{ int tmp;
  pthread_mutex_lock(&paq->tmp_mutex);
  if(paq->aq_cur_size == aq_buf_max)
    tmp = 1;
  else
    tmp = 0;
  pthread_mutex_unlock(&paq->tmp_mutex);
  return tmp;
}
