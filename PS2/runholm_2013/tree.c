#include "tree.h"


#ifdef DUMP_TREES
void
node_print ( FILE *output, node_t *root, uint32_t nesting )
{
    if ( root != NULL )
    {
        fprintf ( output, "%*c%s", nesting, ' ', root->type.text );
        if ( root->type.index == INTEGER )
            fprintf ( output, "(%d)", *((int32_t *)root->data) );
        if ( root->type.index == VARIABLE || root->type.index == EXPRESSION )
        {
            if ( root->data != NULL )
                fprintf ( output, "(\"%s\")", (char *)root->data );
            else
                fprintf ( output, "%p", root->data );
        }
        fputc ( '\n', output );
        for ( int32_t i=0; i<root->n_children; i++ )
            node_print ( output, root->children[i], nesting+1 );
    }
    else
        fprintf ( output, "%*c%p\n", nesting, ' ', root );
}
#endif


node_t * node_init ( node_t *nd, nodetype_t type, void *data, uint32_t n_children, ... ) {
    (*nd).type = type;
    (*nd).data = data;
    (*nd).n_children = n_children;
    (*nd).children = (node_t**) malloc(n_children * sizeof(node_t));
    va_list args;
    va_start(args, n_children);
    for (int child = 0; child < n_children; child++) {
        (*nd).children[child] = va_arg(args, node_t*);
    }
    va_end(arguments);

}

void node_finalize ( node_t *discard ) {
    if(discard) {
        if((*discard).data) {
            free((*discard).data);
        }
    }
    free((*discard).children);
    free(discard);
}

void destroy_subtree ( node_t *discard ){
    if(discard) {
        for (int child=0;child<(*discard).n_children; child++) {
            destroy_subtree((*discard).children[child]);
        }
        node_finalize(discard);
    }
}

