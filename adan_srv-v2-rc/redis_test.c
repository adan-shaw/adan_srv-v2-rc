/*
 * my_test.c
 *
 *  Created on: Jan 28, 2017
 *      Author: adan
 */

#include <stdio.h>
#include "hiredis-master/hiredis.h"
#include "hiredis-master/net.h"

int redis_main (void)
{
	printf ("*****************************************\n");
	printf ("my turn !!\n");
	printf ("*****************************************\n");
	//链接到redis
	redisContext *c = redisConnect ("127.0.0.1", 6379);
	if (c != NULL && c->err)
	{
		printf ("Error: %sn", c->errstr);	// handle error
	}

	sleep (2);
	int tmp;
	char rbuf[64];

	redisReply *reply;						//就算redisReply 是实体，但是redisReply 结构体里面装的是指针
	//所以实际redisReply 还是用new 的方式实现的，必须释放
	//而且redisCommand() 返回的是redisReply 实体，这里必须是指针
	reply = redisCommand (c, "set f1 bar");	//直接发命令
	reply = redisCommand (c, "rpush f11 bar");
	reply = redisCommand (c, "sadd f12 bar");
	reply = redisCommand (c, "hset f13 bar bar");
	reply = redisCommand (c, "zadd f14 1 bar");
	freeReplyObject (reply);

	reply = redisCommand (c, "SET f2 %s", "value");	//直接发格式化变量
	reply = redisCommand (c, "rpush f21 %d", tmp);
	reply = redisCommand (c, "sadd %d %d", tmp, tmp);
	reply = redisCommand (c, "hset %s bar bar", "f23");
	reply = redisCommand (c, "zadd f24 1 bar");
	freeReplyObject (reply);

	reply = redisCommand (c, "SET f3 %b", "1234567890", (size_t) 11);	//直接发二进制数据块
	freeReplyObject (reply);

	reply = redisCommand (c, "SELECT 12");
	freeReplyObject (reply);
	redisCommand (c, "SET f4 bar");
	reply = redisCommand (c, "rpush f41 bar");
	reply = redisCommand (c, "sadd f42 bar");
	reply = redisCommand (c, "hset f43 bar bar");
	reply = redisCommand (c, "zadd f44 1 bar");
	//*********************
	for (tmp = 0; tmp < 100; tmp++)
	{
		/* 不要用格式化字符串然后传递字符串，redis 对字符串缓冲区长度敏感
		   sprintf (&rbuf, "hset a %d %d\0", tmp,tmp);
		   reply = redisCommand(c, rbuf);
		   sprintf (&rbuf, "hset a %d %d", tmp+1,tmp);
		   reply = redisCommand(c, rbuf);
		   sprintf (&rbuf, "hset a %d %d\0", tmp+2,tmp);
		   reply = redisCommand(c, &rbuf);
		   sprintf (&rbuf, "hset a %d %d", tmp+3,tmp);
		   reply = redisCommand(c, &rbuf);
		 */
		reply = redisCommand (c, "rpush %d %d", tmp);

	}

	redisFree (c);
	//flushall
	printf ("everything is good \n");
	return 0;
}
