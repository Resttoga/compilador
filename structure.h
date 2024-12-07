#define MAX_PARAMS 10

// Estructura para listas de parámetros de funciones
struct ParamList {
    int param_count;
    char param_names[MAX_PARAMS][100];
};

// Estructura para parámetros de funciones durante la ejecución
struct FunctionParams {
    int param_count;
    int params[MAX_PARAMS];
};

// Estructura para el cuerpo de una función
struct FuncBody {
    int (*func)(int *params); // Puntero a una función
};

// Estructura para funciones declaradas
struct Function {
    char name[100];
    char param_names[MAX_PARAMS][100];
    int param_count;
    int (*func_body)(int *params); // Puntero a función
};

// Prototipos de funciones que se usan en el análisis
void some_predefined_function(int params[]);