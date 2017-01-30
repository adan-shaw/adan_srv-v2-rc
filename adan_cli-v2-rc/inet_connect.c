/*
 * inet_connect.c
 *
 *  Created on: Oct 13, 2016
 *      Author: adan
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <errno.h>
//************************
//success return socket fd, fail return -1
//************************
int inet_connect(char* srv_ip,int port)
{
  //create socket
  int sfd;
  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sfd == -1)
  {
    printf("create socket fail, errno: %d\n",errno);
    return -1;
  }

  //设置重用本地地址和端口
  int nREUSEADDR = 1;
  if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(const char*)&nREUSEADDR,sizeof(int)) == -1)
  {
    printf("setsockopt = nREUSEADDR = 1 fail, errno: %d\n",errno);
    return -1;
  }
  //设置:如果服务器主动关闭剔除客户端,客户端强制关闭
  struct linger m_sLinger;
  m_sLinger.l_onoff = 1; // (在closesocket()调用,但是还有数据没发送完毕的时候容许逗留)
  m_sLinger.l_linger = 0; // (容许逗留的时间为0秒)
  if(setsockopt(sfd,SOL_SOCKET,SO_LINGER,(const char*)&m_sLinger,sizeof(struct linger)) == -1)
  {
    printf("setsockopt = l_linger = 0 fail, errno: %d\n",errno);
    return -1;
  }

  //init server info
  struct sockaddr_in addr_tmp;
  addr_tmp.sin_addr.s_addr = inet_addr(srv_ip);
  addr_tmp.sin_family = AF_INET;
  addr_tmp.sin_port = htons(port);

  //start connect
  if(connect(sfd, &addr_tmp, sizeof(struct sockaddr_in)))
  {
    printf("connection server fail, errno: %d\n",errno);
    return -1;
  }

  //printf("\ninet socket connect server success\n");
  return sfd;
}




