#pragma once

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions" // а таким нормально заниматься?

inline char * program = NULL;
inline int error_status = 0; 

#pragma clang diagnostic pop

const int OP_NAME_LEN = 50;
const int OP_COUNT = 22;
const int FUNCS_COUNT = 22;
const int OP_PRIORITY_MASK = 240;
const char NIL = '_';

struct lexem_names_numbers_class {
    const double number;
    const char name[OP_NAME_LEN];
    const int arg_quantity;
};

enum operations {
    OP_ADD     = 17,   // 0001|0001     |
    OP_SUB     = 18,   // 0001|0010     |
    OP_MUL     = 33,   // 0010|0001     |    =>    elder 4 bits are for operation priority
    OP_DIV     = 34,   // 0010|0010     |          young 4 bits are for op number
    OP_SQRT    = 49,   // 0011|0001     |
    OP_SIN     = 50,   // 0011|0010     |
    OP_COS     = 51,   // 0011|0011     |
    OP_POW     = 52,   // 0011|0100     |
    OP_FIG_C   = 53,   // divide !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111
    OP_FIG_O   = 54,  
    OP_ROUND_O = 55,
    OP_ROUND_C = 56,
    OP_IF      = 57,
    OP_WHILE   = 58,
    OP_MORE    = 59,
    OP_LESS    = 60,
    OP_EQUAL   = 61,
    OP_END     = 62,
    OP_FUNC    = 63,
    OP_PRINT   = 64,
    OP_RET     = 65,
    OP_NEQUAL  = 65
};

struct op_info {
    operations op_number;
    int arg_quantity;
};

union node_value {
    op_info operator_info;
    double number;
};

// TODO(DONE): Don't use conventions in the way the are not intended, I'm talking about _t
enum types_of_node {
    zero_class     = -1,
    value_class    =  1,
    operator_class =  2,
    variable_class =  3,
    syntax_class   =  4,
    function_class =  5
};

struct diff_tree_element {
    node_value value;
    types_of_node type;
    diff_tree_element * left;
    diff_tree_element * right;
    diff_tree_element * parent;
};

struct diff_tree {
    diff_tree_element * root;
    diff_tree_element * funcs_bodies[FUNCS_COUNT];
    int size;
};





typedef diff_tree_element* elem_ptr;

#define REQUIRE_SYMBOL(symbol)                   \
    if (check_symbol(symbol, pfile) == 0) {      \
        return 1;                                \
    }                                            \

#define verify(element)                  \
    error_status = 0;                    \
    if (tree_verify(element) == 1) {     \
        printf("error");                 \
        tree_visualize(element);         \
        return 0;                        \
    }

#define IS_NULL_PTR(element)                    \
    if (element == NULL) {                      \
        printf("place holder of "               \
               "reporting null ptr element");   \
        return 0;                               \
    }

#define READ_DATA(element)                                      \
    if (read_data(element) == 1) {                              \
        printf("\x1b[31m" "segmentationnnn faulttttt\n");       \
        return 0;                                               \
    }   



#define IS_ROUND_BRACKET                                          \
    (element->type == operator_class) &&                              \
    (element->parent->type == operator_class) &&                      \
    (op_priority(element->value.operator_info.op_number,          \
    element->parent->value.operator_info.op_number) == 1)         \



diff_tree_element * node_ctor(double value, types_of_node type, diff_tree_element *  left, 
                          diff_tree_element * right, diff_tree_element * parent);

int tree_ctor(diff_tree * tree);
void tree_dtor(elem_ptr * root);

const char * get_op_symbol(int op_num);          // maybe static
int is_one_char_symbol(char name);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++11-compat-deprecated-writable-strings"

int read_data(diff_tree * tree, char filename[] = "data.txt");
int print_tex(diff_tree_element * root, char file_name[] = "tex.md");

#pragma clang diagnostic pop
int tree_verify(diff_tree_element * element);

void print_in_pretty_way(diff_tree_element * root);
void print_tex_single_equation(diff_tree_element * root, FILE * pfile);


double tree_eval(diff_tree_element * element, double x_value);

bool op_priority(double op1, double op2);

int get_op_arg_number(operations op);

#define ELEM_OP_NUM element->value.operator_info.op_number
#define ELEM_DOUBLE element->value.number
#define ELEM_OP_ARG element->value.operator_info.arg_quantity
#define ELEM_TYPE element->type
