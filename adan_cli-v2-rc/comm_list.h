/*
 * comm_list.h
 *
 *  Created on: Jan 28, 2017
 *      Author: adan
 */

//就5条数据报，不多吧
#define x3l_login 9213
#define x3l_register 9214//注册肯定要，不然就只能一次聊天了，不能记住对方ID
#define x3l_exit 9215


#define x3l_hello_srv 9216
#define x3l_other_cli 9217

#define x3l_get_cli 9218	//获取更多的客户端--随机弄20个出来？？
//不要弄好友系统，很麻烦，先能根据ID 发信息就很不错了
//#define x3l_make_add 9217
//#define x3l_make_del 9217

#define x3l_error 9219
