/*
 * main_func.c
 *
 *  Created on: Nov 3, 2016
 *      Author: adan
 */

#include "static_val.h"

//
//客户端--全局变量初始化
void init_s_val(void* arg)
{ struct static_val* s_val = arg;
  s_val->test_count = 0;
  s_val->test_err = 0;
  return; }
//
//客户端--客户端退出函数
void quit_main(void* arg)
{ struct static_val* s_val = arg;
  free(s_val);
  printf("good bye\n");
  return; }
//
//客户端--客户端状态信息
void show_cli_status(void* arg)
{ struct static_val* s_val = arg;
  printf("test count: %d, test error: %d\n",s_val->test_count,s_val->test_err);
  return; }
//
//客户端--命令列表
void echo_comm(void)
{ printf("commmand list:\n");
  printf("No.1: test box\n");
  printf("No.2: stop client and quit\n");
  printf("No.3: about us\n");
  printf("No.4: show the client status\n");
  printf("No.5: chat online function test\n");
  printf("No.0: show command list\n");
  return; }
//
//客户端--测试盒子
void test_loop(void* arg)
{ struct static_val* s_val = arg;
  int Y, X;
  printf("this is a loop test,test interaction count X finish then wait for 1 second\n");
  printf("and then keeping test Y times till 'Y = 0'\n");
  printf("please input a test number X*6\n");
  scanf("%d",&X);
  printf("please input a test number Y\n");
  scanf("%d",&Y);

  int tmp;
  int tmp2;
  int test_count = 0;
  int sfd_tmp;
  //局部记录变量
  int tmp_err = 0,tmp_count = 0;
  //start time
  printf("start at: \n");
  get_time_echo(1);
  for(tmp = 0;tmp<Y;tmp++)
    { for(tmp2 = 0;tmp2<X;tmp2++)
	{ int db_all;
	  int uid = get_random();
	  uid = uid / 1000;
	  for(db_all = 0;db_all < 6;db_all++)//反正db 操作数据请求都是1-8,方便递归,1和8是清表，不用
	    { sfd_tmp = inet_connect(SRV_IP,SRV_PORT);//由于每次操作都要链接一次
	      if(sfd_tmp < 0)
		{ s_val->test_err++; tmp_err++; }
	      if(test_once(sfd_tmp,db_all,uid) == -1)//所以不能链接一次就遍历8次
		{ s_val->test_err++; tmp_err++; }
	    }
	  //错误累加 >20
	  if(tmp_err > 20)
	      break;
	  s_val->test_count+=6;
	}
      if(tmp_err > 20)
	{ tmp_count = tmp*X;
	  printf("test box > 20,client has stop test mession,test count: %d\n",tmp_count);
	  break;
	}
    }
  printf("test Y*X times finish\n");
  //finish time
  printf("finsh at: \n");
  get_time_echo(0);
  printf("client status count:\n");
  show_cli_status(s_val);
  echo_comm();
  return;
}
//清空所有服务器测试数据
//
void chat_test(void* arg)
{ struct static_val* s_val = arg;
  printf("welcome to chat test!!\nplease register two test account first and note down the id number!!\n");
  int tmp_loop;
  printf("now targer server ip:%s ,port:%d\n",SRV_IP,SRV_PORT);
  printf("please input a command, need help order number-0\n");
  int id = 0;
  if(init_chat() == 0)
  {
  for(;;)
	{
	chat_comm();
	scanf("%d",&tmp_loop);
	switch(tmp_loop)
	{
	case 1: _register();//_register盒子
	break;
	case 2: id = _login();//调用_login函数
			if(id == -1)
				id = 0;
	break;
	case 3:_getid();		//get a stranger id
	break;
	case 4: _lockid_chat();//lock her id and start chat with her
	break;
	case 5: chat_comm();//help
	break;
	case 0: chat_exit(id);//exit chat
	break;
	default: printf("input a unknow number\n"); break;
	}
	printf("\n");
	if(tmp_loop == 0)
		break;
	}
  }
  else
	  printf("init chat fail!!\n");
  return;
}
void chat_comm(void)
{ printf("chat commmand list:\n");
  printf("No.1: register\n");
  printf("No.2: login\n");
  printf("No.3: get a stranger id\n");
  printf("No.4: lock her id and start chat with her\n");
  printf("No.5: help\n");
  printf("No.0: exit chat\n");
  return; }
void chating_comm(void)
{ printf("chating commmand list:\n");
  printf("No.1: send message\n");
  printf("No.2: check your chat record\n");
  printf("No.3: unlock her and back to chat_test\n");
  printf("No.4: help\n");
  return; }
void chating_test(void* arg)
{ struct static_val* s_val = arg;
  printf("welcome to chat test!!\nplease register two test account first and note down the id number!!\n");
  int tmp_loop;
  printf("now targer server ip:%s ,port:%d\n",SRV_IP,SRV_PORT);
  printf("please input a command, need help order number-0\n");
  for(;;)
	{
	chating_comm();
	scanf("%d",&tmp_loop);
	switch(tmp_loop)
	{
	case 1: send_msg();//测试盒子
	break;
	case 2: chat_record();//调用退出函数
	break;
	case 3: unlockid_exit();
	break;
	case 4: chating_comm();//调用退出函数
	break;
	default: printf("input a unknow number\n"); break;
	}
	printf("\n");
	if(tmp_loop == 3)
		break;
	}

  return;
}
