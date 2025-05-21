#include <7.c>
#include <nrfx_rtc.h>
#include <list.c>
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
   int first;
   int last;
   int check;
   nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
   nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
   nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
   List stack = create_empty_list();
   List que = create_empty_list();
   char add[] = "adderar: ";
        char stack1[] ="stack: " ;
        char que1[] = "que: ";
        char test[] = "deque: ";
        char test1[] = "pop: ";
    while(1){
        
        if(nrf_gpio_pin_read(BUTTON1) == 0  ){
            seed = nrfx_rtc_counter_get(&rtc_instance);
            srand(seed);
            random = rand();
            check = random % 2;            
            buffer[10]; 
            uarte_write(add, strlen(add));
            sprintf(buffer, "%d\n\r", random); 
            uarte_write(buffer, strlen(buffer));
                        
            if(check == 0){
                //push
                add_last(&stack, random);


            }else{
                //enque
                add_last(&que, random);
            }  
            //front
            if(is_empty(que) == 0){
                first = get_first_element(que);
                uarte_write(que1, strlen(que1));
                buffer[10];  
                sprintf(buffer, "%d\n\r", first); 
                uarte_write(buffer, strlen(buffer)); 
            }
            //peek
            if(is_empty(stack) == 0){
                 last = get_last_element(stack);
                 uarte_write(stack1, strlen(stack1));
                buffer[10];  
                sprintf(buffer, "%d\n\r", last);  
                uarte_write(buffer, strlen(buffer));
            }
           
               
        
                nrfx_systick_delay_ms(1000);
                
        }    

        if(nrf_gpio_pin_read(BUTTON2) == 0){
            //pop
              uarte_write(test1, strlen(test1));
            if(is_empty(stack) == 0){
                    remove_last(&stack);
                    if(is_empty(que) == 0){
                    first = get_first_element(que);
                    uarte_write(que1, strlen(que1));
                    buffer[10];  
                    sprintf(buffer, "%d\n\r", first); 
                    uarte_write(buffer, strlen(buffer)); 
                }
                    //peek
                if(is_empty(stack) == 0){
                    last = get_last_element(stack);
                    uarte_write(stack1, strlen(stack1));
                    buffer[10];  
                    sprintf(buffer, "%d\n\r", last);  
                    uarte_write(buffer, strlen(buffer));
                }
            }
                      
            
        
            nrfx_systick_delay_ms(1000);
                
            
        }
        if(nrf_gpio_pin_read(BUTTON3) == 0){
            uarte_write(test, strlen(test));
            //dequeue();
            if(is_empty(que) == 0){


                remove_first(&que);
                if(is_empty(que) == 0){
                    first = get_first_element(que);
                    uarte_write(que1, strlen(que1));
                    buffer[10];  
                    sprintf(buffer, "%d\n\r", first); 
                    uarte_write(buffer, strlen(buffer)); 
                }
                    //peek
                if(is_empty(stack) == 0){
                    last = get_last_element(stack);
                    uarte_write(stack1, strlen(stack1));
                    buffer[10];  
                    sprintf(buffer, "%d\n\r", last);  
                    uarte_write(buffer, strlen(buffer));
                }
            }
            
                
           
                nrfx_systick_delay_ms(1000);
            
            }

    }
       
    
        
}
    
   




