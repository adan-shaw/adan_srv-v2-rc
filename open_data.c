/*
 * open_data.c
 *
 *  Created on: Nov 17, 2016
 *      Author: adan
 */

#include "static_val.h"
#include <errno.h>
#include "epoll_head.h"
#include <string.h>
//
//解析数据帧
/*
redis db 表
online 表：18
int,int

user 表：22
int,string
/* -- 废弃！！不用格式化字符串做命令源==缓冲区敏感
//redis db 如何检测错误返回？？这是个问题～～这里就是需要检查错误返回
//
//操作online 表--成功返回0,错误返回-1
redisReply* do_Tonline(struct static_val *s_val,char* comm)
{   redisReply *reply;
	pthread_mutex_lock(&s_val->tmp_mutex);
	reply = redisCommand(s_val->c, "SELECT 0");
	freeReplyObject(reply);
	reply = redisCommand(s_val->c, comm);
	pthread_mutex_unlock(&s_val->tmp_mutex);
	return reply;
}
//
//操作user 表--成功返回0,错误返回-1
redisReply* do_Tuser(struct static_val *s_val,char* comm)
{   redisReply *reply;
	pthread_mutex_lock(&s_val->tmp_mutex);
	reply = redisCommand(s_val->c, "SELECT 12");
	freeReplyObject(reply);
	reply = redisCommand(s_val->c, comm);
	pthread_mutex_unlock(&s_val->tmp_mutex);
	return reply;
}
*/
//hash !!
//
int open_data(struct static_val *s_val, int sock_tmp, struct data_frame* pdata_frame,int lcode)
{ int re_val;			//解析数据后分辨客户端选择的请求，这里保存辨析，以返回
  redisReply *reply;
  int tmp;
  switch(pdata_frame->comm)
  {
    case x3l_login:
        reply = redisCommand(s_val->c, "hget user %d %s", pdata_frame->uid,&pdata_frame->upw);
        if(reply != NULL)
        {   if(strcmp(reply->str,pdata_frame->upw) == 0)
			{   freeReplyObject(reply);
        		reply = redisCommand(s_val->c, "hset online %d %d", pdata_frame->uid,pdata_frame->ip);
				if(reply != NULL)
					re_val = x3l_login;
				else
					re_val = x3l_error;
			}
        	else
        		re_val = x3l_error;
        }
        else
        	re_val = x3l_error;
        freeReplyObject(reply);
    	break;

    case x3l_register://注册用upw 装密码
    	reply = redisCommand(s_val->c, "hset user %d %s", pdata_frame->uid,&pdata_frame->upw);
    	if(reply != NULL)
    	  	re_val = x3l_register;
    	else
    		re_val = x3l_error;
    	freeReplyObject(reply);
    	break;

    case x3l_exit:
    	reply = redisCommand(s_val->c, "hdel online %d %d", pdata_frame->uid,pdata_frame->ip);
		if(reply != NULL)
			re_val = x3l_exit;
		else
			re_val = x3l_error;
		freeReplyObject(reply);
		break;

    case x3l_hello_srv:
    	re_val = x3l_hello_srv;
    	//显示收到的数据
	    printf("recv socket:%d--'%d-%d-%d-%s-%s-%d-%d-%d-%d-%d-%s-%s' from client\n",sock_tmp,pdata_frame->encode,pdata_frame->comm,pdata_frame->uid,pdata_frame->uname,pdata_frame->upw,pdata_frame->ip,pdata_frame->age,pdata_frame->sex,pdata_frame->port,pdata_frame->u_backup,pdata_frame->s_backup,pdata_frame->buf);
    	break;
    case x3l_other_cli://获取其他用户IP
    	reply = redisCommand(s_val->c, "hget online %d %d", pdata_frame->uid,pdata_frame->ip);
    	if(reply != NULL)
		{ //对方在线
    	  tmp = reply->integer;
          memset(pdata_frame,0,sizeof(struct data_frame));
		  pdata_frame->comm = x3l_other_cli;
		  pdata_frame->ip = reply->integer;//提早格式化-用ip 存对方的ip
		  pdata_frame->u_backup = lcode;
		  freeReplyObject(reply);
		  return x3l_other_cli;
		}
		else
			re_val = x3l_error;
		freeReplyObject(reply);

    	break;
    case x3l_get_cli://获取客服ID
    	memset(pdata_frame,0,sizeof(struct data_frame));
    	pdata_frame->comm = x3l_get_cli;
		pdata_frame->uid = 100000;//客服ID
		pdata_frame->u_backup = lcode;
    	break;
    default:
    	printf("unknow number !!\n");
      return x3l_error;//返回错误操作
  }
  //
  //提交查询语句

  //处理结果集--暂时都没有统一做数据库结果集处理
  memset(pdata_frame,0,sizeof(struct data_frame));
  pdata_frame->comm = re_val;
  pdata_frame->u_backup = lcode;
  return re_val;//返回正确操作
}

