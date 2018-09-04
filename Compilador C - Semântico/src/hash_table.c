#include "hash_table.h"
#include "list.h"
#include "string.h"
#include "func_destroy_data.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct _hashtable{
	int size;
	int counter;
	list_t **array;
	func_destroy_data_t *destroy_data;
};

struct _iterator{
	hash_table_t *table;
	int i, j;
	node_t *current, *next;
};

struct _entry{
	char *key;
	void *data;
};
typedef struct _entry entry_t;

static int hash_key( hash_table_t *table, char *key );

static list_t **get_list( hash_table_t *table, int i );

static node_t *search_node_key( list_t *list, char *key );

static node_t *search_node_data( list_t *list, void *data );

static entry_t *entry_create( char *key, void *data );

static void *entry_destroy( entry_t *entry );

static void get_next_node( iterator_t *iterator );

/* ========================================================================== */

static int hash_key( hash_table_t *table, char *key ){
	int N, i, sum;
	static const int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113 };
	static const int Nprimes = sizeof(primes) / sizeof(primes[0]);

	sum = 0;
	N = strlen(key);
	if( N > Nprimes ){
		N = Nprimes;
	}
	for( i = 0; i < N; i++ ){
		sum += primes[i] * (int)key[i];
	}

	return sum % table->size;
}

static list_t **get_list( hash_table_t *table, int i ){
	return &table->array[i];
}

static node_t *search_node_key( list_t *list, char *key ){
	node_t *node;
	for( node = list_get_first(list); node != NULL; node = node_get_next(node) ){
		entry_t *entry = node_get_data(node);
		if( strcmp( key, entry->key ) == 0 ){
			break;
		}
	}
	return node;
}

static node_t *search_node_data( list_t *list, void *data ){
	node_t *node;
	for( node = list_get_first(list); node; node = node_get_next(node) ){
		entry_t *entry = node_get_data(node);
		if( data == entry->data ){
			break;
		}
	}
	return node;
}

static entry_t *entry_create( char *key, void *data ){
	entry_t *entry;
	entry = malloc(sizeof(entry_t));
	entry->key = string_create(key);
	entry->data = data;
	return entry;
}

static void *entry_destroy( entry_t *entry ){
	void *data;
	string_destroy(entry->key);
	data = entry->data;
	free(entry);
	return data;
}

/* ========================================================================== */

hash_table_t *hash_table_create( int size ){
	hash_table_t *table;
	int i;

	if( size < 1 ) return NULL;

	table = malloc(sizeof(hash_table_t));
	table->size = size;
	table->counter = 0;
	table->array = malloc( size * sizeof(list_t*) );
	for( i = 0; i < size; i++ ){
		table->array[i] = NULL;
	}
	table->destroy_data = NULL;
	return table;
}

void hash_table_destroy( hash_table_t *table ){
	hash_table_free(table);
	free(table->array);
	free(table);
}

void hash_table_free( hash_table_t *table ){
	int i;
	list_t **list;

	for( i = 0; i < table->size; i++ ){
		list = get_list(table, i);
		if(*list){
			while(!list_is_empty(*list)){
				void *data = entry_destroy(list_remove_fisrt(*list));
				if(table->destroy_data){
					table->destroy_data(data);
				}
			}
			list_destroy(*list);
			*list = NULL;
		}
	}
	table->counter = 0;
	table->destroy_data = NULL;
}

int hash_table_insert( hash_table_t *table, char *key, void *data ){
	list_t **list = get_list( table, hash_key( table, key ) );
	if( *list && search_node_key( *list, key ) ){
		return 1;
	}
	table->counter++;
	if(!*list){
		*list = list_create();
	}
	list_insert( *list, entry_create( key, data ) );

	return 0;
}

void *hash_table_remove( hash_table_t *table, char *key, void *data ){
	list_t **list;
	node_t *node;

	list = get_list( table, hash_key( table, key ) );
	if(*list){
		if(data){
			node = search_node_data(*list, data);
		}
		else{
			node = search_node_key(*list, key);
		}
		if(node){
			entry_t *entry = list_remove(*list, node);
			table->counter--;
			if(list_is_empty(*list)){
				list_destroy(*list);
				*list = NULL;
			}
			return entry_destroy(entry);
		}
	}
	return NULL;
}

void *hash_table_search( hash_table_t *table, char *key ){
	list_t *list = *get_list(table, hash_key(table, key));
	if(list){
		node_t *node = search_node_key(list, key);
		if( node != NULL ){
			entry_t *entry = node_get_data(node);
			return entry->data;
		}
	}
	return NULL;
}

void hash_table_set_func_destroy_data( hash_table_t *table, func_destroy_data_t *destroy_data ){
	table->destroy_data = destroy_data;
}

int hash_table_get_size( hash_table_t *table ){
	return table->size;
}

int hash_table_get_counter( hash_table_t *table ){
	return table->counter;
}

int hash_table_is_empty( hash_table_t *table ){
	return table->counter == 0;
}

/* ========================================================================== */

static void get_next_node( iterator_t *iterator ){
	while( iterator->j < iterator->table->size ){
		list_t *list = *get_list(iterator->table, iterator->j);
		if(list){
			iterator->next = list_get_first(list);
			return;
		}
		iterator->j++;
	}
}

iterator_t *iterator_create( hash_table_t *table ){
	iterator_t *iterator;
	iterator = malloc(sizeof(iterator_t));
	iterator->table = table;
	iterator->current = NULL;
	iterator->i = 0;
	iterator->next = NULL;
	iterator->j = 0;
	get_next_node(iterator);
	return iterator;
}

void iterator_destroy( iterator_t *iterator ){
	free(iterator);
}

int iterator_has_next( iterator_t *iterator ){
	return ! (iterator->next == NULL);
}

void *iterator_next( iterator_t *iterator ){
	iterator->current = iterator->next;
	iterator->i = iterator->j;

	if( iterator->next ){
		iterator->next = node_get_next(iterator->next);
		if( iterator->next == NULL ){
			iterator->j++;
			get_next_node(iterator);
		}
	}

	if( iterator->current != NULL ){
		entry_t *entry = node_get_data(iterator->current);
		return entry->data;
	}
	return NULL;
}

char *iterator_get_key( iterator_t *iterator ){
	if( iterator->current != NULL ){
		entry_t *entry = node_get_data(iterator->current);
		return entry->key;
	}
	return NULL;
}

void iterator_remove( iterator_t *iterator ){
	if( iterator->current != NULL ){
		entry_destroy( list_remove( *get_list( iterator->table, iterator->i ), iterator->current ) );
		iterator->current = NULL;
		iterator->i = 0;
	}
}

int iterator_get_i( iterator_t *iterator ){
	return iterator->i;
}

int iterator_get_j( iterator_t *iterator ){
	return iterator->j;
}
