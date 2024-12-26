#include <stdio.h>
#include <zephyr/logging/log.h>

//LOG_MODULE_REGISTER(my_module, LOG_LEVEL_DBG);
LOG_MODULE_REGISTER(my_module2, LOG_LEVEL_DBG);

int main() 
{
   LOG_INF("hola");
   LOG_ERR("hola");
   printf("Hello, World!\n");
// printf("Hello, World! %u %u\n",CONFIG_IOMICO_OPTION_A,CONFIG_IOMICO_OPTION_B);

 return 0;
}
