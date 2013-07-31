/**
 * This if the common interface for double linked list.
 * based on list.h from e2fsprogs
 */

#ifndef COMMON_MLIST_H
#define COMMON_MLIST_H


struct list_node  // double linkded list node 
{
    struct list_node * next, *prev;
};

/**
 * init the ptr as the head of a list, the head is empty.
 * @ptr,  the list_node
 */
#define M_INIT_LIST_HEAD(ptr) do \
    { \
    (ptr)->next = (ptr); \
    (ptr)->prev = (ptr); \
    } while(0)


/**
 * Insert the node @add between the node prev and next
 * @add,  the node to add.
 * @prev, the node before @add after insertion.
 * @next, the node after @add after insertion.
 */
static inline void __mlist_add( struct list_node * add, 
                                struct list_node * prev ,
                                struct list_node * next )
{
    prev->next = add;
    next->prev = add;
    add->prev = prev;
    add->next = next;
}

/**
 * Insert @add before @node
 * @add,  the list_node to be inserted
 * @node, the list_node after @add after insertion.
 */
static inline void mlist_add_ahead( struct list_node * add,
                                    struct list_node * node )
{
    __mlist_add( add, node->prev, node );
}

/**
 * Insert @add after @node
 * @add,  the list_node to be inserted
 * @node, the list_node after @add after insertion
 */
static inline void mlist_add_tail( struct list_node * add,
                                   struct list_node * node )
{
    __mlist_add( add, node, node->next );
}

/**
 * Delete the node between @prev and @next
 * @prev,  the list_node before the node to be deleted
 * @next,  the list_node after the node to be deleted
 */
static inline void __mlist_delete( struct list_node * prev, 
                                   struct list_node * next )
{
    prev->next = next;
    next->prev = prev;
}

/**
 * Delete node @del
 * @del,  the list_node to be deleted
 */
static inline void mlist_delete( struct list_node * del )
{
    __mlist_delete( del->prev, del->next );
}

/**
 * Check whether the list is empty.
 * @head,  the head of the list
 */
static inline int mlist_is_empty( struct list_node * head )
{
    return ( head->next == head );
}

/**
 * Check whether the node is the tail of a list.
 * @head, the head of a specify list.
 * @node, the node to be cheked.
 */
static inline int mlist_is_tail( struct list_node * head, 
                                 struct list_node * node )
{
    return ( head->prev == node );
}

#define list_entry( ptr, type, member ) \
    ( (type *)( (char *)(ptr) - (unsigned long)( &((type*)(0))->member ) ) )

#define list_for_each_safely( pos, pnext, head  )\
    for( pos = (head)->next , pnext = pos->next; pos != (head); pos = pnext, pnext = pos->next )


#endif
