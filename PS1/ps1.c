#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum { false, true } bool;

// A struct for tree nodes, with pointers to the parent and child nodes
// and a int to store the value at the node.
typedef struct Node{
    struct Node* left;
    struct Node* right;
    int value;
} Node;


// Returns a random number between 0 and n
// For simplicity, the random number generator is not seeded,
// hence the same random numbers will be generated on every execution
int get_random_number(int n){
    return rand() % n;
}


// Return a (dynamically allocated) array of length size,
// filled with random numbers between 0 and n
int* create_random_array(int size, int n){
    int* array = calloc(size, sizeof(int));
    int i = 0;
    for(i=0;i<size;i++) {
        array[i] = get_random_number(n);
        array[i];
    }
    return array;
}


// Should print the contents of array of lenght size
void print_array(int* array, int size){
    int i = 0;
    for(i=0;i<size-1;i++) {
        printf("%d, ",array[i]);
    }
    printf("%d\n",array[size-1]);
}

// Compare funcrion for the sort
int compare_integer(const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}

// Should sort the numbers in array in increasing order
void sort(int* array, int size){
    qsort(array, size, sizeof(int), compare_integer);
}


// Inserts the node into the tree rooted at the node pointed to by root
void insert_node(Node** root, Node* node){
    int depth = 0;
    while(true) {
        //if(insert_node_at_depth(*root, *node, depth))
            break;
        depth++;
    }
}

bool insert_node_at_depth(Node* root, Node* node, int max_depth) {
    if(max_depth==0) {
        if(root==NULL) {
            *root = *node;
            return true;
        }
    } else {
        if(insert_node_at_depth((root->left), node, max_depth-1))
            return true;
        if(insert_node_at_depth((root->right), node, max_depth-1)) 
            return true;
        return false;
    }
}


// Searches for the number n in the tree rooted at root.
// Should return 1 if the number is present, and 0 if not.
int search(Node* root, int n){
    if(root->left != NULL) 
        if(search(root->left, n))
            return 1;
    if(root->right != NULL) 
        if(search(root->right, n))
            return 1;
    return root->value==n;
}


// Returns a dynamically allocated node, with all fields set to NULL/0
Node* create_blank_node(){
    struct Node* node = (struct Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    node->value = 0;
}


// Builds a tree of all the numbers in an array
Node* create_tree(int* array, int size){
    struct Node* root = malloc(sizeof(Node));
    int i;
    for(i=0;i<size;i++) {
        struct Node* new_node = create_blank_node();
        new_node->value = array[i];
        //printf("Inserting node with value %d\n", array[i]);
        insert_node(&root, new_node);
    }
    return root;
}


// Prints all the nodes of the tree.
// Assuming non-NULL root node
void print_tree(Node* n, int offset){
    int i;
    for(i=0;i<offset;i++) {
        printf(" ");
    }
    printf("%d\n", n->value);
    if(n->left != NULL) {
        print_tree(n->left, offset+1);
    }
    if(n->right != NULL) {
        print_tree(n->right, offset+1);
    }
}


// Computes x^2
double x_squared(double x){
    return x*x;
}


// Computes x^3
double x_cubed(double x){
    return x*x*x;
}


// Computes the definite integral of the function using the rectangle method
double integrate(double (*function)(double), double start, double end, double stepsize){
    int n = (end-start)/stepsize;
    double sum = 0.0;
    int i;
    for(i=0;i<n;i++) {
        double x = start + i*stepsize;
        sum += (*function)(x); 
    }
    return sum*stepsize;
}


int main(int argc, char** argv){

    // Creates an array with random values
    int* array = create_random_array(10, 10);

    // Prints the values of the array, e.g:
    // 3 6 7 5 3 5 6 2 9 1
    print_array(array, 10);

    // Sorts the array
    sort(array, 10);

    // Prints the sorted array, e.g:
    // 1 2 3 3 5 5 6 6 7 9
    print_array(array, 10);

    // Create another random array
    int* new_array = create_random_array(10,10);

    // Print the second array
    print_array(new_array, 10);

    // Create a tree with the values in the new array
    Node* root = create_tree(new_array, 10);

    // Print the tree
    print_tree(root, 0);

    // Search for the values 3 and 11 in the tree
    // and print the results
    int found_3 = search(root, 3);
    int found_11 = search(root, 11);
    printf("%d, %d\n", found_3, found_11);

    // Integrate x^2 and x^3 from 0 to 1.
    // Should be approx 1/3 and 1/4.
    printf("%f\n", integrate(&x_squared, 0, 1, 0.001));
    printf("%f\n", integrate(&x_cubed, 0, 1, 0.001));
}




