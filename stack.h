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
// #define STACK_INIT(point_stack_one, stack_length) stack_init (point_stack_one, stack_length IF_ON_DEBAG(,  \
//                                                                                ????? "stack_one",               \
//                                                                                 ??????"main()",                  \
//                                                                                 __FILE__,                  \
//                                                                                 __LINE__)    )?????????
#define CORRECTION_SIZE_FOR_DATA_INDEX 1
// ---------------------------------------------------

// determining the data type in the stack-------------
typedef double TYPE_OF_STACK_ELEM;
#define SPECIFICATOR_TYPE "%lf"
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
    CAPACITY_SMALLER_THAN_ZERO = -2,
    SIZE_SMALLER_THAN_ZERO = -3,
    CAPACITY_SMALLER_THAN_SIZE = -4
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
void stack_real_up_capacity (struct Stack* stack_i);
// ---------------------------------------------------

#endif  // #ifndef STACK_H
