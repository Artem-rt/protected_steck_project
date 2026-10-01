// stack.h - work safely whith stack!-----------------

// include guards-------------------------------------
#ifndef STACK_H
#define STACK_H
// ---------------------------------------------------

// important define for create debag-mode-------------
#ifdef DEBAG_OFF
#define NDEBAG
#define IF_ON_DEBAG(...)
#else
#define IF_ON_DEBAG(...) __VA_ARGS__
#endif                                                 // #ifdef DEBAG_OFF
// ---------------------------------------------------

// useful macro---------------------------------------
#define VIOLET_START "\e[35m"
#define RED_START "\e[31m"
#define GREEN_START "\e[32m"
#define COLOR_STOP "\e[0m"
#define ERROR_STACK_FILE "ERROR_IN_STACK_I.log"
#define STACK_PRINTED "STACK_PRINTED.txt"
#define OPEN_FILE_FOR_WRITING "w"
#define CANARIES 2


#define CORRECTION_SIZE_FOR_DATA_INDEX 1
// ---------------------------------------------------

// determining the data type in the stack-------------
typedef int TYPE_OF_STACK_ELEM;
#define SPECIFICATOR_TYPE "%d"
// ---------------------------------------------------

// canary const---------------------------------------
const TYPE_OF_STACK_ELEM CANARY_ONE = 0xDEADC0DE;
const TYPE_OF_STACK_ELEM CANARY_TWO = 0xDEADBABE;
// ---------------------------------------------------

// structure == our stack-----------------------------
struct Stack
{
    IF_ON_DEBAG(
        const char* name;
        const char* func;
        const char* file;
        int line;
    ) ;

    TYPE_OF_STACK_ELEM* data;

    int size;

    int capacity;

} ;
// ---------------------------------------------------

// error's codes enum---------------------------------
enum Error_Codes
{
    NO_ERROR = 0,
    NULL_POINTER_STACK_I = -1,
    NULL_POINTER_DATA = -2,
    CAPACITY_SMALLER_THAN_ZERO = -3,
    SIZE_SMALLER_THAN_ZERO = -4,
    CAPACITY_SMALLER_THAN_SIZE = -5,
    CANARY_ONE_WAS_DEAD = -6,
    CANARY_TWO_WAS_DEAD = -7
} ;
// ---------------------------------------------------

// function prototypes--------------------------------
Error_Codes stack_init (struct Stack* stack_i, int stack_length IF_ON_DEBAG(,
                                                                                const char* name,
                                                                                const char* func,
                                                                                const char* file,
                                                                                int line)        );
Error_Codes stack_push (struct Stack* stack_i, TYPE_OF_STACK_ELEM var);
Error_Codes stack_pop (struct Stack* stack_i, TYPE_OF_STACK_ELEM* pop_elem);
void decode_the_error_code_enum (Error_Codes* error_returned);
void stack_destroy (struct Stack* stack_i);


IF_ON_DEBAG(
Error_Codes stack_verifier (struct Stack* stack_i);
void stack_dump (struct Stack* stack_i);
)


void stack_printf (struct Stack* stack_i);
void stack_real_up_capacity (struct Stack* stack_i);
void stack_real_down_capacity (struct Stack* stack_i);
// ---------------------------------------------------

#endif  // #ifndef STACK_H





























































































// generic.h
