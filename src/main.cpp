#include <stdio.h>
#include <zephyr/logging/log.h>
#include <zephyr/devicetree.h>

#include "util/include/util.h"

//LOG_MODULE_REGISTER(my_module, LOG_LEVEL_DBG);
LOG_MODULE_REGISTER(my_module2, LOG_LEVEL_DBG);

#define MAX_BOARD_NAME_LEN 20

class myConfigClass {
   public:
      bool cppEnable;
      bool cpp17;
      char boardName[MAX_BOARD_NAME_LEN];
} myConfig;

int data=0;

int main(void) 
{
//   myConfig.cppEnable = CONFIG_CPP;
//   myConfig.cpp17     = CONFIG_STD_CPP17;
//   strncpy(myConfig.boardName, CONFIG_BOARD, MAX_BOARD_NAME_LEN);
//   printf("board name: %s is cpp enable? %u version 17? %u\r\n",myConfig.boardName,myConfig.cppEnable,myConfig.cpp17);
//
//   data = DT_PHA_BY_IDX(DT_PATH(zephyr_user), data_s, 0, data2);
//   data = DT_PHA_BY_IDX(DT_PATH(zephyr_user), ppp, 0);
//   printf("data2: %d\r\n",data);

   myUtilFunction(4,2);
 return 0;
}
