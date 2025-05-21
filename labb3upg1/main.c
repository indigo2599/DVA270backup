#include <7.c>

#include <BSTree-5.c>
int main(void){



    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(20, 22);
    nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
    if (errr != 0)
    {
        // Do something... perhaps?
    }
    
	BSTree tree = create_empty_tree(); 
    int* arr = NULL;
    int size = 0;

   

    
while(1){
        
    char chosieOfList[] = "\r\n1: Sort tree: \r\n2: Tree empty? \r\n3: Insert: \r\n4: Print preorder: \r\n5: Print inorder: \r\n6: Print postorder: \r\n7: Find: \r\n8: Remove element: \r\n9: Number of nodes: \r\n10: Depth: \r\n11: min depth: \r\n12: Balance tree: \r\n13: Free tree: \r\n14: Sorted Array: \r\n15: Sorted list: \r\nInput: ";
        uarte_write(chosieOfList, strlen(chosieOfList));
        int depth1 ;
        int choise = read_int();
        char addNumber1[] = "";
        char preorder[] = "Preorder: ";
        char inorder[] = "Inorder: ";
        char postorder[] = "Postorder: ";
        char addNumber[] = "Skriv tal att lägga till: ";
        char creatTree[] = "Tree created:";
        char tomt[] = "Trädet är tomt:";
        char ickeTomt[] = "Trädet är inte tomt:";
        char toFindNummer[] = "Vilket nummer vill du Hitta: ";
        char findNummerYes[] = "Hittade:";
        char findNummerNo[] = "Hittade inte:";
        char removeEle[] = "Nummer att ta bort: ";
        char removeEleYes[] = "Nummert är borta: ";
        char removeEleNo[] = "Nummert finns inte: ";
        char nummerNodes[] = "Noder: ";
        char depthText[] = "Depth: ";
        char depthMinText[] = "Depth min: ";
        char freeTree[] = "Trädet är bortaget: ";
        char sortedArray[] = "Array is sorted: ";
        char sortedNotArray[] = "Array is not sorted: ";
        char buffer[10];
        int size;
        int* arr;
        int value;

        
        if (0 < choise && choise < 16 )
        switch (choise) {
            case 1:  
                size = number_of_nodes(tree);  
                arr = write_sorted_to_array(tree); 
                build_tree_sorted_from_array(&tree, arr, size);
                free(arr);
                break;

            case 2:  
                if(is_empty(tree)) {
                    uarte_write(tomt, strlen(tomt));
                }
                else {
                    uarte_write(ickeTomt, strlen(ickeTomt));
                }
                break; 
            case 3:  
                uarte_write(addNumber, strlen(addNumber));
                value = read_int();
                insert_sorted(&tree, value);
                break;
            case 4:  
                uarte_write(preorder, strlen(preorder));
                print_preorder(tree);
                break;
            case 5:  
                uarte_write(inorder, strlen(inorder));
                print_inorder(tree);
                break;
            case 6:
                uarte_write(postorder, strlen(postorder));
                print_postorder(tree);
                break; 
            case 7:                
                uarte_write(toFindNummer, strlen(toFindNummer));
                value = read_int();
                if(find(tree, value)) {
                    uarte_write(findNummerYes, strlen(findNummerYes));
                }
                else {
                    uarte_write(findNummerNo, strlen(findNummerNo));
                }
               
                break;
            case 8: 

                uarte_write(removeEle, strlen(removeEle));
                 value = read_int();

                if(find(tree, value)) {
                    remove_element(&tree, value);
                    uarte_write(removeEleYes, strlen(removeEleYes));
                }    
                else {
                    uarte_write(removeEleNo, strlen(removeEleNo));
                }
                break;
            case 9: 
                value = number_of_nodes(tree);

                uarte_write(nummerNodes, strlen(nummerNodes));
                buffer[10];
                sprintf(buffer, "%d", value);
                uarte_write(buffer, strlen(buffer));
                break;
                
            case 10:// djup och minimum djup
                depth1 = depth(tree);

                uarte_write(depthText, strlen(depthText));
                buffer[10];
                sprintf(buffer, "%d", depth1);
                uarte_write(buffer, strlen(buffer));
                break; 
            case 11:
                value = min_depth(tree);
                uarte_write(depthMinText, strlen(depthMinText));
                buffer[10];
                sprintf(buffer, "%d", value);
                uarte_write(buffer, strlen(buffer));
                break;

            case 12: // balens tree
                balance_tree(&tree);
                break;
            case 13: // free tree
                uarte_write(freeTree, strlen(freeTree));
                free_tree(&tree);
                break; 
            case 14:
                if(is_sorted_array(list)) {
                    uarte_write()
                }
    }
}
}
