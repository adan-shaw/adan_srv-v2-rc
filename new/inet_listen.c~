/*
 * inet_listen.c
 *
 *  Created on: Oct 13, 2016
 *      Author: adan
 */

#include <sys/socket.h>
#include <fcntl.h>	        /* nonblocking需要 */
#include <netinet/in.h>		/* socket类定义需要*/
#include <stdio.h>
#include <errno.h>

#define BACKLOG 20	//BACKLOG = MAX wait user

//
//success return socket fd, fail return -1
int inet_listen(char* inet_ip, int port)
{ int sfd;
  sfd = socket(AF_INET, SOCK_STREAM, 0);  //create socket
  if(sfd == -1){
	printf("create socket fail, errno: %d\n",errno); return -1;
  }
  //set nonblocking
  if(fcntl_nonblocking(sfd) == -1)
    return -1;
  //init sockaddr_in
  struct sockaddr_in addr_tmp;
  memset(&addr_tmp, 0, sizeof(struct sockaddr_in));
  addr_tmp.sin_addr.s_addr = inet_addr(inet_ip);
  addr_tmp.sin_family = AF_INET;
  addr_tmp.sin_port = htons(port);
  //
  //bind
  if(bind(sfd, (struct sockaddr_in*)&addr_tmp, sizeof(struct sockaddr_in)) == -1){
    printf("socket %d bind fail, errno: %d\n", sfd, errno); return -1;
  }
  //start listen
  if(listen(sfd, BACKLOG) == -1){
    printf("socket %d listen fail, errno: %d\n", sfd, errno); return -1;
  }
  printf("*****tcp socket %d listen port %d success*****\n", sfd, port);
  return sfd;//success
}
//
//通用ctl 设置 socket nonblocking
int fcntl_nonblocking(int fd)
{ if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK) == -1){
    printf("socket %d set blocking fail, errno: %d\n", fd, errno); return -1;
  }
  return 0;
}
