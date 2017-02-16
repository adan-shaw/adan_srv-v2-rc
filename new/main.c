/*
 * main.c
 *
 *  Created on: Nov 3, 2016
 *      Author: adan
 */

#include "static_val.h"
#include <stdio.h>
#include <stdlib.h>

//服务器主函数
int main(int argc,int argv[])
{ printf("******************************************\n");
  printf("welcome you tu use our server\n");
  printf("assrvxx server is running now\n");
  printf("******************************************\n");
  //动态创建全局变量
  struct static_val* s_val;
  s_val = malloc(sizeof(struct static_val));
  if(s_val == NULL) exit(EXIT_FAILURE);
  //
  //初始化全局变量
  init_s_val(s_val);
  //初始化主函数pid_li
  init_main(s_val);
  //显示命令列表
  echo_comm();
  //
  int tmp_loop;
  for(;;){//输入控制loop
    printf("please input a command, need help order number-0\n"); scanf("%d",&tmp_loop);
    switch(tmp_loop){
    case 1:
	  if(s_val->srv_sig != 0){  	//如果服务已经开启/拒绝二次启动
	    printf("program has start!!do not order 1 again\n");break;
	  }
	  if(start_srv(s_val) == -1)	//开始server 服务
	    printf("start services fail\n");
	  s_val->srv_sig = 1;
	  break;

	case 2:
	  if(s_val->srv_sig == 0){		//如果服务没有启动/直接退出
	    exit(0);
	  }
	  //全部服务杀停--如果这里现实内存越界则有指针回收出错
	  quit_main(s_val);
	  exit(0);		//退出程序

	case 3:
	  printf("hello stranger, i am adan shaw, thx for you use us software\n");
	  printf("what if you have any questions or good idea, please contact us\n");
	  printf("our email:adan_shaw@qq.com\n");
	  break;

	case 4: show_srv_info(s_val); break;	//显示服务器统计信息

	case 0: echo_comm(); break;				//显示命令列表

	default: printf("！！！！！input a unknow number！！！！！\n"); break;
    }
    printf("\n");
  }
  //控制loop 内存溢出
  printf("******************************************\n");
  printf("oh my god,main()-pthread out of memory\n");
  printf("the server has stop,input any key to quit\n");
  printf("******************************************\n");
  scanf("%d",&tmp_loop);
  exit(0);
}





