#include <stdio.h>
#include <zephyr/logging/log.h>

#define MAX_BOARD_NAME_LEN 20

class myConfigClass {
   public:
      bool cppEnable;
      bool cpp17;
      char boardName[MAX_BOARD_NAME_LEN];
} myConfig;

int main(void) 
{
   myConfig.cppEnable = CONFIG_CPP;
   myConfig.cpp17     = CONFIG_STD_CPP17;
   strncpy(myConfig.boardName, CONFIG_BOARD, MAX_BOARD_NAME_LEN);
   printf("board name: %s is cpp enable? %u version 17? %u\r\n",myConfig.boardName,myConfig.cppEnable,myConfig.cpp17);

   return 0;
}
