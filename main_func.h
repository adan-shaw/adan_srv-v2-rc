/*
 * main_func.h
 *
 *  Created on: Nov 3, 2016
 *      Author: adan
 */

#include "epoll_head.h"
#include "static_val.h"

//mysql 服务器信息
const char *g_host_name = "127.0.0.1";
const char *g_user_name = "as";
const char *g_password  = "work";
const char *g_db_name   = "as";
const int   g_db_port   = 3306;

//g_user_name and g_db_name 前缀都是as+首大写功能名 如asManager
