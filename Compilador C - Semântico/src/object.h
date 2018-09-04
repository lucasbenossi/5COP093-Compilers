#ifndef OBJECT_H
#define OBJECT_H

typedef enum object_type_e {
	OBJECT_LIST,
	OBJECT_NODE,
	OBJECT_HASH_TABLE,
	OBJECT_ITERATOR,
	OBJECT_AST_EXP_PRIMARIA
} object_type_t;

typedef struct object_type_s {
	object_type_t type;
} object_t;

#endif
