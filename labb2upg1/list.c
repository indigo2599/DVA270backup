#include <list.h>
#include <7.h>
#include <assert.h>



//Returnera en tom lista - funktionen är färdig
List create_empty_list(void)
{
	List list = {NULL};
    return list;
}

//Här skapas nya noder. Denna funktion är den enda som ska använda malloc.
//Denna funktion ska i sin tur bara kallas av add_first och add_last.
//Notera att den är static och inte finns med i interfacet
static Node * create_list_node(const Data data)
{	
	
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (newNode == NULL) { 
		return NULL;
	}

	newNode->data = data;
	newNode->next = NULL;  // Eftersom den vet inte vad som är efter. 
	return newNode;
	//glöm inte att kolla så att malloc inte returnerade NULL
}

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0 
int is_empty(const List list)
{
	if (list == NULL) { 
		return 1;
	}
	return 0;
}

//Lägg till en nod först i listan
void add_first(List *list, const Data data)
{	
	
	Node *newNode = create_list_node(data);
	if (newNode == NULL) {
		return;
	}

	newNode->next = *list;
	*list = newNode;
}

//lägg till nod sist i listan
void add_last(List *list, const Data data)
{
	
		Node *newNode = create_list_node(data);
		if (newNode == NULL) {
			return;
		}

		newNode->next = NULL;

		if (*list == NULL){
			*list = newNode;
		}
		else{
		Node *current = *list;


		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newNode;

		}
}

//Ta bort första noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_first(List *list)
{
	assert(list != NULL && *list != NULL);
	Node *temp = *list;
	*list = (*list)->next;
	free(temp);
}

//ta bort sista noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_last(List *list)
{
	assert(list != NULL && *list != NULL);

    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
        return;
    }

    Node *current = *list;
    while (current->next != NULL && current->next->next != NULL) {
        current = current->next;
    }

    Node *temp = current->next;
    current->next = NULL;
    free(temp);

}

//töm listan (ta bort alla noder ur listan)
//postcondition: Listan är tom, *list är NULL
void clear_list(List *list)
{

	assert(list != NULL);
	if (*list == NULL) {
    	return;
    }
    
    clear_list(&((*list)->next));
	free(*list);

    *list = NULL;

}

//Skriv ut listan genom UART
void print_list(const List list)
{
    
	Node *node = list;
    if (list != NULL) {
        char buffer[10];
        sprintf(buffer, "%d ", node->data);
        uarte_write(buffer, strlen(buffer));
        print_list(node->next);
    }
}

//returnera första datat i listan
//precondition: listan är inte tom (testa med assert)
Data get_first_element(const List list)
{	
	assert(list != NULL);
	
      // 
	return list->data;
}

//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List list)
{
	 // Ensure the list is not empty
    assert(list != NULL);

    // Handle the case where the list has only one element
    if (list->next == NULL) {
        // If the list has only one element, return it directly
        char buffer[10];
        sprintf(buffer, "%d", list->data);  // Print the data of the only node
        uarte_write(buffer, strlen(buffer));  // Send the data over UART
        return list->data;  // Return the data from the first node
    }

    // Traverse the list to the last node
    Node* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
   
    return current->data;
 
	
}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list)
{
	Node* current = list;
	int i = 0;
	while (current != NULL) {
			i++;
        	current = current->next;      
		}
		return i;
}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data)
{
	Node* current = list;
	while (current->data != data) {
        	current = current->next;      
		}
		if (current->data == data ) {
		return 1;
		}
		return 0;
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1

int remove_element(List *list, const Data data)
{
    if (list == NULL || *list == NULL) {
        return 0;
    }

    Node* current = *list;        
    Node* currentBefore = NULL;

    
    while (current != NULL && current->data != data) {
        currentBefore = current;    
        current = current->next;    
    }

    
    if (current != NULL && current->data == data) {
       
        if (currentBefore == NULL) {
            *list = current->next; 
        } else {
            currentBefore->next = current->next;  
        }

        
        free(current);

        return 1;  
    }

    return 0;
}







	