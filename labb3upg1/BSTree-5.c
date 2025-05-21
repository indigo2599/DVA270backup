#include <assert.h>
#include <BSTree-5.h>
#include <math.h>
/*Det är helt tillåtet att lägga till egna hjälpfunktioner men de befintliga funktionerna ska implementeras enligt instruktionerna*/

/* Statiska hjälpfunktioner används av andra funktioner i trädet och ska inte ligga i interfacet (användaren behöver inte känna till dessa) */

/* Skapar en trädnod med det givna datat. Denna funktion bör vara den enda som använder malloc för att skapa en ny treeNode*/
static struct treeNode* create_tree_node(int data)
{
    
	struct treeNode* newTreeNode = (struct treeNode*)malloc(sizeof(struct treeNode));
	if (newTreeNode == NULL) { 
		return NULL;
	}

	newTreeNode->data = data;
	newTreeNode->left = NULL;  
    newTreeNode->right = NULL;
	return newTreeNode;
}

static void write_sorted_to_array_help(const BSTree tree, int* array, int* index) {
    if(tree == NULL) {
        return;
    }
    write_sorted_to_array_help(tree->left, array, index);
    array[(*index)++] = tree->data;
    write_sorted_to_array_help(tree->right, array, index);

}

/* Returnerar en dynamiskt allokerad array som innehåller trädets data sorterat */
static int* write_sorted_to_array(const BSTree tree)
{
    int n = number_of_nodes(tree);
    int * array = malloc(n* sizeof(int));
    if (array == NULL){
        return NULL;
    }
    int index = 0;
    write_sorted_to_array_help(tree, array, &index);
    return array;
    


     /*Skapa en dynamisk array med rätt storlek
    
    Skriv datat från trädet sorterat till arrayen (minsta till största)
       - till detta kanske du behöver en hjälpfunktion */
    
}


/* Bygger upp ett sorterat, balanserat träd från en sorterad array */
static void build_tree_sorted_from_array(BSTree* tree, const int arr[], int size) {
    *tree = NULL; // Clear the tree before rebuilding
    build_subtree(tree, arr, 0, size - 1);
}

void build_subtree(BSTree* tree, const int arr[], int start, int end) {
    if (start > end) {
        return;  // Base case: No more elements to insert
    }

    int mid = (start + end) / 2;
    insert_sorted(tree, arr[mid]);  // Insert middle element

    // Recursively build left and right subtrees
    build_subtree(tree, arr, start, mid - 1);  // Left subtree
    build_subtree(tree, arr, mid + 1, end);    // Right subtree
}



/* Implementation av trädet, funktionerna i interfacet */

/* Skapar ett tomt träd - denna funktion ar färdig */
BSTree create_empty_tree(void)
{
	return NULL;
}

/* Returnerar 1 ifall trädet är tomt, 0 annars */
int is_empty(const BSTree tree)
{
    if (tree == NULL) {
        return 1;
    }
    return 0;
}

/* Sätter in 'data' sorterat i *tree */
void insert_sorted(BSTree* tree, int data)
{   
   
        // Om vi når en NULL-nod, betyder det att vi har hittat rätt plats att infoga noden.
    if (*tree == NULL) {
        *tree = create_tree_node(data);  // Skapa den nya noden
        if (*tree == NULL) {
            return;  // Hantera minnesfel
        }
        return;  // Noden är nu insatt
    }

    // Om det nya data är mindre än den aktuella nodens data, gå till vänster
    if (data < (*tree)->data) {
        insert_sorted(&(*tree)->left, data);  // Rekursiv anrop till vänsterbarnet
    }
    // Om det nya data är större, gå till höger
    else if (data > (*tree)->data) {
        insert_sorted(&(*tree)->right, data);  // Rekursiv anrop till högerbarnet
    }
    if (data == (*tree)->data){
        return;
    }
    // Om data är lika med den aktuella nodens värde, gör inget (vi tillåter inte dubletter)
}
	/*Tänk på att trädet kan vara tomt vid insättning
    I vanliga fall kan man lösa dubletter på olika sätt. Eftersom vi vill att era lösningar
    fungerar likadant inför examinationen så bestämmer jag att dubletter ej ska tillåtas i trädet.
    Post-condition kan verifieras med hjälp av find(...)*/


/* Utskriftsfunktioner
Det räcker att ni implementerar LR-ordningarna*/
void print_preorder(const BSTree tree)
{   
    
    if (tree != NULL) {
        char buffer[10];
        sprintf(buffer, "%d ", tree->data);
        uarte_write(buffer, strlen(buffer));
        print_preorder(tree->left);
        print_preorder(tree->right);
    }
}

void print_inorder(const BSTree tree)
{
    if (tree != NULL) {
        print_inorder(tree->left);
        char buffer[10];
        sprintf(buffer, "%d ", tree->data);
        uarte_write(buffer, strlen(buffer));
        print_inorder(tree->right);
    }
}

void print_postorder(const BSTree tree)
{
    if (tree != NULL) {
        print_postorder(tree->left);
        print_postorder(tree->right);
        char buffer[10];
        sprintf(buffer, "%d ", tree->data);
        uarte_write(buffer, strlen(buffer));
        
    }
}

/* Returnerar 1 om 'data' finns i tree, 0 annars */
int find(const BSTree tree, int data)
{
    if (tree == NULL) {
        return 0;  // Tree is empty, data not found
    }

    if (data < tree->data) {
        return find(tree->left, data);  // Go left if data is smaller
    } else if (data > tree->data) {
        return find(tree->right, data);  // Go right if data is greater
    }
    else{
        return 1;
    }

      // Data is equal to the current node's data, return 1 (found)
}


/* Tar bort 'data' från trädet om det finns */
void remove_element(BSTree* tree, int data)
{
    if (*tree == NULL) {
        return;  // Base case: the tree is empty.
    }

    // Find the node to remove
    if (data < (*tree)->data) {
        remove_element(&(*tree)->left, data);
    } else if (data > (*tree)->data) {
        remove_element(&(*tree)->right, data);
    } else {
        // Node to delete found
        if ((*tree)->left == NULL && (*tree)->right == NULL) {
            // Case 1: No children (leaf node)
            free(*tree);
            *tree = NULL;
        } else if ((*tree)->left == NULL) {
            // Case 2: Only right child
            BSTree temp = *tree;
            *tree = (*tree)->right;
            free(temp);
        } else if ((*tree)->right == NULL) {
            // Case 3: Only left child
            BSTree temp = *tree;
            *tree = (*tree)->left;
            free(temp);
        } else {
            // Case 4: Two children
            BSTree temp = *tree;
            BSTree largestLeft = (*tree)->left;
            
            // Find the largest node in the left subtree
            while (largestLeft->right != NULL) {
                largestLeft = largestLeft->right;
            }
            
            // Replace current node with the largest node in the left subtree
            (*tree)->data = largestLeft->data;
            remove_element(&(*tree)->left, largestLeft->data);  // Recursively delete the largest left node
            free(temp);
        }
    }
}




/* Returnerar hur många noder som totalt finns i trädet */
int number_of_nodes(const BSTree tree)
{
    if (tree == NULL) {
        return 0;
    }
    else {
        return 1 + number_of_nodes(tree->left) + number_of_nodes(tree->right);
    }
    
}

/* Returnerar hur djupt trädet är */
int depth(const BSTree tree)
{
    if(tree == NULL) {
        return 0;
    }

    int left_depth = depth(tree->left);
    int right_depth = depth(tree->right);

    if(left_depth > right_depth) {
        return 1 + left_depth;
    }
    else {
        return 1 + right_depth;
    }
   
}

/* Returnerar minimidjupet för trädet
Se math.h för användbara funktioner*/
int min_depth(const BSTree tree)
{
    int tal = number_of_nodes(tree);
    
    int value = (int)ceil(log2(tal + 1));
    return value;
    
    

}

/* Balansera trädet så att depth(tree) == minDepth(tree) */
void balance_tree(BSTree* tree)
{   
   //char e[] = "1";
    //uarte_write(e, strlen(e));

    int size1 = number_of_nodes(*tree);
    int *arr1 = write_sorted_to_array(*tree);
    //char ee[] = "10";
   // uarte_write(ee, strlen(ee));
    
    

   // char f[] = "2";
    //uarte_write(f, strlen(f));

    if(arr1 == NULL) {
     return;
    }
        

        free_tree(tree);
        //char g[] = "3";
        //uarte_write(g, strlen(g));
        build_tree_sorted_from_array(tree, arr1, size1);
        //char j[] = "4";
        
        //uarte_write(j, strlen(j));          
        

        free(arr1);

        //char l[] = "6";
        //uarte_write(l, strlen(l));
    

   /* int size1 = number_of_nodes(*tree);
    int *arr = write_sorted_to_array(*tree);
    if(arr == NULL)return;
    free_tree(tree);
    build_tree_sorted_from_array(tree, arr, size1);
    free(arr);
*/    

    
/* Förslag på algoritm:
- överfor trädet till en dynamiskt allokerad array med writeSortedToArray()
- töm trädet med freeTree()
- bygg upp trädet rekursivt från arrayen med buildTreeSortedFromArray()
- frigör minne för den dynamiskt allokerade arrayen


Post-conditions:
- tree har lika många noder som tidigare
  - djupet för trädet är samma som minimumdjupet för trädet */
}


/* Töm trädet och frigör minnet för de olika noderna */
void free_tree(BSTree* tree)
{
    /*if(tree == NULL || *tree == NULL) {
        return;
    }
    else if((*tree)->left != NULL) {
        free_tree(&(*tree)->left);
    }
    else if((*tree)->right != NULL) {
        free_tree(&(*tree)->right);
    }

    free(*tree);
    *tree = NULL;*/
    if(tree != NULL && *tree != NULL) {
        if((*tree)->left != NULL){
            free_tree(&(*tree)->left);
          
        }
        if((*tree)->right != NULL){
            free_tree(&(*tree)->right);
           
        }
        
       
    } 
    free(*tree);
    *tree = NULL;
}


