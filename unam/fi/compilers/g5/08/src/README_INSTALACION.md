# Compilador LL(1) + SDT (C++17)

Esta entrega integra un árbol sintáctico concreto (ParseTree) en el parser LL(1), y un
analizador semántico independiente (SDT) con tabla de símbolos y ámbitos.

## Instalación en tu proyecto

Desde tu carpeta `src`, **haz un respaldo** antes de sustituir archivos.

### Nuevos
- `Parser/parse_tree.h`
- `Parser/parse_tree.cpp`
- `SDT/sdt.h`
- `SDT/sdt.cpp`
- `SDT/symbol_table.h`
- `SDT/symbol_table.cpp`

### Reemplazar (necesarios para integrar el SDT)
- `Parser/parser.h`
- `Parser/parser.cpp`
- `main.cpp`

### Reemplazos de cabeceras (recomendados)
- `Token/token.h`
- `Parser/grammar.h`
- `Parser/first_follow.h`
- `Parser/parsing_table.h`
- `Lexer/lexer_utils.h`

Estas cabeceras incluyen guardas para evitar redefiniciones. No hay que cambiar las
producciones de `grammar.cpp`, ni FIRST/FOLLOW, ni la tabla predictiva.

El ZIP también incluye copias sin modificar funcionalmente de los demás `.cpp`, `.re`,
para que puedas copiar el árbol entero si lo prefieres. **El `.cpp` generado por re2c no
está incluido**; debes generarlo con tu versión instalada de re2c.

## Generar lexer, compilar y ejecutar

Desde `src`:

```bash
re2c -o Lexer/lexer.cpp Lexer/lexer.re
g++ -std=c++17 main.cpp Lexer/*.cpp Token/*.cpp Parser/*.cpp SDT/*.cpp \
    -I Token -I Parser -I Lexer -I SDT -o main
./main
```

IMPORTANTE: El comando de compilación ahora incluye `SDT/*.cpp`.

## Cómo probar

`main.cpp` sigue leyendo `cadena_de_prueba.txt` (desde el directorio de ejecución).
Para probar uno de los casos suministrados:

```bash
cp tests/02_tipo_incompatible.txt cadena_de_prueba.txt
./main
```

Los casos están en `tests/`. El archivo `cadena_de_prueba.txt` se incluye como ejemplo:
respalda tu versión antes de copiarlo si ya tienes pruebas propias.

## Funcionalidad semántica implementada

- Construcción del árbol desde las producciones LL(1); terminales guardan índice de token.
- Registro de variables y funciones globales, con doble pasada para admitir llamadas a
  funciones definidas después.
- Tabla de símbolos con ámbitos (funciones, bloques y for).
- Detección de identificadores no declarados y duplicados en el mismo ámbito.
- Tipos de inicialización y asignación, y operaciones aritméticas.
- Comprobación de condiciones, de argumentos de funciones y de tipos de retorno.
- Errores con número de línea; se detiene tras el primer error semántico.
- Política de conversiones del SDT: identidad, char->int, y tipos numéricos a float.

## Límites actuales

- No es un compilador C completo: se validan las estructuras de la gramática de 95
  reglas. No se ejecuta el programa ni se genera código máquina.
- No se exige que toda función no-void tenga una sentencia return en cada camino.
- No se analiza el uso de variables antes de ser inicializadas.
- El lenguaje acepta literales de cadena como `string`; no cubre todos los literales C.
- La gramática original requiere una expresión en `return` y no admite `return;`.
- El análisis de tipos aplica las reglas documentadas arriba, no la semántica completa
  de conversiones y promoción de tipos de C.
- El árbol se guarda en memoria y se puede imprimir con `printParseTree(tree,tokens,cout)`;
  por defecto no se imprime para mantener limpia la salida.

## Pruebas de compilación

El parser + SDT se compilaron y se probaron mediante un harness de tokens, incluyendo:
programa válido; incompatibilidad de tipos; duplicados; variable no declarada;
retorno incompatible; operaciones aritméticas; llamadas a función; error de argumentos;
y condicionales. En el entorno de preparación no estaba disponible `re2c`, por lo que
**no se verificó el ejecutable final compilando el scanner generado**; ese paso se
realiza con el comando anterior en tu máquina.
