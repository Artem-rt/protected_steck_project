// stack_func.cpp - it includes, why our stack work safely

// include guards-------------------------------------
#ifndef STACK_FUNC_CPP
#define STACK_FUNC_CPP
// ---------------------------------------------------

// useful libraries---------------------------------------
#include "stack.h"                                        // our library for safe working with stack
#include <stdio.h>                                        // for standart input/output func.
#include <assert.h>                                       // for assert-protection
#include <stdlib.h>                                       // for calloc & realloc
#include <math.h>                                         // for fabs() for compare doubles
// -------------------------------------------------------

// function ----------------------------------------------
Error_Codes stack_init (struct Stack* stack_i, int stack_length IF_ON_DEBAG(,
                                                                                const char* name,
                                                                                const char* func,
                                                                                const char* file,
                                                                                int line)        )
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------


    // working area----------------------------------------
    if (stack_length == 0) printf (VIOLET_START "WARNING: you want to create 0-size stack!!!" COLOR_STOP);

    stack_i -> size = 0;
    stack_i -> capacity = stack_length;

    IF_ON_DEBAG(
        stack_i -> name = name;
        stack_i -> func = func;
        stack_i -> file = file;
        stack_i -> line = line;
    )

    stack_i -> data = (TYPE_OF_STACK_ELEM*)calloc (stack_length, sizeof (TYPE_OF_STACK_ELEM));

    for (int i = 0; i < stack_i -> capacity; i++)
    {
        stack_i -> data [i] = 0xDED;
    }
    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
    )

    assert (!error);

    return error;
    // ----------------------------------------------------
}

Error_Codes stack_push (struct Stack* stack_i, TYPE_OF_STACK_ELEM var)
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------


    // working area----------------------------------------
    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
    )

    assert (!error);


    if (stack_i -> size == stack_i -> capacity)
    {
        stack_real_up_capacity (stack_i);
    }

    stack_i -> data [stack_i -> size] = var;


    stack_i -> size ++ ;

    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
    )

    assert (!error);


    return error;
    // ----------------------------------------------------
}

Error_Codes stack_pop (struct Stack* stack_i, TYPE_OF_STACK_ELEM* pop_elem)
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------


    // working area----------------------------------------
    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
    )

    assert (!error);


    *pop_elem = stack_i -> data [stack_i -> size - CORRECTION_SIZE_FOR_DATA_INDEX];
    stack_i -> size -- ;

    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
    )

    assert (!error);

    return error;
    // ----------------------------------------------------
}

void decode_the_error_code_enum (Error_Codes* error_returned)
{
    // working area----------------------------------------
    switch (*error_returned)
    {
        case NO_ERROR : printf (GREEN_START "NO ERROR: %d" COLOR_STOP, *error_returned);
        break;

        case NULL_POINTER_STACK_I : printf (RED_START "struct Stack* stack_i == 0, error code : %d" COLOR_STOP, *error_returned);
        break;

        case CAPACITY_SMALLER_THAN_ZERO : printf (RED_START "capacity < 0 (null), error code : %d" COLOR_STOP, *error_returned);
        break;

        case SIZE_SMALLER_THAN_ZERO : printf (RED_START "size < 0 (null), error code : %d" COLOR_STOP, *error_returned);
        break;

        case CAPACITY_SMALLER_THAN_SIZE : printf (RED_START "capacity < size, error code : %d" COLOR_STOP, *error_returned);
        break;

        default : printf (VIOLET_START "ERROR CODE: %d" COLOR_STOP, *error_returned);
    }
    // ----------------------------------------------------
}

void stack_destroy (struct Stack* stack_i)
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------


    // working area----------------------------------------
    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
    )

    assert (!error);

    for (int i = 0; i < stack_i -> capacity; i ++)
    {
        stack_i -> data [i] = 0;
    }
    free (stack_i -> data);
    stack_i -> data = NULL;
    stack_i -> capacity = 0;
    stack_i -> size = 0;
    // ----------------------------------------------------
}


IF_ON_DEBAG(
Error_Codes stack_verifier (struct Stack* stack_i)
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------


    // working area----------------------------------------
    if (stack_i == NULL)
    {
        error = NULL_POINTER_STACK_I;
        stack_dump (stack_i);
        return error;
    }

    if ((stack_i -> capacity) < 0)
    {
        error = CAPACITY_SMALLER_THAN_ZERO;
        stack_dump (stack_i);
        return error;
    }

    if ((stack_i -> size) < 0)
    {
        error = SIZE_SMALLER_THAN_ZERO;
        stack_dump (stack_i);
        return error;
    }

    if ((stack_i -> capacity) < (stack_i -> size))
    {
        error = CAPACITY_SMALLER_THAN_SIZE;
        stack_dump (stack_i);
        return error;
    }

    return error;
    // ----------------------------------------------------
}

void stack_dump (struct Stack* stack_i)
{
    // working area----------------------------------------
    if (stack_i == NULL)
    {
        printf ("struct Stack \"%s\" [%p] created by \"%s\" at \"%s\" : %d\n\n{\n", stack_i -> name, stack_i,
                                                                                stack_i -> func, stack_i -> file,
                                                                                stack_i -> line);
    } else
    {
        printf ("struct Stack \"%s\" [%p] created by \"%s\" at \"%s\" : %d\n\n{\n", stack_i -> name, stack_i,
                                                                                    stack_i -> func, stack_i -> file,
                                                                                    stack_i -> line);
        printf ("\tcapacity = %d\n", stack_i -> capacity);
        printf ("\tsize = %d\n", stack_i -> size);
        printf ("\tdata [%p]\n\t{\n", stack_i -> data);

        for (int i = 0; i < stack_i -> capacity; i ++)
        {
            if (fabs(stack_i -> data [i] - 0xDED) < 0.0001)
                printf ("\t\t[%d] = " SPECIFICATOR_TYPE " (MAYBE POIZEN)\n", i, stack_i -> data [i]);
            else
                printf ("\t\t*[%d] = " SPECIFICATOR_TYPE "\n", i, stack_i -> data [i]);
        }

        printf ("\t}\n");

        printf ("}\n");
    }
    // ----------------------------------------------------
}
)


void stack_real_up_capacity (struct Stack* stack_i)
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------


    // working area----------------------------------------
    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
        assert (!error);
    )

    stack_i -> data = (TYPE_OF_STACK_ELEM*)realloc (stack_i -> data, 2*(stack_i -> capacity));
    stack_i -> capacity = 2*(stack_i -> capacity);

    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
        assert (!error);
    )

    // ----------------------------------------------------
}
// -------------------------------------------------------

#endif

// THE END------------------------------------------------
