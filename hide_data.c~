/*
 * hide_data.c
 *
 *  Created on: Nov 7, 2016
 *      Author: adan
 */
#include <math.h>
#include "static_val.h"

void pickup_encode_int(void* arg,int change_val)
{ struct data_frame* pdata_frame = arg;
  pdata_frame->comm = pdata_frame->comm + change_val + 20;
  pdata_frame->uid = pdata_frame->uid + change_val + 566;
  pdata_frame->ip = pdata_frame->ip + change_val + 98;
  pdata_frame->port = pdata_frame->port + change_val + 59;
  pdata_frame->age = pdata_frame->age + change_val + 9213;
  pdata_frame->sex = pdata_frame->sex + change_val + 84;
  pdata_frame->u_backup = pdata_frame->u_backup + change_val + 588;
  return;
}

void pickup_encode_char(void* arg,int change_val)
{ struct data_frame* pdata_frame = arg;
  int tmp;
  for(tmp = 0;tmp<16;tmp++)
    {
      pdata_frame->uname[tmp] = pdata_frame->uname[tmp] + change_val;
      pdata_frame->upw[tmp] = pdata_frame->upw[tmp] + change_val;
    }
  for(tmp = 0;tmp<32;tmp++)
    pdata_frame->s_backup[tmp] = pdata_frame->s_backup[tmp] + change_val;
  for(tmp = 0;tmp<BUF_SIZE;tmp++)
    pdata_frame->buf[tmp] = pdata_frame->buf[tmp] + change_val;
  return;
}

void open_encode_int(void* arg,int change_val)
{ struct data_frame* pdata_frame = arg;
  pdata_frame->comm = pdata_frame->comm - change_val - 20;
  pdata_frame->uid = pdata_frame->uid - change_val - 566;
  pdata_frame->ip = pdata_frame->ip - change_val - 98;
  pdata_frame->port = pdata_frame->port - change_val - 59;
  pdata_frame->age = pdata_frame->age - change_val - 9213;
  pdata_frame->sex = pdata_frame->sex - change_val - 84;
  pdata_frame->u_backup = pdata_frame->u_backup - change_val - 588;
  return;
}

void open_encode_char(void* arg,int change_val)
{ struct data_frame* pdata_frame = arg;
  int tmp;
  for(tmp = 0;tmp<8;tmp++)
    {
      pdata_frame->uname[tmp] = pdata_frame->uname[tmp] - change_val;
      pdata_frame->upw[tmp] = pdata_frame->upw[tmp] - change_val;
    }
  for(tmp = 0;tmp<32;tmp++)
    pdata_frame->s_backup[tmp] = pdata_frame->s_backup[tmp] - change_val;
  for(tmp = 0;tmp<BUF_SIZE;tmp++)
    pdata_frame->buf[tmp] = pdata_frame->buf[tmp] - change_val;
  return;
}

unsigned int hide_math(unsigned int boss,unsigned int ichoose)
{ unsigned int tmp;
  switch(ichoose)
  {
    case 1:
      tmp = boss + log(boss);
      break;
    case 2:
      tmp = boss + boss%1000000;
      break;
    case 3:
      tmp = boss + sqrt(boss);
      break;
    case 4:
      tmp = boss + boss/ichoose-92138;
      break;
    case 5:
      tmp = boss + ichoose*boss%10000;
      break;
    case 6:
      tmp = boss + ichoose*log(boss);
      break;
    case 7:
      tmp = boss + log10(boss);
      break;
    case 8:
      tmp = boss + ichoose*sqrt(boss);
      break;
    case 9:
      tmp = boss + ichoose*log10(boss);
      break;
    default:
      printf("choose encode algorithm error!!\n");
      tmp = -1;
      break;
  }
  return tmp;
}

