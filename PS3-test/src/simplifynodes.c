#include "simplifynodes.h"

extern int outputStage; // This variable is located in vslc.c
/*
 * These three lines would normally be in the header file, but they are here because
 * we were asked to only deliver the .c file.
 */
void simplify_children( Node_t *root, int depth );
void remove_the_n_first_children( Node_t *root, int n);
void simplify_single_child_helper( Node_t *root);

/*
 * The default for a node that doesn't require any special actions is to call all their childrens simplify functions.
 */
Node_t* simplify_default ( Node_t *root, int depth )
{
    simplify_children(root, depth);
}

/*
 * The base_type and class_name childrens base_type and class_name are moved to the parrent and the children are destroyed.
 * The remaining children is moved to a new children array of a smaller size.
 */
Node_t *simplify_types ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    if(root->data_type.base_type == CLASS_TYPE) {
        root->data_type.class_name = root->children[0]->label;
        remove_the_n_first_children(root, 1);
    }
}


/*
 * The label and data_type childrens label and data_type are moved to the parrent and the children are destroyed.
 * The remaining children is moved to a new children array of a smaller size.
 */
Node_t *simplify_function ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    root->data_type = root->children[0]->data_type;
    root->label = root->children[1]->label;
    remove_the_n_first_children(root, 2);
}


/*
 * The label childs label is moved to the parrent and the child is destroyed.
 * The remaining children is moved to a new children array of a smaller size.
 */
Node_t *simplify_class( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    root->label = root->children[0]->label;
    free(root->children[0]);
    Node_t** newChildren = malloc((root->n_children-1) * sizeof(Node_t));
    int i=0;
    for(i=0;i<(root->n_children-1);i++) {
        newChildren[i] = root->children[i+1];
    }
    free(root->children);
    root->children = newChildren;
    root->n_children = root->n_children-1;
}


/*
 * The data type and label children have their properties moved to the parrent before being destroyed. 
 * The remaining children is moved to a new children array of a smaller size.
 */
Node_t *simplify_declaration_statement ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    root->data_type = root->children[0]->data_type;
    root->label = root->children[1]->label;
    remove_the_n_first_children(root, 2);
}


/*
 * Move the only child up one level to replace it's parrent
 */
Node_t *simplify_single_child ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    simplify_single_child_helper(root);
}

/*
 * There are two cases for lists with potential NULL. If their first child is NULL
 * the NULL child is simply removed and the remaining child is made to be the only child.
 * Else there children of the non-terminal children is hoisted up one level in the three.
 */
Node_t *simplify_list_with_null ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);

    if(root->children[0]==NULL) {
        Node_t* nonNullChild = root->children[1];
        free(root->children);
        root->children = malloc(sizeof(Node_t));
        root->children[0] = nonNullChild;
        root->n_children = root->n_children-1;
    } else if(root->children[0]->nodetype.index==root->nodetype.index) {
        Node_t** newChildren = malloc((root->children[0]->n_children+1) * sizeof(Node_t));
        int i=0;
        for(i=0;i<(root->children[0]->n_children+1);i++) {
            newChildren[i] = root->children[0]->children[i];
        }
        newChildren[root->children[0]->n_children] = root->children[1];
        root->n_children = root->children[0]->n_children+1;
        free(root->children);
        root->children = newChildren;
    }
}


/*
 * All list with 2 children are simplified by setting all the children of the 1st child to be direct children.
 */
Node_t *simplify_list ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s \n", depth, ' ', root->nodetype.text );
    simplify_children(root, depth);
    if(root->n_children==2) {
        Node_t** newChildren = malloc((root->children[0]->n_children+1) * sizeof(Node_t));
        int i=0;
        for(i=0;i<(root->children[0]->n_children+1);i++) {
            newChildren[i] = root->children[0]->children[i];
        }
        newChildren[root->children[0]->n_children] = root->children[1];
        root->n_children = root->children[0]->n_children+1;
        free(root->children);
        root->children = newChildren;
    }
}

/*
 * Most expressions does not require simplification, but the ones that do are simplified here.
 */
Node_t *simplify_expression ( Node_t *root, int depth )
{
    if(outputStage == 4)
        fprintf ( stderr, "%*cSimplify %s (%s) \n", depth, ' ', root->nodetype.text, root->expression_type.text );
    simplify_children(root, depth);
    if(root->expression_type.index==DEFAULT_E || root->expression_type.index==CONSTANT_E || root->expression_type.index==VARIABLE_E) {
        simplify_single_child_helper(root);
    }

}

/*
 * Call the simplify function on each of the children recursivly down until a leafnode or NULL node is found.
 */
void simplify_children(Node_t *root, int depth) {
    int i;
    for(i=0;i<root->n_children;i++) {
        if(root->children[i]!=NULL) {
            root->children[i]->simplify(root->children[i], depth+1);
        }
    }
}

/*
 * Remove the first n children from the children array and move the remaining children into a new smaller array.
 */
void remove_the_n_first_children( Node_t *root, int n) {
    Node_t** newChildren = malloc((root->n_children-n) * sizeof(Node_t));
    int i=0;
    for(i=0;i<(root->n_children-n);i++) {
        free(root->children[i]);
        newChildren[i] = root->children[i+2];
    }
    free(root->children);
    root->children = newChildren;
    root->n_children = root->n_children-2;
}

/*
 *
 */
void simplify_single_child_helper( Node_t *root) {
    Node_t* child = root->children[0];
    free(root->children);
    *root = *child;
}
