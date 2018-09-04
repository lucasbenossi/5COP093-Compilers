#ifndef STRING_H
#define STRING_H

char *string_create( const char *string );

void string_destroy( char *string );
void string_destroy_void( void *string );

char *alloc_char( int size );

char *string_create_cat( int n, ... );
void string_cat( char **s, const char *c );
void string_rep( char **s, const char *c );

#endif
