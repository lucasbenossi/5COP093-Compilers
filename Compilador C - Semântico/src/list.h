#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "func_destroy_data.h"

typedef struct _list list_t;

typedef struct _node node_t;


/* ================================================================================================================ */

list_t *list_create();

void list_destroy( list_t *list );

void list_free( list_t *list );

void list_reset( list_t *list );

int list_lenght( list_t *list );

int list_is_empty( list_t *list );

void list_set_func_destroy_data( list_t *list, func_destroy_data_t *destroyData );

node_t *list_insert( list_t *list, void *data );
node_t *list_insert_first( list_t *list, void *data );

node_t *list_insert_before( list_t *list, node_t *node, void *data );

node_t *list_insert_after( list_t *list, node_t *node, void *data );

void *list_remove_fisrt( list_t *list );

void *list_remove_last( list_t *list );

void *list_remove( list_t *list, node_t *node );

node_t *list_get_first( list_t *list );

node_t *list_get_last( list_t *list );

/* ================================================================================================================ */

node_t *node_create( void *data );

void *node_destroy( node_t *node );

void *node_get_data( node_t *node );

node_t *node_get_next( node_t *node );

node_t *node_get_previous( node_t *node );

#endif
