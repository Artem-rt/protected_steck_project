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
    if (stack_length == 0) printf (VIOLET_START "WARNING: you created 0-size stack!!!\n" COLOR_STOP);


    stack_i -> capacity = stack_length;
    if (stack_i -> capacity == 0)
        stack_i -> size = -1;
    else
        stack_i -> size = 1;

    IF_ON_DEBAG(
        stack_i -> name = name;
        stack_i -> func = func;
        stack_i -> file = file;
        stack_i -> line = line;
    )

    stack_i -> data = (TYPE_OF_STACK_ELEM*)calloc (CANARIES + stack_length, sizeof (TYPE_OF_STACK_ELEM));

    stack_i -> data [0] = CANARY_ONE;
    if (stack_i -> capacity == 0)
        stack_i -> data [1] = CANARY_TWO;
    else
        stack_i -> data [stack_i -> capacity - 1] = CANARY_TWO;

    for (int i = 1; i < stack_i -> capacity - 1; i++)
    {
        stack_i -> data [i] = 0xDED;
    }
    stack_printf (stack_i);
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


    if ( (stack_i -> size) + 1 == (stack_i -> capacity) || (stack_i -> capacity) == 0 )
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

    if (stack_i -> capacity == 0)
    {
        error = CAPACITY_ZERO_IN_STACK_POP;
        stack_dump (stack_i);
    }

    assert (!error);

     if (stack_i -> size + 1 == (stack_i -> capacity / 4))
    {
        stack_real_down_capacity (stack_i);
    }

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

        case NULL_POINTER_STACK_I : printf (RED_START "struct Stack* stack_i == NULL, error code : %d" COLOR_STOP, *error_returned);
        break;

        case NULL_POINTER_DATA : printf (RED_START "stack_i -> data == NULL, error code : %d" COLOR_STOP, *error_returned);
        break;

        case CAPACITY_SMALLER_THAN_ZERO : printf (RED_START "capacity < 0 (null), error code : %d" COLOR_STOP, *error_returned);
        break;

        case SIZE_SMALLER_THAN_ZERO : printf (RED_START "size < 0 (null), error code : %d" COLOR_STOP, *error_returned);
        break;

        case CAPACITY_SMALLER_THAN_SIZE : printf (RED_START "capacity < size, error code : %d" COLOR_STOP, *error_returned);
        break;

        case CANARY_ONE_WAS_DEAD : printf (RED_START "CANARY_ONE WAS DEAD (stack_i.data[0] attacked), error code : %d" COLOR_STOP, *error_returned);
        break;

        case CANARY_TWO_WAS_DEAD : printf (RED_START "CANARY_TWO WAS DEAD (stack_i.data[stack.capacity - 1] attacked), error code : %d" COLOR_STOP, *error_returned);
        break;

        case CAPACITY_ZERO_IN_STACK_POP : printf (RED_START "capacity == 0 (null), error code : %d" COLOR_STOP, *error_returned);
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

    if (stack_i -> data == NULL)
    {
        error = NULL_POINTER_DATA;
        stack_dump (stack_i);
        return error;
    }

    if ((stack_i -> capacity) < 0)
    {
        error = CAPACITY_SMALLER_THAN_ZERO;
        stack_dump (stack_i);
        return error;
    }

    if ((stack_i -> size) < 0 && (stack_i -> capacity) != 0)
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

    if (stack_i -> data [0] != CANARY_ONE)
    {
        error = CANARY_ONE_WAS_DEAD;
        stack_dump (stack_i);
        return error;
    }

    if (stack_i -> data [stack_i -> capacity - 1] != CANARY_TWO && stack_i -> capacity != 0)
    {
        error = CANARY_TWO_WAS_DEAD;
        stack_dump (stack_i);
        return error;
    }

    return error;
    // ----------------------------------------------------
}

void stack_dump (struct Stack* stack_i)
{
    // variable--------------------------------------------
    FILE* error_in_stack_i = NULL;
    // ----------------------------------------------------

    // working area----------------------------------------

    if ((error_in_stack_i = fopen (ERROR_STACK_FILE, OPEN_FILE_FOR_WRITING)) == NULL)
    {
        printf ("You have errors with stack, but " ERROR_STACK_FILE " didn't open. Sorry...");
        error_in_stack_i = stderr;
    }

    if (stack_i == NULL)
    {
        fprintf (error_in_stack_i, "SORRY, BUT Stack* stack_i == NULL");
    } else
    {
        fprintf (error_in_stack_i, "\n\nstruct Stack \"%s\" [%p] created by \"%s\" at \"%s\" : %d\n\n{\n", stack_i -> name, stack_i,
                                                                                                                                      stack_i -> func, stack_i -> file,
                                                                                                                                      stack_i -> line);

        if (stack_i -> capacity == 0)
        {
            fprintf (error_in_stack_i, "\n\nMAYBE PROBLEM IN stack_i.capacity == 0 in stack_pop(--//--)\n\n");
        }
        fprintf (error_in_stack_i, "\tcapacity = %d\n", stack_i -> capacity);
        fprintf (error_in_stack_i, "\tsize = %d\n", stack_i -> size);
        fprintf (error_in_stack_i, "\tdata [%p]\n\t{\n", stack_i -> data);

        if (stack_i -> size > 0 && stack_i -> capacity > 0 && stack_i -> size <= stack_i -> capacity && stack_i -> data != NULL)
        {
            fprintf (error_in_stack_i, "\t\tCANARY_ONE: data[0] = " SPECIFICATOR_TYPE " \n", stack_i -> data [0]);

            int cnt_print_dump = 1;

            for (; cnt_print_dump < stack_i -> capacity - 1; cnt_print_dump  ++)
            {
                if (fabs(stack_i -> data [cnt_print_dump ] - 0xDED) < 0.0001)
                    fprintf (error_in_stack_i, "\t\t[%d] = " SPECIFICATOR_TYPE " (MAYBE POIZEN)\n", cnt_print_dump , stack_i -> data [cnt_print_dump ]);
                else
                    fprintf (error_in_stack_i, "\t\t*[%d] = " SPECIFICATOR_TYPE "\n", cnt_print_dump , stack_i -> data [cnt_print_dump ]);
            }

            fprintf (error_in_stack_i, "\t\tCANARY_ONE: data[%d] = " SPECIFICATOR_TYPE " \n", cnt_print_dump, stack_i -> data [cnt_print_dump]);
        }
        fprintf (error_in_stack_i, "\t}\n");

        fprintf (error_in_stack_i, "}\n");

        if (fclose(error_in_stack_i)) printf ("ERROR WITH CLOSING ERROR_FILE");
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

    if (stack_i -> capacity == 0)
    {
        stack_i -> data = (TYPE_OF_STACK_ELEM*)realloc (stack_i -> data, (size_t)((5 + CANARIES)* sizeof (TYPE_OF_STACK_ELEM)));
        stack_i -> capacity = 5;
        stack_i -> size = 1;

    } else
    {
        stack_i -> data = (TYPE_OF_STACK_ELEM*)realloc (stack_i -> data, 2*(stack_i -> capacity * sizeof (TYPE_OF_STACK_ELEM)));
        stack_i -> capacity = 2*(stack_i -> capacity);
    }

    stack_i -> data [stack_i -> capacity - 1] = CANARY_TWO;

    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
        assert (!error);
    )
    // ---------------------------------------------------
}

void stack_real_down_capacity (struct Stack* stack_i)
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------


    // working area----------------------------------------
    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
        assert (!error);
    )

    if (stack_i -> capacity == 0)
    {
        error = CAPACITY_ZERO_IN_STACK_POP;
        stack_dump (stack_i);
    }

    assert (!error);

    stack_i -> data = (TYPE_OF_STACK_ELEM*)realloc (stack_i -> data, (stack_i -> capacity/4 * sizeof (TYPE_OF_STACK_ELEM)));
    stack_i -> capacity = (stack_i -> capacity) / 4;
    stack_i -> data [stack_i -> capacity - 1] = CANARY_TWO;

    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
        assert (!error);
    )

    // ----------------------------------------------------
}

void stack_printf (struct Stack* stack_i)
{
    // variables and etc.----------------------------------
    Error_Codes error = NO_ERROR;
    // ----------------------------------------------------

    // working area----------------------------------------
    IF_ON_DEBAG(
        error = stack_verifier (stack_i);
        assert (!error);
    )

    // variable--------------------------------------------
    FILE* stack_printed = NULL;
    // ----------------------------------------------------

    // working area----------------------------------------

    if ((stack_printed = fopen (STACK_PRINTED, OPEN_FILE_FOR_WRITING)) == NULL)
    {
        printf ("You have errors with stack, but " ERROR_STACK_FILE " didn't open. Sorry...");
        stack_printed = stdout;
    }

    fprintf (stack_printed, "\n\nstruct Stack \"%s\" [%p] created by \"%s\" at \"%s\" : %d\n\n{\n", stack_i -> name, stack_i,
                                                                                                                                      stack_i -> func, stack_i -> file,
                                                                                                                                      stack_i -> line);
    fprintf (stack_printed, "\tcapacity = %d\n", stack_i -> capacity);
    fprintf (stack_printed, "\tsize = %d\n", stack_i -> size);
    fprintf (stack_printed, "\tdata [%p]\n\t{\n", stack_i -> data);

    fprintf (stack_printed, "\t\tCANARY_ONE: data[0] = " SPECIFICATOR_TYPE " \n", stack_i -> data [0]);

    int cnt_print_dump = 1;

    for (; cnt_print_dump < stack_i -> capacity - 1; cnt_print_dump  ++)
        {
            if (fabs(stack_i -> data [cnt_print_dump ] - 0xDED) < 0.0001)
                fprintf (stack_printed, "\t\t[%d] = " SPECIFICATOR_TYPE " (MAYBE POIZEN)\n", cnt_print_dump , stack_i -> data [cnt_print_dump ]);
            else
                fprintf (stack_printed, "\t\t*[%d] = " SPECIFICATOR_TYPE "\n", cnt_print_dump , stack_i -> data [cnt_print_dump ]);
        }

    fprintf (stack_printed, "\t\tCANARY_TWO: data[%d] = " SPECIFICATOR_TYPE " \n", cnt_print_dump, stack_i -> data [cnt_print_dump]);

    fprintf (stack_printed, "\t}\n");

    fprintf (stack_printed, "}\n");

    if (fclose(stack_printed)) printf ("ERROR WITH CLOSING ERROR_FILE");
    // ----------------------------------------------------
}
// -------------------------------------------------------

#endif

// THE END------------------------------------------------
