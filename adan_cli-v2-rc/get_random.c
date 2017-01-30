/*
 * get_random.c
 *
 *  Created on: Nov 7, 2016
 *      Author: adan
 */

#include <time.h>

//获取唯一计算码--随机数-->一般就是3*4位数，可能会上亿，但不会超10亿
unsigned int get_random(void)
{ clock_t clock_tmp;
  double d_tmp;
  for(;;)
    {
      clock_tmp = clock();//获取CPU 系统始终random
      d_tmp = (double)(clock_tmp) / CLOCKS_PER_SEC;
      d_tmp = d_tmp*1000000;//只取前面7位--实际经常只有3位--预留多4位
      if(d_tmp > 100 )
	break;//只取种子>100
    }
  d_tmp = d_tmp*17;//将前7位*17扰乱
  //获取系统时间random
  unsigned int tmp;
  for(;;)
    {
      tmp = (unsigned)time( NULL );
      tmp = tmp%100000;//取最后的5位数--可能是00000
      if(tmp != 0)
	break;//只要不等于0,就返回
    }
  tmp = tmp*13;//将后5位/13扰乱
  tmp = (unsigned int)tmp*d_tmp;
  if(tmp < 990000000)//少于9.9亿？tmp+9213:tmp/10-9213
    return tmp+20566;//加入干扰值
  else
    return tmp/46-9859;//大于9.9亿/1000-9213
}
//
//获取boss 最后一位
unsigned int get_last1(unsigned int boss)
{ unsigned int tmp = boss%10;//取最后一位数
  if(tmp == 0)
    tmp++;//最后一位不许为0,0和1重叠
  return tmp;
}
//
//获取boss 第二位
unsigned int get_last2(unsigned int boss)
{ unsigned int tmp = boss%100;
  if(tmp < 10)
    return 1;//第二位不许为0,0和1重叠
  return tmp/10;
}
//
//在数据报中隐藏唯一计算码--将boss 变成超10亿的数--
unsigned int hide_random(unsigned int boss)
{ unsigned int tmp = boss%10;
  switch(tmp)
  {
    case 0://尾数=0,翻译成7
      tmp = boss+1783127;
      break;
    case 1://尾数=1,翻译成6
      tmp = boss+375;
      break;
    case 2://尾数=2,翻译成4
      tmp = boss+362732;
      break;
    case 3://尾数=3,翻译成0
      tmp = boss+2137;
      break;
    case 4://尾数=4,翻译成5
      tmp = boss+90031;
      break;
    case 5://尾数=5,翻译成2
      tmp = boss+9307;
      break;
    case 6://尾数=6,翻译成1
      tmp = boss+640035;
      break;
    case 7://尾数=7,翻译成9
      tmp = boss+50402;
      break;
    case 8://尾数=8,翻译成3
      tmp = boss+41084105;
      break;
    case 9://尾数=9,翻译成8
      tmp = boss+79;
      break;
    default:
      printf("hide_random error\n");
      tmp = -1;//错误
      break;
  }
  return tmp;
}
//
//还原被隐藏的唯一计算码
unsigned int encode_random(unsigned int frame_encode)
{
  unsigned int tmp = frame_encode%10;
  switch(tmp)
  {
    case 0://尾数=0,还原成3
      tmp = frame_encode-2137;
      break;
    case 1://尾数=1,还原成6
      tmp = frame_encode-640035;
      break;
    case 2://尾数=2,还原成5
      tmp = frame_encode-9307;
      break;
    case 3://尾数=3,还原成8
      tmp = frame_encode-41084105;
      break;
    case 4://尾数=4,还原成2
      tmp = frame_encode-362732;
      break;
    case 5://尾数=5,还原成4
      tmp = frame_encode-90031;
      break;
    case 6://尾数=6,还原成1
      tmp = frame_encode-375;
      break;
    case 7://尾数=7,还原成0
      tmp = frame_encode-1783127;
      break;
    case 8://尾数=8,还原成9
      tmp = frame_encode-79;
      break;
    case 9://尾数=9,还原成7
      tmp = frame_encode-50402;
      break;
    default:
      printf("encode_random error\n");
      tmp = -1;//错误
      break;
  }
  return tmp;
}
