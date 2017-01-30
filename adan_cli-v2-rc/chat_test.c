/*
 * chat_test.c
 *
 *  Created on: Jan 29, 2017
 *      Author: adan
 */

#include "static_val.h"
#include "comm_list.h"
void _register(void)
{ printf("please input a <int> type of number as your id\n");
  int id;
  scanf("%d",&id);
  printf("please input a <string> type of char string as your password(16)\n");
  struct data_frame buf;
  buf.comm = x3l_register;
  scanf("%s",&buf.upw);
  printf("%s",buf.upw);
  buf.u_backup = get_lencode();
  if(send_srv(&buf) != -1)//发送服务器一次数据
  {
    if(buf.u_backup == get_lencode())
  	  open_data(&buf);
    else
  	  printf("unknow data,but this data may not from our software,be careful !!\n");
    if(buf.comm == x3l_register)
    	printf("register ok\n");
    else if(buf.comm == x3l_error)
        printf("id or password format error\n");
    else
    	printf("server or client software error\n");

  }
  return ;
}

int _login(void)
{ printf("please input a <int> type of number as your id\n");
  int id;
  scanf("%d",&id);
  printf("please input a <string> type of char string as your password(16)\n");
  struct data_frame buf;
  buf.comm = x3l_login;
  scanf("%s",&buf.upw);
  buf.u_backup = get_lencode();
  if(send_srv(&buf) != -1)//发送服务器一次数据
  {
    if(buf.u_backup == get_lencode())
  	  open_data(&buf);
    else
  	  printf("unknow data,but this data may not from our software,be careful !!\n");
    if(buf.comm == x3l_login)
    	{printf("login ok\n");  return id;}
    else if(buf.comm == x3l_error)
        printf("id or password format error\n");
    else
    	printf("server or client software error\n");

  }
  return -1;
}

//id = 0,则不需要发送服务器告知退出，维护在线列表--在线列表需要守护进程扫描，但是现阶段不做
void chat_exit(int id)
{ if(id > 0){
  struct data_frame buf;
  buf.comm = x3l_exit;
  buf.u_backup = get_lencode();
  if(send_srv(&buf) != -1)//发送服务器一次数据
  {
    if(buf.u_backup == get_lencode())
  	  open_data(&buf);
    else
  	  printf("unknow data,but this data may not from our software,be careful !!\n");
    if(buf.comm == x3l_exit)
    	printf("exit ok\n");
    else if(buf.comm == x3l_error)
        printf("exit fail\n");
    else
    	printf("server or client software error\n");

  }
}

  return ;
}

void _getid(void)
{
	//获取一堆ID


  return ;
}

void _lockid_chat(void)
{   //获取对方的IP,然后调用chating
	return ;
}

int init_chat()
{
	return 0;
}














int send_srv(void* buf)
{	int sock_tmp;
	sock_tmp = inet_connect(SRV_IP,SRV_PORT);//由于每次操作都要链接一次
	if(sock_tmp < 0)
	  {printf("connect server fail\n");return -1;}
	//加密数据
    encode_pickup(buf);
    //执行发送
    if(send(sock_tmp, buf, sizeof(struct data_frame), 0) < 0)
    {
      close(sock_tmp);
      printf("\nsend() an data to server fail!\n");
      return -1;
    }
    //接受数据
    if(recv(sock_tmp, buf, sizeof(struct data_frame), 0) < 0)
    {
      close(sock_tmp);
      printf("\nrecv() an data from server fail!\n");
      return -1;
    }
    //解密数据
    encode_open(buf);
    //客户端解析数据--这个操作没有什么特别，只是显示正确与否
    close(sock_tmp);
	return 0;
}
