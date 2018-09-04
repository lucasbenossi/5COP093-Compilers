#include "list.h"
#include "func_destroy_data.h"
#include <stdlib.h>

struct _list{
	struct _node *head;
	struct _node *tail;
	int size;
	func_destroy_data_t *destroy_data;
};

struct _node{
	void *data;
	struct _node *next;
	struct _node *previous;
};

/* ========================================================================== */

list_t *list_create(){
	list_t *list;
	list = malloc( sizeof(list_t) );
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	list->destroy_data = NULL;
	return list;
}

void list_destroy( list_t *list ){
	list_free(list);
	free(list);
}

void list_free( list_t *list ){
	node_t *node, *node0;
	void *data;

	node = list->head;
	while( node != NULL ){
	    node0 = node;
	    node = node->next;
	    data = node_destroy(node0);
	    if(list->destroy_data){
	        list->destroy_data(data);
	    }
	}

	list->destroy_data = NULL;
	list_reset(list);
}

void list_reset( list_t *list ){
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}

int list_lenght( list_t *list ){
	return list->size;
}

int list_is_empty( list_t *list ){
	return list->size == 0;
}

void list_set_func_destroy_data( list_t *list, func_destroy_data_t *destroy_data ){
	list->destroy_data = destroy_data;
}

node_t *list_insert( list_t *list, void *data ){
	node_t *node;

	node = node_create(data);

	if( list->head == NULL ){
	    list->head = node;
	    list->tail = node;
	}
	else{
	    list->tail->next = node;
	    node->previous = list->tail;
	    list->tail = node;
	}
	(list->size)++;
	return node;
}

node_t *list_insert_first( list_t *list, void *data ){
	node_t *node = node_create(data);

	if(!list->head){
		list->head = node;
		list->tail = node;
	}
	else{
		list->head->previous = node;
		node->next = list->head;
		list->head = node;
	}
	(list->size)++;
	return node;
}

node_t *list_insert_before( list_t *list, node_t *node, void *data ){
	node_t *newNode, *previousNode;

	newNode = NULL;

	if( node != NULL ){
	    newNode = node_create(data);
	    previousNode = node->previous;
	    if( previousNode == NULL ){
	        list->head = newNode;
	    }
	    else{
	        previousNode->next = newNode;
	        newNode->previous = previousNode;
	    }
	    newNode->next = node;
	    node->previous = newNode;
	    (list->size)++;
	}
	return newNode;
}

node_t *list_insert_after( list_t *list, node_t *node, void *data ){
	node_t *newNode, *nextNode;

	newNode = NULL;

	if( node != NULL ){
	    newNode = node_create(data);
	    nextNode = node->next;
	    if( nextNode == NULL ){
	        list->tail = newNode;
	    }
	    else{
	        nextNode->previous = newNode;
	        newNode->next = nextNode;
	    }
	    newNode->previous = node;
	    node->next = newNode;
	    (list->size)++;
	}
	return newNode;
}

void *list_remove_fisrt( list_t *list ){
	void *data;
	node_t *node;

	data = NULL;

	if( list->head != NULL ){
	    node = list->head;
	    if( list->head == list->tail ){
	        list->head = NULL;
	        list->tail = NULL;
	    }
	    else{
	        list->head = list->head->next;
	        list->head->previous = NULL;
	    }
	    data = node_destroy(node);
	    (list->size)--;
	}
	return data;
}

void *list_remove_last( list_t *list ){
	void *data;
	node_t *node;

	data = NULL;

	if( list->tail != NULL ){
	    node = list->tail;
	    if( list->tail == list->head ){
	        list->tail = NULL;
	        list->head = NULL;
	    }
	    else{
	        list->tail = list->tail->previous;
	        list->tail->next = NULL;
	    }
	    data = node_destroy(node);
	    (list->size)--;
	}
	return data;
}

void *list_remove( list_t *list, node_t *node ){
	void *data = NULL;

	if( node != NULL ){
	    if( node->previous == NULL ){
	        list->head = node->next;
	    }
	    else{
	        node->previous->next = node->next;
	    }
	    if( node->next == NULL ){
	        list->tail = node->previous;
	    }
	    else{
	        node->next->previous = node->previous;
	    }
	    data = node_destroy(node);
	    (list->size)--;
	}
	return data;
}

node_t *list_get_first( list_t *list ){
	return list->head;
}

node_t *list_get_last( list_t *list ){
	return list->tail;
}

/* ========================================================================== */

node_t *node_create( void *data ){
	node_t *node;
	node = malloc( sizeof( node_t ) );
	node->data = data;
	node->next = NULL;
	node->previous = NULL;
	return node;
}

void *node_destroy( node_t *node ){
	void *data;
	data = node_get_data(node);
	free(node);
	return data;
}

node_t *node_get_next( node_t *node ){
	return node->next;
}

node_t *node_get_previous( node_t *node ){
	return node->previous;
}

void *node_get_data( node_t *node ){
	return node->data;
}
