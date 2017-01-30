/*
 * main_func.h
 *
 *  Created on: Nov 3, 2016
 *      Author: adan
 */


#include <sys/resource.h>	/* 设置最大的连接数需要setrlimit */
#include <sys/epoll.h>		/* epoll头文件 */
#include <fcntl.h>	        /* nonblocking需要 */

#define	MAXEPOLL	300000	/* 每个进程允许打开的最大文件数 30W*/




