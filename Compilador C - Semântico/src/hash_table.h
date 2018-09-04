#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "list.h"
#include "func_destroy_data.h"

#define HT_SIZE_SMALL 13
#define HT_SIZE 97
#define HT_SIZE_LARGE 997

typedef struct hash_table_s hash_table_t;

typedef struct iterator_s iterator_t;

/* ========================================================================== */

hash_table_t *hash_table_create( int size );

void hash_table_destroy( hash_table_t *table );
void hash_table_free( hash_table_t *table );

int hash_table_insert( hash_table_t *table, char *key, void *data );

void *hash_table_remove( hash_table_t *table, char *key, void *data );

void *hash_table_search( hash_table_t *table, char *key );

void hash_table_set_func_destroy_data( hash_table_t *table, func_destroy_data_t *destroyData );

int hash_table_size( hash_table_t *table );
int hash_table_counter( hash_table_t *table );
int hash_table_is_empty( hash_table_t *table );

/* ========================================================================== */

/*

iterator_t *iterator = createIterator(table);
while( iteratorHasNext(iterator) ){
	void *data = iteratorNext(iterator);
	char *key = iteratorKey(iterator);
	iteratorRemove(iterator);
}
destroyIterator(iterator);

*/

iterator_t *iterator_create( hash_table_t *table );
void iterator_destroy( iterator_t *iterator );

int iterator_has_next( iterator_t *iterator );
void *iterator_next( iterator_t *iterator );

char *iterator_get_key( iterator_t *iterator );

void iterator_remove( iterator_t *iterator );

int iterator_get_i( iterator_t *iterator );
int iterator_get_j( iterator_t *iterator );

#endif
