
flex lexer.l || { echo "Error al compilar lexer.l"; exit 1; }

bison -d parser.y || { echo "Error al compilar parser.y"; exit 1; }

gcc lex.yy.c parser.tab.c -o lenguaje -lm || { echo "Error al compilar con GCC"; exit 1; }

echo "Compilacion exitosa. Ejecuta ./lenguaje para probar."
