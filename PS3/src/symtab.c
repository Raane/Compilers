#include "symtab.h"
#include <stdlib.h>

// These variables is located in vslc.c
extern int arch;
extern int outputStage; 

static char **strings;
static int strings_size = 16, strings_index = -1;

/*
 * Initialize the variables and create the table we will use to store the strings.
 */
void symtab_init ( void )
{
    strings_size=0;
    strings_index=-1;
    strings = malloc(0);
}

/*
 * Free all memory used for the data structures used to store the strings.
 */
void symtab_finalize ( void )
{
    int i;
    for(i=0;i<strings_size;i++) {
        free(strings[i]);
    }
    free(strings);
}

/*
 * Expand the array with the strings and add the new one.
 * Please note that if there was a risk of really large abounts of strings 
 * we should probably expand the array by many places every time it is necessary.
 * I do however not believe that anyone will ever have a vsl program that is so large 
 * that this extra time consumption of the compiler will be an issue.
 */
int strings_add ( char *str )
{
    strings_index++;
    char **newStrings = malloc((strings_index+1) * 32);
    int i;
    for(i=0;i<strings_size+1;i++) {
        newStrings[i] = strings[i];
    }
    newStrings[strings_size] = str;
    free(strings);
    strings = newStrings;
    strings[strings_index] = str;
    if(outputStage == 7)
        fprintf ( stderr, "Add strings (%s), index: %d \n", str, strings_index );
    strings_size++;

    
}

// Prints the data segment of the assembly code
// which includes all the string constants found
// ARM and x86 have different formats
void strings_output ( FILE *stream )
{
    if(arch == 1) { //ARM
    	 fputs (
			".syntax unified\n"
			".cpu cortex-a15\n"
			".fpu vfpv3-d16\n"
			".data\n"
			".align	2\n"
			".DEBUG: .ascii \"Hit Debug\\n\\000\"\n"
			".DEBUGINT: .ascii \"Hit Debug, r0 was: %d\\n\\000\"\n"
		    ".INTEGER: .ascii \"%d \\000\"\n"
			".FLOAT: .ascii \"%f \\000\"\n"
			".NEWLINE: .ascii \"\\n \\000\"\n",
		    stream
		);
		for ( int i=0; i<=strings_index; i++ ) {
		    fprintf ( stream, ".STRING%d: .ascii %s\n", i, strings[i] );
		    fprintf ( stream, ".ascii \"\\000\"\n", i, strings[i] ); // ugly hack
		}
		fputs ( ".globl main\n", stream );
		fputs ( ".align	2\n", stream );
    }
    else { //x86
		fputs (
		    ".data\n"
		    ".INTEGER: .string \"%d \"\n"
			".FLOAT: .string \"%f \"\n"
			".NEWLINE: .string \"\\n \"\n",
		    stream
		);
		for ( int i=0; i<=strings_index; i++ )
		    fprintf ( stream, ".STRING%d: .string %s\n", i, strings[i] );
		fputs ( ".globl main\n", stream );
    }
}

