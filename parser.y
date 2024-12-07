%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
void yyerror(const char *s);
int yylex();

/* Constants*/
#define MAX_VAR 100
#define MAX_FUNC 50
#define MAX_PARAMS 10
#define MAX_STACK 100


struct Variable {
    char name[100];
    int type; 
    union {
        int ival;
        char strval[100];
    } value;
};


struct Function {
    char name[100];
    char param_names[MAX_PARAMS][100];
    int param_count;
    int (*func_body)(int *params);
};


struct Variable variables[MAX_VAR];
int var_count = 0;

struct Function functions[MAX_FUNC];
int func_count = 0;

int return_stack[MAX_STACK];
int execution_stack[MAX_STACK];
int stack_top = -1;

/* functions */

void some_predefined_function(int params[]) {
    printf("Ejecutando función con parámetros: ");
    for (int i = 0; i < MAX_PARAMS && params[i] != 0; i++) {
        printf("%d ", params[i]);
    }
    printf("\n");
}


int is_variable_declared(char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

int get_variable_value(char *name, int *type, char *strval) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            *type = variables[i].type;
            if (*type == 0) {
                return variables[i].value.ival;
            } else if (*type == 1) {
                strcpy(strval, variables[i].value.strval);
                return 0;
            }
        }
    }
    return -1;
}

void set_variable_value(char *name, int type, int ival, char *strval) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].type = type;
            if (type == 0) {
                variables[i].value.ival = ival;
            } else if (type == 1) {
                strcpy(variables[i].value.strval, strval);
            }
            return;
        }
    }
    strcpy(variables[var_count].name, name);
    variables[var_count].type = type;
    if (type == 0) {
        variables[var_count].value.ival = ival;
    } else if (type == 1) {
        strcpy(variables[var_count].value.strval, strval);
    }
    var_count++;
}


void push_return_value(int value) {
    if (stack_top < MAX_STACK - 1) {
        return_stack[++stack_top] = value;
    } else {
        yyerror("Error: Desbordamiento de pila de retorno.");
        exit(1);
    }
}

int pop_return_value() {
    if (stack_top >= 0) {
        return return_stack[stack_top--];
    } else {
        yyerror("Error: Pila de retorno vacía.");
        exit(1);
    }
}

struct Function *get_function(char *name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(functions[i].name, name) == 0) {
            return &functions[i];
        }
    }
    return NULL;
}

void add_function(char *name, char param_names[MAX_PARAMS][100], int param_count, int (*func_body)(int *params)) {
    strcpy(functions[func_count].name, name);
    functions[func_count].param_count = param_count;
    for (int i = 0; i < param_count; i++) {
        strcpy(functions[func_count].param_names[i], param_names[i]);
        set_variable_value(param_names[i], 0, 0, NULL);
    }
    functions[func_count].func_body = func_body;
    func_count++;
}

/*stack*/

void push_execution_context(int value) {
    if (stack_top < MAX_STACK - 1) {
        execution_stack[++stack_top] = value;
    } else {
        yyerror("Error: Desbordamiento de pila de ejecución.");
        exit(1);
    }
}

int pop_execution_context() {
    if (stack_top >= 0) {
        return execution_stack[stack_top--];
    } else {
        yyerror("Error: Pila de ejecución vacía.");
        exit(1);
    }
}

int get_current_execution_context() {
    if (stack_top >= 0) {
        return execution_stack[stack_top];
    }
    return 1;
}

%}
%debug
%union {
    int val; 
    char *str;
    struct ParamList {
    int param_count;
    char param_names[10][100];
} param_list;


struct FunctionParams {
    int param_count;
    int params[10];
} function_params;


struct FuncBody {
    int (*func)(int *params); 
} func_body; 
}

%token <val> NUMBER
%token <str> ID TEXTO
%token IF ELSE ELIF LPAR RPAR LBRAC RBRAC IGUAL SUMA RESTA MULTIPLICACION DIVISION GREATER LESSER GTEQ LSEQ EQ FOR SEMICOLON WHILE PLUS CALL RETURN FUNCTION COMA IMPRIMIR

%type <val> OPERATION LOGIC CONDITIONAL ELSEIF THEN FOR_INC inCOND ASSIGNMENT
%type <param_list> PARAM_LIST
%type <function_params> PARAMS
%type <func_body> FUNCTION_BODY


%left SUMA RESTA
%left MULTIPLICACION DIVISION

%%

PROGRAM:
    /* vacio */
    | PROGRAM EXPRESSION
    ;

EXPRESSION:
    OPERATION {
        if (get_current_execution_context()) {
            
        }
    }
    | LOGIC {
        if (get_current_execution_context()) {
            
        }
    }
    | ASSIGNMENT
    | CONDITIONAL
    | LOOP
    | FUNCTION_DECLARATION
    | FUNCTION_CALL
    | IMPRIMIR LPAR OPERATION RPAR  { imprimir((void*)&$3, 0); }
    | IMPRIMIR LPAR TEXTO RPAR  { imprimir((void*)&$3, 1); }
    ;


ASSIGNMENT:
    ID IGUAL TEXTO {
        if (get_current_execution_context()) {
            set_variable_value($1, 1, 0, $3);
            printf("Variable %s asignada a %s\n", $1, $3);
        }
    }
    | ID IGUAL OPERATION {
        if (get_current_execution_context()) {
            set_variable_value($1, 0, $3, NULL);
            printf("Variable %s asignada a %d\n", $1, $3);
        }
    }
    ;

OPERATION:
    OPERATION SUMA OPERATION { $$ = $1 + $3; }
    | OPERATION RESTA OPERATION { $$ = $1 - $3; }
    | OPERATION MULTIPLICACION OPERATION { $$ = $1 * $3; }
    | OPERATION DIVISION OPERATION {
        if ($3 == 0) {
            yyerror("Error: División por cero.");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
    }
    | NUMBER { $$ = $1; }
    | ID {
        char strval[100];
        int type;
        int val = get_variable_value($1, &type, strval);
        if (val == -1) {
            yyerror("Error: Variable no declarada.");
            exit(1);
        } else if (type == 0) {
            $$ = val;
        } else if (type == 1) {
            yyerror("Error: No se pueden realizar operaciones numéricas con strings.");
            exit(1);
        }
    }
    ;

LOGIC:
    OPERATION GREATER OPERATION { $$ = $1 > $3; }
    | OPERATION LESSER OPERATION { $$ = $1 < $3; }
    | OPERATION GTEQ OPERATION { $$ = $1 >= $3; }
    | OPERATION LSEQ OPERATION { $$ = $1 <= $3; }
    | OPERATION EQ OPERATION { $$ = $1 == $3; }
    ;

CONDITIONAL:
    IF LPAR LOGIC RPAR LBRAC {
        push_execution_context($3);
    } inCOND RBRAC ELSEIF THEN {
        pop_execution_context();
    }
    ;

ELSEIF:
    /* vaciop */ {}
    | ELIF LPAR LOGIC RPAR LBRAC {
        if (get_current_execution_context() == 0 && $3) {
            push_execution_context(1);
        } else {
            push_execution_context(0);
        }
    } inCOND RBRAC ELSEIF {
        pop_execution_context();
    }
    ;

THEN:
    /* vacio */ {}
    | ELSE LBRAC {
        if (get_current_execution_context() == 0) {
            push_execution_context(1);
        } else {
            push_execution_context(0);
        }
    } inCOND RBRAC {
        pop_execution_context();
    }
    ;

inCOND:
    EXPRESSION inCOND {}
    | /* vacio */ {}
    ;

LOOP:
    FOR LPAR ASSIGNMENT SEMICOLON LOGIC SEMICOLON FOR_INC RPAR LBRAC inCOND RBRAC {
        if (get_current_execution_context()) {

            int var= $3;
            int lgc = $5;
            int inc = $10;

            
            for (int i=0;i<3;i++) {
                push_execution_context(1);
                $10;
                pop_execution_context();
            }
        }
    }
    | WHILE LPAR LOGIC RPAR LBRAC inCOND RBRAC {
        if (get_current_execution_context()) {
            while ($3) {
                push_execution_context(1);
                $6;
                pop_execution_context();
            }
        }
    }
    ;

FOR_INC:
    ID PLUS PLUS {
        if (get_current_execution_context()) {
            int type;
            char strval[100];
            int value = get_variable_value($1, &type, strval);
            if (type != 0) {
                yyerror("Error: Solo se puede incrementar variables numéricas.");
                exit(1);
            }
            
            value++;
            set_variable_value($1, 0, value, NULL);
            printf("Valor: %d",get_variable_value($1, &type, strval));
        }
    }
    | ID SUMA NUMBER {
        if (get_current_execution_context()) {
            int type;
            char strval[100];
            int value = get_variable_value($1, &type, strval);
            if (type != 0) {
                yyerror("Error: Solo se puede incrementar variables numéricas.");
                exit(1);
            }
            value += $3;
            set_variable_value($1, 0, value, NULL);
        }
    }
    ;

FUNCTION_DECLARATION:
    FUNCTION ID LPAR PARAM_LIST RPAR LBRAC FUNCTION_BODY RBRAC {
        char param_names[MAX_PARAMS][100];
        
        for (int i = 0; i < $4.param_count; i++) {
            strcpy(param_names[i], $4.param_names[i]);
        }

        add_function($2, param_names, $4.param_count, $7.func);
        printf("Función %s declarada.\n", $2);
    }
    ;

PARAM_LIST:
    /* vacio */ { 
        $$ = (struct ParamList){0, {{0}}}; 
    }
    | ID { 
        $$ = (struct ParamList){1, {{0}}}; 
        strcpy($$.param_names[0], $1); 
    }
    | PARAM_LIST COMA ID {
        $1.param_count++;
        strcpy($1.param_names[$1.param_count - 1], $3);
        $$ = $1;
    }
    ;

FUNCTION_BODY:
    RETURN OPERATION {
        struct FuncBody fb;
        fb.func = some_predefined_function;  
        $$ = fb;
    }
    | RETURN FUNCTION_CALL { 
        struct FuncBody fb;
        fb.func = some_predefined_function; 
        $$ = fb;
    }
    ;

FUNCTION_CALL:
    CALL ID LPAR PARAMS RPAR {
        struct Function *func = get_function($2);
        if (!func) {
            yyerror("Error: Función no definida.");
        } else {
            if ($4.param_count != func->param_count) {
                yyerror("Error: Número incorrecto de parámetros.");
            } else {
                int params[MAX_PARAMS];
                for (int i = 0; i < $4.param_count; i++) {
                    params[i] = $4.params[i];
                }

                printf("Llamada a función %s\n", $2);
                func->func_body(params); 
            }
        }
    }
;


PARAMS:
     { 
        $$ = (struct FunctionParams){0, {0}}; 
    }
    | OPERATION {
        $$ = (struct FunctionParams){1, {0}};
        $$.params[0] = $1;
    }
    | PARAMS COMA OPERATION {
        $1.param_count++;
        $1.params[$1.param_count - 1] = $3;
        $$ = $1;
    }
    ;

%%
void imprimir(void* value, int tipo) {
    if (tipo == 0) {  // Es un entero
        printf("%d\n", *(int*)value);
    } else if (tipo == 1) {  // Es una cadena
        printf("%s\n", (char*)value);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {

    FILE *archivo = fopen(argv[1], "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return 1;
    }

    yyin = archivo;
    yyparse();
    fclose(archivo);
    return 0;
}
