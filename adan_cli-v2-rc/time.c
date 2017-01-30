/*
 * ptime.c
 *
 *  Created on: Oct 13, 2016
 *      Author: adan
 */

#include <time.h>
#include <stdio.h>
#include <errno.h>

//开始和结束时间记录容器
struct tm loc_t_start,loc_t_end;

//输入时间变量struct tm* 打印时间
//
void echo_time(struct tm* loc_t)
{ printf("year-month-day: %d-%d-%d | hour:minute:second: %d:%d:%d\n",loc_t->tm_year,loc_t->tm_mon,loc_t->tm_mday,loc_t->tm_hour,loc_t->tm_min,loc_t->tm_sec);
  return; }
//获取并显示当前获取的时间-- 参数start_end=1,获取，显示并记录开始时间;
//                          start_end=0,获取，显示开始和结束时间
//
void get_time_echo(int start_end)
{
  time_t time_c;		//时间容器
  time_c = time(NULL);		//执行获取时间
  struct tm* tmp;
  tmp = localtime(&time_c);	//转换为本地时间格式
  if(tmp == NULL)
  { printf("get machine's time fail, errno: %d\n",errno);
    return ; }

  if(start_end)
  { loc_t_start = *tmp;
    echo_time(tmp); }
  else
  { loc_t_end = *tmp;
    echo_time(&loc_t_start);
    echo_time(tmp); }

  return ;
}

