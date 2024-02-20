/**
* C PROGRAM TO MINIMIZE BOOLEAN EXPRESSIONS
* -----------------------------------------
* To add new operators to the program
*   1. Increase the value of NO_OF_CONST_SYMBOLS at line 22
*   2. Include them in the set defined by SET_OF_CONST_SYMBOLS at line 23
*   3. Set their precedence in detect_operator() at line 27
*   4. Describe their operations in the function evaluate_constant_postfix()
*   
* To exclude some operators from the output expression
*   1. Specify them in the macro IS_EXCLUDED_OPERATOR at line 25
**/

#include <stdio.h>

// MACROs that are used for customization

#define  MAX_LEN_EXP              50                                       // max. expression size
#define  MAX_LEN_ANS              10                                       // max. length of the minimized expression
#define  MAX_NUM_VAR              5                                        // max. number of distinct variables

#define  NO_OF_CONST_SYMBOLS      5                                        // number of operators and constants
#define  SET_OF_CONST_SYMBOLS     {'0', '1', '~', '+', '.'}                // set of operators and constants

#define  IS_EXCLUDED_OPERATOR(W)  (W=='\0'|W=='\0')                        // exclude these operators from the output

#define  detect_operator(X)       ((X=='+')|(X=='.')<<1|(X=='~')<<2)       // check if X is an operator
#define  detect_operand(Y)        ((Y>47&Y<50)|(Y>96&Y<123|Y>64&Y<91)<<1)  // check if Y is an operand

// MACROs which are used internally by the program

#define  SIZE_SYMBOL_TABLE  (NO_OF_CONST_SYMBOLS + MAX_NUM_VAR)  // size of the symbol table
#define  SIZE_TRTABLE_ROW   (MAX_NUM_VAR)                        // width of a row of the truth table
#define  TRTABLE_HEIGHT     (1 << MAX_NUM_VAR)                   // number of rows in the truth table
#define  STACK_SIZE         (MAX_LEN_EXP)                        // size of the stack used for infix-postfix conversions

// user-defined data type to represent a node of a binary tree

typedef struct node {char val; struct node *LC, *RC;} node;

// function prototype declarations

char*  input                     (char []);
int    is_valid_len_and_chars    (char []);
int    is_valid_infix            (char []);
int    initialize                (char [], char* [], char [], char [], int*, char* []);
int    truth_table_maker         (char [], int, char* []);
int    init_or_matchwith_result  (char, int);
char   evaluate_constant_postfix (char* []);
char** permute_symbols           (int, char* [], int, char [], int);
void   output                    (char []);
void   inorder_traversal         (node*, char);

// definition of some inline functions

inline void push (int stack [], int X) {stack [(*stack)++] = X;}
inline int  pop  (int stack [])        {return stack [--(*stack)];}

// global array 'result[]' to store the value of the user-input expression

char result [TRTABLE_HEIGHT + 1] = {0};

// the 'main()' function as the driver module

int main (void)
{
    int no_of_out_symbols, no_of_variables;

    char  actual_expression        [MAX_LEN_EXP + 1],
         *ptr_actual_expression    [MAX_LEN_EXP + 1],

          symbol_table             [SIZE_SYMBOL_TABLE + 1] = SET_OF_CONST_SYMBOLS,
          blank_trtable_row        [SIZE_TRTABLE_ROW  + 1],
         *ptr_symbol_table         [SIZE_SYMBOL_TABLE + 1],

        **ptr_minimized_expression,
          minimized_expression     [MAX_LEN_ANS + 1];

    if (!input (actual_expression) && printf ("\n  [Error : invalid / too large expr.]\n"))
        return 1;

    no_of_out_symbols = initialize (actual_expression, ptr_actual_expression, symbol_table, blank_trtable_row, &no_of_variables, ptr_symbol_table);

    if (!no_of_out_symbols && printf ("\n  [Error : too many variables]\n"))
        return 1;

    truth_table_maker (blank_trtable_row, no_of_variables, ptr_actual_expression);
    
    for (int i = 1 ; i <= MAX_LEN_ANS ; i++)
        if (ptr_minimized_expression = permute_symbols (no_of_out_symbols, ptr_symbol_table, i, blank_trtable_row, no_of_variables))
        {
            int j;

            for (j = NO_OF_CONST_SYMBOLS ; j < NO_OF_CONST_SYMBOLS + no_of_variables ; j++)
                blank_trtable_row [j - NO_OF_CONST_SYMBOLS] = symbol_table [j];
            
            for (j = 0 ; j < i ; j++, ptr_minimized_expression++)
                minimized_expression [j] = **ptr_minimized_expression;
            minimized_expression [j] = 0;

            output (minimized_expression);

            return 0;
        }
}

// function to input an infix expression from the user and return its postfix equivalent

char* input (char postfix_expression [])
{
    char infix_expression [MAX_LEN_EXP + 2];
    int  stack            [STACK_SIZE + 1];

    int  ind_infix, ind_postfix;
    char ch;

    printf ("\n  Max. input length    : %d"
            "\n  Max. input variables : %d"
            "\n  Max. output length   : %d", MAX_LEN_EXP, MAX_NUM_VAR, MAX_LEN_ANS);
    
    printf ("\n  Recognized operands  :");
    for (int flag = 0, i = 0 ; i < 128 ; i++)
        !flag &&  detect_operand (i) && (++flag, printf (" %c", i)) ||
         flag && !detect_operand (i) && (--flag, printf ("-%c", i - 1));
        
    printf ("\n  Recognized operators :");
    for (int i = 2 ; i < NO_OF_CONST_SYMBOLS ; i++)
        printf (" %c", (int []) SET_OF_CONST_SYMBOLS [i]);
        
    printf ("\n  Operator precedence  :");
    for (int count = 0, exp2 = 1 ; count < NO_OF_CONST_SYMBOLS - 2 ; exp2 = exp2 << 1)
    {
        int arr [] = SET_OF_CONST_SYMBOLS;
        count && printf (" <");
        for (int i = 2 ; i < NO_OF_CONST_SYMBOLS ; i++)
            detect_operator (arr [i]) == exp2 && (++count, printf (" %c", arr [i]));        
    }
    
    printf ("\n  Excluded pperators   :");
    {
        int arr [] = SET_OF_CONST_SYMBOLS;
        for (int i = 2 ; i < NO_OF_CONST_SYMBOLS ; i++)
            IS_EXCLUDED_OPERATOR (arr [i]) && printf (" %c", arr [i]);
    }
    
    printf ("\n\n  Enter expression (max. length %d, max. var %d):"
              "\n  ----------------------------------------------\n\n\t", MAX_LEN_EXP, MAX_NUM_VAR);
    scanf ("%[^\n]s", infix_expression);

    *postfix_expression = 0;

    if (!is_valid_len_and_chars (infix_expression) || !is_valid_infix (infix_expression))
        return NULL;

    stack [0] = 2;
    stack [1] = '(';

    for (ind_postfix = 0, ind_infix = 0 ; ch = infix_expression [ind_infix], stack [0] > 1 ; ind_infix++)
        if (detect_operator (ch))
        {
            while (detect_operator (stack [stack [0] - 1]) >= detect_operator (ch))
                postfix_expression [ind_postfix++] = stack [--stack [0]];
            stack [stack [0]++] = ch;
        }
        else if (detect_operand (ch))
            postfix_expression [ind_postfix++] = ch;
            
        else if (ch == '(')
            stack [stack [0]++] = ch;
        else if (ch == ')')
        {
            while (stack [stack [0] - 1] ^ '(')
                postfix_expression [ind_postfix++] = stack [--stack [0]];
            --stack [0];
        }
            
    postfix_expression [ind_postfix] = 0;
    
    return postfix_expression;
}

// function to check the length and the characters in an input expression. ok - 1, not ok - 0.

int is_valid_len_and_chars (char infix_expr [])
{
    int i;

    for (i = 0 ; infix_expr [i] && i < MAX_LEN_EXP ; i++)
        if (infix_expr [i] ^ ' ' &&
            infix_expr [i] ^ '(' && infix_expr [i] ^ ')' &&
            !detect_operator (infix_expr [i]) && !detect_operand (infix_expr [i]))
                return 0;

    return infix_expr [i] == 0;
}

// function to check if a string is storing a valid infix expression. yes - 1, no - 0.

int is_valid_infix (char infix_expr [])
{
    int token_index, token_offset, unclosed_parentheses = 0;

    for (token_offset = token_index = 0 ; infix_expr [token_index] ; token_index++)
    {
        infix_expr [token_index] == '(' && unclosed_parentheses++;
        if (infix_expr [token_index] == ')' && !unclosed_parentheses--) return 0;
        
        if (infix_expr [token_index] == '(' || infix_expr [token_index] == '~')
        {
            if (token_offset && infix_expr [token_offset - 1] == ')' | detect_operand (infix_expr [token_offset - 1]))
                return 0;
        }
        else if (infix_expr [token_index] == ')' || detect_operator (infix_expr [token_index]) && infix_expr [token_index] != '~')
        {
            if (!token_offset || infix_expr [token_offset - 1] != ')' & !detect_operand (infix_expr [token_offset - 1]))
                return 0;
        }
        else if (infix_expr [token_index] == ' ') continue;
        else
        {
            if (!detect_operand (infix_expr [token_index]) ||
                token_offset && infix_expr [token_offset - 1] == ')' | detect_operand (infix_expr [token_offset - 1]))
                return 0;
        }
        token_offset = token_index + 1;
    }

    if (unclosed_parentheses || !detect_operand (infix_expr [token_offset - 1]) & infix_expr [token_offset - 1] != ')')
        return 0;

    infix_expr [token_offset] = ')';
    infix_expr [token_offset + 1] = 0;

    return 1;
}

// function to initialize 'symbol_table[]', 'ptr_exprn[]', 'ptr_symbol_table[]' and 'no_of_out_symbols'(returned to main())

int initialize (char actual_exprn [], char *ptr_exprn [], char symbol_table [], char blank_trtable_row [], int *no_of_variables, char *ptr_symbol_table [])
{
    int symbl_tbl_length = NO_OF_CONST_SYMBOLS;

    while (*actual_exprn)
    {
        int i;
        
        for (i = 0 ; *actual_exprn ^ symbol_table [i] && i < symbl_tbl_length ; i++);
        i == symbl_tbl_length && symbl_tbl_length++;

        if (symbl_tbl_length > MAX_NUM_VAR + NO_OF_CONST_SYMBOLS)
            return 0;

        symbol_table [i] = *actual_exprn;
        *ptr_exprn++ = detect_operand (*actual_exprn) >> 1 ? blank_trtable_row + i - NO_OF_CONST_SYMBOLS
                                                           : symbol_table + i;
        actual_exprn++;
    }
    *ptr_exprn = NULL;
    
    int ptr_symbol_table_length = 0;
        
    for (int i = 0 ; i < NO_OF_CONST_SYMBOLS ; i++)
        !IS_EXCLUDED_OPERATOR (symbol_table [i]) &&
        (ptr_symbol_table [ptr_symbol_table_length++] = symbol_table + i);
        
    *no_of_variables = symbl_tbl_length - NO_OF_CONST_SYMBOLS;
        
    for (int i = NO_OF_CONST_SYMBOLS ; i < symbl_tbl_length ; i++)
        ptr_symbol_table [ptr_symbol_table_length++] = blank_trtable_row + i - NO_OF_CONST_SYMBOLS;

    return ptr_symbol_table_length;
}

// function to recursively construct the truth table rows of size 'no_of_variables' inside 'blank_table_row[]'

int truth_table_maker (char blank_table_row [], int no_of_variables, char *any_pointr_expression [])
{
    static int tablerow_current_width;
    
    if (tablerow_current_width == no_of_variables)
        return init_or_matchwith_result (evaluate_constant_postfix (any_pointr_expression), no_of_variables);

    for (int i = 0 ; i < 2 ; i++)
    {
        blank_table_row [tablerow_current_width] = i + '0';

        ++tablerow_current_width;
        if (!truth_table_maker (blank_table_row, no_of_variables, any_pointr_expression))
        {
            tablerow_current_width = 0;
            return 0;
        }
        --tablerow_current_width;
    }

    return 1;
}

// function to initialize a 'result[]' array element, or, match a value with a 'result[]' array element

int init_or_matchwith_result (char bool_value, int no_of_variables)
{
    static int index;

    index ^ 1 << no_of_variables || (index = 0);

    if (!result [index])
    {
        result [index++] = bool_value;
        return 1;
    }
    else
        return (result [index++] == bool_value) ||
               (index = 0);
}

// function to evaluate a postfix expression (reference by an array of pointers) containing constant operands 0 and 1

char evaluate_constant_postfix (char *ptr_actual_expression [])
{
    int stack [STACK_SIZE + 1];
    *stack = 1;

    while (*ptr_actual_expression)
    {
        switch (**ptr_actual_expression)
        {
            case '0' :
            case '1' : push (stack, **ptr_actual_expression - 48); break;

            case '+' : push (stack,  pop (stack) | pop (stack)); break;
            case '.' : push (stack,  pop (stack) & pop (stack)); break;
            case '~' : push (stack, !pop (stack));
        }
        ptr_actual_expression++;
    }

    return (pop (stack) + 48);
}

// function to permute 'm' number of symbols referenced by 'ptr_symbol_table[]' into '1', '2', ..., 'n' locations

char** permute_symbols (int m, char *ptr_symbol_table [], int n, char blank_table_row [], int no_of_variables)
{
    static char *new_ptr_actual_expression [MAX_LEN_ANS + 1];
    static int   newexp_current_index;
    
    static int flg_no_of_operands, flg_number_of_binary_operators;
    
    if (newexp_current_index == n)
    {
        new_ptr_actual_expression [newexp_current_index] = NULL;
        
        if ((flg_no_of_operands + flg_number_of_binary_operators) & 1)
            return truth_table_maker (blank_table_row, no_of_variables, new_ptr_actual_expression)
                   ? new_ptr_actual_expression : NULL;
                   
        return NULL;
    }

    for (int i = 0 ; i < m ; i++)
    {
        char curr_symbol = *ptr_symbol_table [i];
        new_ptr_actual_expression [newexp_current_index] = ptr_symbol_table [i];
        
        detect_operand  (curr_symbol) && ++flg_no_of_operands;
        detect_operator (curr_symbol) && curr_symbol ^ '~' && ++flg_number_of_binary_operators;

        if (flg_number_of_binary_operators < flg_no_of_operands && flg_no_of_operands <= n / 2 + 1)
        {
            ++newexp_current_index;
            if (permute_symbols (m, ptr_symbol_table, n, blank_table_row, no_of_variables))
            {
                newexp_current_index = 0;
                return (new_ptr_actual_expression);
            }
            --newexp_current_index;
        }
            
        detect_operand  (curr_symbol) && --flg_no_of_operands;
        detect_operator (curr_symbol) && curr_symbol ^ '~' && --flg_number_of_binary_operators;
    }

    return (NULL);
}

// function to display a postfix expression in infix

void output (char postfix_expression [])
{
    node  chunk [MAX_LEN_ANS],
         *c_ptr_dm_ = chunk;

    node *stack [STACK_SIZE];
    int   top = 0;

    while (*postfix_expression)
    {
        node *tNew = c_ptr_dm_++;
        tNew -> val = *postfix_expression;

        if (detect_operand (*postfix_expression))
            tNew -> LC  = NULL,
            tNew -> RC  = NULL;
        else
            tNew -> RC  = stack [--top],
            tNew -> LC  = *postfix_expression ^ '~' ? stack [--top] : NULL;

        stack [top++] = tNew;
        postfix_expression++;
    }

    printf ("\n  Eqv. expression (max. length %d):"
            "\n  ---------------------------------\n\n\t", MAX_LEN_ANS);
    inorder_traversal (*stack, '\0');
}

// function to perform inorder traversal of a binary tree

void inorder_traversal (node *head, char value_of_parent)
{
    if (!head) return;

    if (!detect_operand (head -> val) &&
        detect_operator (value_of_parent) > detect_operator (head -> val))
            putchar ('(');

    inorder_traversal (head -> LC, head -> val);
    putchar (head -> val);
    inorder_traversal (head -> RC, head -> val);

    if (!detect_operand (head -> val) &&
        detect_operator (value_of_parent) > detect_operator (head -> val))
            putchar (')');
}
