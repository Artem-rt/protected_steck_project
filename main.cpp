// stack_and_protection --- project about stack with a lot of protections

//DEBUG-MODE OFF-----------------------------------------------
// #define DEBAG_OFF
// -----------------------------------------------------------

// useful libraries-------------------------------------------
#include "stack.h"                                            // our library for safe working with stack
#include <stdio.h>                                            // for standart input/output func.
#include <assert.h>                                           // for assert-protection
#include <stdlib.h>                                           // for calloc & realloc
#include "stack_func.cpp"                                     // our functions bodyes
// -----------------------------------------------------------

// main func.-------------------------------------------------
int main ()
{
    // variables and etc.-------------------------------------
    struct Stack stack_one = {} ;                             // our stack structure
    Error_Codes error_returned = NO_ERROR;                    // error's codes returned from func.
    TYPE_OF_STACK_ELEM var_one = 10, var_two = 20;            // data pushing to stack_one
    TYPE_OF_STACK_ELEM pop_elem = 0;                          // our element poped from steck
    int stack_length = 5;                                     // length of creating stack
    // -------------------------------------------------------

    // working area------------------------------------------
    if ( ( error_returned = stack_init (&stack_one, stack_length IF_ON_DEBAG(,
                                                                                "stack_one",
                                                                                "main()",
                                                                                __FILE__,
                                                                                __LINE__)    ) ) != NO_ERROR)
        decode_the_error_code_enum (&error_returned);

    if ((error_returned = stack_push (&stack_one, var_one)) != NO_ERROR)
        decode_the_error_code_enum (&error_returned);

    if ((error_returned = stack_push (&stack_one, var_two)) != NO_ERROR)
        decode_the_error_code_enum (&error_returned);

    if ((error_returned = stack_pop (&stack_one, &pop_elem)) != NO_ERROR)
        decode_the_error_code_enum (&error_returned);

    printf ("pop_elem = " SPECIFICATOR_TYPE, pop_elem);

    stack_destroy (&stack_one);

    return 0;
}
// -----------------------------------------------------------

// THE END----------------------------------------------------
