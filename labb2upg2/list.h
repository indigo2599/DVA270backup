#ifndef LIST_H
#define LIST_H

#include <nrfx.h>

/*******************************************************/
/* DVA270 - Interface för dubbellänkad lista           */
/* Anpassad efter interface från DVA244                */
/* av Stefan Bygde och Caroline Uppsäll                */
/* Vid fel eller frågor, kontakta jonas.larsson@mdu.se */
/*******************************************************/


typedef int Data;

/*******************************************************/
/* Avkommentera den struktdefinition ni vill använda,  */
/* Beroende på om ni vill implementera en enkel- eller */
/* dubbellänkad lista.                                 */
/*******************************************************/

/*
//struktdefinition för dubbellänkad lista
typedef struct node
{
	Data data;
	struct node* next;
	struct node* previous;
}Node;
*/


//struktdefinition för enkellänkad lista
typedef struct node
{
	Data data;
	struct node* next;
}Node;


typedef Node *List; //Listan representeras av en nodpekare. 

/* Funktionsdeklarationer */

//Returnera en tom lista
List create_empty_list(void);

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0
int is_empty(const List list);

//Lägg till en nod först i listan
void add_first(List *list, const Data data); //1

//Lägg till nod sist i listan
void add_last(List *list, const Data data); //2 

//Ta bort första noden i listan
void remove_first(List *list);  //3 

//Ta bort sista noden i listan
void remove_last(List *list); //4

//Töm listan (ta bort alla noder ur listan)
void clear_list(List *list);//5 

//Skriv ut listan genom UART
void print_list(const List list); //6

//Returnera första datat i listan
Data get_first_element(const List list); //7

//Returnera sista datat i listan
Data get_last_element(const List list); //8

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list); //9

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data); // 10

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *list, const Data data); //11

int is_sorted_list(List *list);
static int sorted_to_array_help(List *list, int* array, int* index);
static int* is_sorted_array(List *list);



#endif