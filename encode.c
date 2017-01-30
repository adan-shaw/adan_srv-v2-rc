/*
 * encode.c
 *
 *  Created on: Nov 6, 2016
 *      Author: adan
 */

#include <stdio.h>
#include "static_val.h"

//pickup_open = 1 加密
//pickup_open = 0 解密
//函数不带数据帧尸体,请& 进来实体，或者传指针进来
void frame_encode(void* arg,int pickup_open)
{ struct data_frame* pdata_frame = arg;
  unsigned int tmp;
  unsigned int last1,last2;
  unsigned int boss;
  if(pickup_open == 0)
    { //解密
      boss = encode_random(pdata_frame->encode);//对随机数进行解密
      //boss = pdata_frame->encode;//不隐藏随机码-OK(调试)
      last1 = get_last1(boss);
      last2 = get_last2(boss);
      tmp = hide_math(boss,last1);//计算解密值-int
      open_encode_int(pdata_frame,tmp);
      tmp = hide_math(boss,last2);//计算解密值-char
      open_encode_char(pdata_frame,tmp);
      return;
    }
  else
    { //加密
      boss = get_random();//获取boss
      last1 = get_last1(boss);
      last2 = get_last2(boss);
      tmp = hide_math(boss,last1);//计算解密值-int
      pickup_encode_int(pdata_frame,tmp);
      tmp = hide_math(boss,last2);//计算解密值-char
      pickup_encode_char(pdata_frame,tmp);
      //pdata_frame->encode = boss;//不隐藏随机码-OK(调试)
      pdata_frame->encode = hide_random(boss);//对随机数进行加密
      return;
    }
  printf("encode data fail, unknow order come in\n");
  return;
}
//
//解密数据
void encode_open(struct data_frame* pdata_frame)
{ unsigned int tmp;
  unsigned int last1,last2;
  unsigned int boss;
  boss = encode_random(pdata_frame->encode);//对随机数进行解密
  //boss = pdata_frame->encode;//不隐藏随机码-OK(调试)
  last1 = get_last1(boss);
  last2 = get_last2(boss);
  tmp = hide_math(boss,last1);//计算解密值-int
  open_encode_int(pdata_frame,tmp);
  tmp = hide_math(boss,last2);//计算解密值-char
  open_encode_char(pdata_frame,tmp);
  return;
}
//
//加密数据
void encode_pickup(struct data_frame* pdata_frame)
{ unsigned int tmp;
  unsigned int last1,last2;
  unsigned int boss;
  boss = get_random();//获取boss
  last1 = get_last1(boss);
  last2 = get_last2(boss);
  tmp = hide_math(boss,last1);//计算解密值-int
  pickup_encode_int(pdata_frame,tmp);
  tmp = hide_math(boss,last2);//计算解密值-char
  pickup_encode_char(pdata_frame,tmp);
  //pdata_frame->encode = boss;//不隐藏随机码-OK(调试)
  pdata_frame->encode = hide_random(boss);//对随机数进行加密
  return;
}


