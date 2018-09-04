#include "string.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

char *string_create( const char *string ){
	char *string0;
	int size;

	if( string == NULL ) return NULL;

	size = strlen(string);
	if( size > 0 ){
	    string0 = alloc_char( size );
	    strcpy(string0,string);
	}
	else{
	    string0 = alloc_char(0);
	}

	return string0;
}

void string_destroy( char *string ){
	if( string ){
	    free(string);
	}
}

void string_destroy_void( void *string ){
	string_destroy((char*)string);
}

char *alloc_char( int size ){
	char *string;
	int i;

	size = size + 1;
	string = (char*)malloc( size * sizeof(char) );

	for(i = 0; i < size; i++){
	    *(string+i) = '\0';
	}

	return string;
}

char *string_create_cat( int n, ... ){
	va_list args;
	char *string;
	const char *arg;
	int size, i;

	if( n == 0 ) return NULL;

	size = 0;

	va_start(args,n);
	for( i = 0; i < n; i++){
	    arg = va_arg(args, const char*);
	    if( arg != NULL ){
	        size += strlen( arg );
	    }
	}
	va_end(args);

	if( size > 0 ){
	    string = alloc_char(size);
	    va_start(args,n);
	    for( i = 0; i < n; i++){
	        arg = va_arg(args, const char*);
	        if( arg != NULL ){
	            strcat( string, arg );
	        }
	    }
	    va_end(args);
	}
	else{
	    string = alloc_char(0);
	}

	return string;
}

void string_cat( char **s, const char *c ){
	int sizeC, sizeS;
	char *newS;

	if( c != NULL ){
	    sizeC = strlen(c);
	    if( *s != NULL ){
	        if( sizeC > 0 ){
	    		sizeS = strlen(*s);
	    		newS = alloc_char( sizeS + sizeC );
	    		strcpy(newS, *s);
	    		strcat(newS, c);
	    		string_destroy(*s);
	    		*s = newS;
	    	}
	    }
	    else{
	        if( sizeC > 0 ){
	            *s = string_create(c);
	        }
	        else{
	            *s = alloc_char(0);
	        }
	    }
	}
}

void string_rep( char **s, const char *c ){
	string_destroy(*s);
	*s = string_create(c);
}
