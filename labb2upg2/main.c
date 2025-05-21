#include <7.c>
#include <list.c>
#define MAX_VALUE 10


int main(void){



    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(20, 22);
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
    if (errr != 0)
    {
        // Do something... perhaps?
    }
    List head = create_empty_list();  //Kom ihåg att head alltid ska peka på det första elementet i listan   
    char buffer[10];
    int array[MAX_VALUE];
      uint32_t rtc_value = get_rtc_counter_value();
        srand(rtc_value);
    for(int i = 0; i < MAX_VALUE; i++) {
      
        array[i] = rand()%100;
        int tal = array[i];
       uarte_write(tal, strlen(buffer));
    }
    for(int j = 0; j < MAX_VALUE; j++) {
        buffer[10];
        int tal = array[j];
       uarte_write(tal, strlen(buffer));
       add_last(&head, array[j]);
    }
    

    int value;
	
    while(1){
        char chosieOfList[] = "\r\n1: Add first: \r\n2: Add last: \r\n3: Remove first: \r\n4: Remove last: \r\n5: Clear list: \r\n6: Print list: \r\n7: Get first element: \r\n8: Get last element: \r\n9: Number of nodes: \r\n10: Search: \r\n11: Remove elament:\r\n12: Array sorted: \r\nSvar: ";
            uarte_write(chosieOfList, strlen(chosieOfList));

        int choise = read_int();
        char addNumber[] = "Välj ett tal du vill lägga in i listan: ";
        char findNumber[] = "Välj ett tal du vill hitta: ";
        char removeNumber[] = "Välj ett tal du vill ta bort: ";
        char removeNumberSpecComp[] = "Tog bort talet ";
        char removeNumberSpecNot[] = "Tog inte bort talet ";
        char findNumberfound[] = "Hittade talet ";
        char findNumberNot[] = "Hittade inte talet ";
        char sortedArray[] = "Array is sorted: ";
        char sortedNotArray[] = "Array is not sorted: ";
       
        Data data;

        if (0 < choise && choise < 13 )
        switch (choise) {
            case 1:
                uarte_write(addNumber, strlen(addNumber));
                value = read_int();
                add_first(&head, value);
                break;
            case 2:  
                uarte_write(addNumber, strlen(addNumber));
                value = read_int();
                add_last(&head, value);
                break;
            case 3: remove_first(&head); break; 
            case 4: remove_last(&head); break;
            case 5: clear_list(&head); break;
            case 6: print_list(head); break;
            case 7: 
                    data = get_first_element(head);
                    buffer[10];  // Assuming that Data is an int, adjust if needed
                    sprintf(buffer, "%d", data);  // Format the integer into a string
                    uarte_write(buffer, strlen(buffer)); // Assuming you have the function uarte_write to send data over UART
                    break;
            case 8: data = get_last_element(head); 
                    buffer[10];
                    sprintf(buffer, "%d", data);
                    uarte_write(buffer, strlen(buffer));
                    break;
            case 9: 
                int i = number_of_nodes(head); 
                buffer[10];
                sprintf(buffer, "%d ", i);  
                uarte_write(buffer, strlen(buffer));    
                break;
            case 10:
                uarte_write(findNumber, strlen(findNumber));
                value = read_int();
                if(search(head, value)){
                    uarte_write(findNumberfound, strlen(findNumberfound));
                }
                else{
                    uarte_write(findNumberNot, strlen(findNumberNot));
                }
                break;  
            case 11: 
                uarte_write(removeNumber, strlen(removeNumber));
                value = read_int();
                if (remove_element(&head, value)){
                    uarte_write(removeNumberSpecComp, strlen(removeNumberSpecComp));
                }
                else{
                    uarte_write(removeNumberSpecNot, strlen(removeNumberSpecNot));
                }
                break;  
            case 12: 
                /*if(is_sorted_array(array)) {
                    uarte_write(sortedArray, strlen(sortedArray));
                }*/
                break;
        }
    }
}

