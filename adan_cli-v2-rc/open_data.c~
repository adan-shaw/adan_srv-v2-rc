/*
 * open_data.c
 *
 *  Created on: Nov 17, 2016
 *      Author: adan
 */
#include "comm_list.h"
#include "static_val.h"


//解析数据帧
//
void open_data(struct data_frame* pdata_frame)
{ int lcode = get_lencode();
  pdata_frame->u_backup = lcode;

  switch(pdata_frame->comm)
  {
  //uinfo
  case x3l_login:
    printf("~!@#$%^&*(x3l_login adan_srv success~~\n");
    break;
  case x3l_register:
    printf("~!@#$%^&*(x3l_register success!\n");
    break;
  case x3l_exit:
    printf("~!@#$%^&*(x3l_exit success!\n");
    break;
  case x3l_hello_srv:
    printf("~!@#$%^&*(x3l_hello_srv ok\n");
    break;
  case x3l_other_cli:
    printf("~!@#$%^&*(x3l_other_cli success\n");
    break;
  case x3l_get_cli:
    printf("~!@#$%^&*(x3l_get_cli success !\n");
    break;
  case x3l_error:
    printf("~!@#$%^&*(x3l_error success but why??!\n");
    break;
  default:
    printf("~!@#$%^&*(server return a unknow package\n");
    break;
}

}



