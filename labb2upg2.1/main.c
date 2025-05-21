#include <7.c>
#include <nrfx_rtc.h>
const nrfx_rtc_t rtc_instance = NRFX_RTC_INSTANCE(0);
int main(void){
    nrfx_systick_init();
     const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(20, 22);
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);


   nrfx_rtc_config_t config1 = NRFX_RTC_DEFAULT_CONFIG;
   
   nrfx_rtc_enable(&rtc_instance);
   int i = 2;
   char buffer[10]; 
   int random; 
   int seed;
   nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
while(1){
    nrfx_systick_delay_ms(150);
    if(nrf_gpio_pin_read(BUTTON1) == 0  ){
    // Assuming that Data is an int, adjust if needed
                    seed = nrfx_rtc_counter_get(&rtc_instance);
                    srand(seed);
                    random = rand();
                    
                    sprintf(buffer, "%d\n\r", random);  // Format the integer into a string
                    uarte_write(buffer, strlen(buffer));

   }

}
   
}



