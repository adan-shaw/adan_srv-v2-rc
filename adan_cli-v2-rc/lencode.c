/*
 * lencode.c
 *
 *  Created on: Jan 25, 2017
 *      Author: adan
 */


#include <time.h>
#include <stdio.h>
#include <sys/time.h>
//
//做个线程，sleep() 执行定期任务，检查离线认证并更新
//10 分钟一换--尽量放大tm_min / 10
unsigned int get_lencode(void)
{
	time_t t;
	struct tm *gmp;
	t = time(NULL);
	gmp = gmtime(&t);//日期和时间转换为格林威治(GMT)时间

	unsigned int n1,n2;
	n1 = gmp->tm_year * gmp->tm_mon * gmp->tm_mday;
	n2 = gmp->tm_min / 10;//0,1,2,3,4,5

	if( n2 == 0 )
		{ n2 = gmp->tm_hour;//0-24 or 0-12
		  return n2 * ++n2 * ++n2 * ++n2 * ++n2* ++n2 * 2721 + n1 *  + 91213; }
	else
		return ( n2 * ++n2 * ++n2 * ++n2 * ++n2* ++n2 ) * gmp->tm_hour * gmp->tm_hour * 123 + n1 + 123456;
}



