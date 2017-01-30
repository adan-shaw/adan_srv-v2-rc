/*
 * static_val.h
 *
 *  Created on: Nov 3, 2016
 *      Author: adan
 */

//512 以下 512-96=416
#define BUF_SIZE 400

struct data_frame{
  unsigned int encode;		//4
  unsigned int comm;		//4
  unsigned int uid;		//4
  char uname[16];		//16
  char upw[16];			//16
  unsigned int ip;		//4
  unsigned int port;		//4
  unsigned int age;		//4
  unsigned int sex;		//4
  unsigned int u_backup;	//4
  char s_backup[32];		//32
  char buf[BUF_SIZE];		//BUF_SIZE
};
//
//#define SRV_IP "192.168.56.1"
#define SRV_IP "127.0.0.1"
#define SRV_PORT 9213

//客户端--全局变量
//
struct static_val{
  unsigned int test_err;
  unsigned int test_count;
};




