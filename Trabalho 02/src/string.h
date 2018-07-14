#ifndef STRING_H
#define STRING_H

char *create_string( const char *string );

void destroy_string( char *string );
void destroy_string_void( void *string );

char *alloc_char( int size );

char *create_string_cat( int n, ... );
void cat_string( char **s, const char *c );
void rep_string( char **s, const char *c );

#endif
