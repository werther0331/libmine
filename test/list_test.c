#include <stdio.h>

#include "../include/mlist.h"

struct entry_list
{
    int i;
    struct list_node node;
};

int main ( int argc , char ** argv )
{
    struct entry_list *head  = malloc( sizeof (struct entry_list) );

    head->i = 0;
    M_INIT_LIST_HEAD( &(head->node) );

    int i = 0;
    for ( i = 1; i < 10; i++ ) {
        struct entry_list * node = malloc( sizeof( struct entry_list) );
        node->i = i;
        mlist_add_tail( &(node->node) , (head->node).prev );
    }

    struct list_node * pos = NULL;
    struct list_node * pnext = NULL;
    list_for_each_safely( pos, pnext, &(head->node) ) {
        struct entry_list * list = list_entry( pos, struct entry_list, node );
        printf("%d\n", list->i );
        free(list);
    }

    free(head);
}
