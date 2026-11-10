#include "grammar.h"

using namespace std;

// Datos de la gramatica.
map<int, Production> productions;
set<string> terminals;
set<string> nonterminals;

const string epsilon = "epsilon";
const string initialSymbol = "Programa";

void loadGrammar() {

    // Los numeros se conservan iguales a los del documento LL(1).
    // productions[11] es la regla numero 11.
    // productions[11].left indica su lado izquierdo.
    // productions[11].right indica su lado derecho.
    productions.clear();

    productions[1] = {"ListaVariables", {"Variable", "ListaVariablesPrima"}};
    productions[2] = {"ListaVariablesPrima", {"PUNCTUATION_COMMA", "Variable", "ListaVariablesPrima"}};
    productions[3] = {"ListaVariablesPrima", {}};
    productions[4] = {"Variable", {"TOKEN_IDENTIFIER", "InicializacionOpc"}};
    productions[5] = {"InicializacionOpc", {"OPERATOR_ASSIGN", "Asignacion"}};
    productions[6] = {"InicializacionOpc", {}};
    productions[7] = {"ListaArgumentos", {"Expresion", "ListaArgumentosPrima"}};
    productions[8] = {"ListaArgumentos", {}};
    productions[9] = {"ListaArgumentosPrima", {"PUNCTUATION_COMMA", "Expresion", "ListaArgumentosPrima"}};
    productions[10] = {"ListaArgumentosPrima", {}};
    productions[11] = {"ParametrosOpc", {"ListaParametros"}};
    productions[12] = {"ParametrosOpc", {}};
    productions[13] = {"ListaParametros", {"Parametro", "ListaParametrosPrima"}};
    productions[14] = {"ListaParametrosPrima", {"PUNCTUATION_COMMA", "Parametro", "ListaParametrosPrima"}};
    productions[15] = {"ListaParametrosPrima", {}};
    productions[16] = {"Parametro", {"Tipo", "TOKEN_IDENTIFIER"}};
    productions[17] = {"Tipo", {"KEYWORD_INT"}};
    productions[18] = {"Tipo", {"KEYWORD_FLOAT"}};
    productions[19] = {"Tipo", {"KEYWORD_CHAR"}};
    productions[20] = {"Tipo", {"KEYWORD_STRING"}};
    productions[21] = {"TipoFuncion", {"Tipo"}};
    productions[22] = {"TipoFuncion", {"KEYWORD_VOID"}};
    productions[23] = {"Expresion", {"Termino", "ExpresionPrima"}};
    productions[24] = {"ExpresionPrima", {"OPERATOR_PLUS", "Termino", "ExpresionPrima"}};
    productions[25] = {"ExpresionPrima", {"OPERATOR_MINUS", "Termino", "ExpresionPrima"}};
    productions[26] = {"ExpresionPrima", {}};
    productions[27] = {"Termino", {"Unario", "TerminoPrima"}};
    productions[28] = {"TerminoPrima", {"OPERATOR_MULT", "Unario", "TerminoPrima"}};
    productions[29] = {"TerminoPrima", {"OPERATOR_DIV", "Unario", "TerminoPrima"}};
    productions[30] = {"TerminoPrima", {}};
    productions[31] = {"Unario", {"OPERATOR_PLUS", "Unario"}};
    productions[32] = {"Unario", {"OPERATOR_MINUS", "Unario"}};
    productions[33] = {"Unario", {"Primario"}};
    productions[34] = {"Primario", {"TOKEN_CONSTANT"}};
    productions[35] = {"Primario", {"TOKEN_LITERAL"}};
    productions[36] = {"Primario", {"TOKEN_IDENTIFIER", "LlamadaFuncionPrima"}};
    productions[37] = {"Primario", {"PUNCTUATION_LPAREN", "Expresion", "PUNCTUATION_RPAREN"}};
    productions[38] = {"LlamadaFuncionPrima", {"PUNCTUATION_LPAREN", "ListaArgumentos", "PUNCTUATION_RPAREN"}};
    productions[39] = {"LlamadaFuncionPrima", {}};
    productions[40] = {"Declaracion", {"Tipo", "ListaVariables", "PUNCTUATION_SEMICOLON"}};
    productions[41] = {"Asignacion", {"TOKEN_IDENTIFIER", "ContinuarAsignacion"}};
    productions[42] = {"Asignacion", {"InicioSinId", "ContinuarExpresion"}};
    productions[43] = {"ContinuarAsignacion", {"OPERATOR_ASSIGN", "Asignacion"}};
    productions[44] = {"ContinuarAsignacion", {"LlamadaFuncionPrima", "ContinuarExpresion"}};
    productions[45] = {"ContinuarExpresion", {"TerminoPrima", "ExpresionPrima"}};
    productions[46] = {"InicioSinId", {"TOKEN_CONSTANT"}};
    productions[47] = {"InicioSinId", {"TOKEN_LITERAL"}};
    productions[48] = {"InicioSinId", {"PUNCTUATION_LPAREN", "Expresion", "PUNCTUATION_RPAREN"}};
    productions[49] = {"InicioSinId", {"OPERATOR_PLUS", "Unario"}};
    productions[50] = {"InicioSinId", {"OPERATOR_MINUS", "Unario"}};
    productions[51] = {"Comparacion", {"Expresion", "ComparacionOpc"}};
    productions[52] = {"ComparacionOpc", {"OperadorComparacion", "Expresion"}};
    productions[53] = {"ComparacionOpc", {}};
    productions[54] = {"OperadorComparacion", {"OPERATOR_EQUAL"}};
    productions[55] = {"OperadorComparacion", {"OPERATOR_GREATER_EQUAL"}};
    productions[56] = {"OperadorComparacion", {"OPERATOR_LESS_EQUAL"}};
    productions[57] = {"OperadorComparacion", {"OPERATOR_GREATER"}};
    productions[58] = {"OperadorComparacion", {"OPERATOR_LESS"}};
    productions[59] = {"OperadorComparacion", {"OPERATOR_NOT_EQUAL"}};
    productions[60] = {"ListaComparaciones", {"Conjuncion", "ListaComparacionesPrima"}};
    productions[61] = {"ListaComparacionesPrima", {"OPERATOR_OR", "Conjuncion", "ListaComparacionesPrima"}};
    productions[62] = {"ListaComparacionesPrima", {}};
    productions[63] = {"Conjuncion", {"ComparacionLogica", "ConjuncionPrima"}};
    productions[64] = {"ConjuncionPrima", {"OPERATOR_AND", "ComparacionLogica", "ConjuncionPrima"}};
    productions[65] = {"ConjuncionPrima", {}};
    productions[66] = {"ComparacionLogica", {"Comparacion"}};
    productions[67] = {"ComparacionLogica", {"OPERATOR_NOT", "PUNCTUATION_LPAREN", "Comparacion", "PUNCTUATION_RPAREN"}};
    productions[68] = {"Bloque", {"PUNCTUATION_LBRACE", "ListaSentencias", "PUNCTUATION_RBRACE"}};
    productions[69] = {"ListaSentencias", {"Sentencia", "ListaSentencias"}};
    productions[70] = {"ListaSentencias", {}};
    productions[71] = {"Sentencia", {"Declaracion"}};
    productions[72] = {"Sentencia", {"Asignacion", "PUNCTUATION_SEMICOLON"}};
    productions[73] = {"Sentencia", {"SentenciaRetorno"}};
    productions[74] = {"Sentencia", {"SentenciaCondicional"}};
    productions[75] = {"Sentencia", {"SentenciaFor"}};
    productions[76] = {"Sentencia", {"SentenciaWhile"}};
    productions[77] = {"Sentencia", {"Bloque"}};
    productions[78] = {"Sentencia", {"PUNCTUATION_SEMICOLON"}};
    productions[79] = {"SentenciaCondicional", {"KEYWORD_IF", "PUNCTUATION_LPAREN", "ListaComparaciones", "PUNCTUATION_RPAREN", "Bloque", "ElseOpcional"}};
    productions[80] = {"ElseOpcional", {"KEYWORD_ELSE", "Bloque"}};
    productions[81] = {"ElseOpcional", {}};
    productions[82] = {"SentenciaFor", {"KEYWORD_FOR", "PUNCTUATION_LPAREN", "InicializacionFor", "PUNCTUATION_SEMICOLON", "ListaComparaciones", "PUNCTUATION_SEMICOLON", "ActualizacionFor", "PUNCTUATION_RPAREN", "Bloque"}};
    productions[83] = {"InicializacionFor", {"Tipo", "ListaVariables"}};
    productions[84] = {"InicializacionFor", {"Asignacion"}};
    productions[85] = {"InicializacionFor", {}};
    productions[86] = {"ActualizacionFor", {"Asignacion"}};
    productions[87] = {"SentenciaWhile", {"KEYWORD_WHILE", "PUNCTUATION_LPAREN", "ListaComparaciones", "PUNCTUATION_RPAREN", "Bloque"}};
    productions[88] = {"DefinicionFuncion", {"TipoFuncion", "TOKEN_IDENTIFIER", "PUNCTUATION_LPAREN", "ParametrosOpc", "PUNCTUATION_RPAREN", "Bloque"}};
    productions[89] = {"SentenciaRetorno", {"KEYWORD_RETURN", "Asignacion", "PUNCTUATION_SEMICOLON"}};
    productions[90] = {"Programa", {"ElementoGlobal", "Programa"}};
    productions[91] = {"Programa", {}};
    productions[92] = {"ElementoGlobal", {"Tipo", "TOKEN_IDENTIFIER", "ContinuacionGlobal"}};
    productions[93] = {"ElementoGlobal", {"KEYWORD_VOID", "TOKEN_IDENTIFIER", "PUNCTUATION_LPAREN", "ParametrosOpc", "PUNCTUATION_RPAREN", "Bloque"}};
    productions[94] = {"ContinuacionGlobal", {"PUNCTUATION_LPAREN", "ParametrosOpc", "PUNCTUATION_RPAREN", "Bloque"}};
    productions[95] = {"ContinuacionGlobal", {"InicializacionOpc", "ListaVariablesPrima", "PUNCTUATION_SEMICOLON"}};

    // Estas son las variables de la gramatica (no terminales).
    nonterminals = {
        "ListaVariables", "ListaVariablesPrima", "Variable", "InicializacionOpc",
        "ListaArgumentos", "ListaArgumentosPrima", "ParametrosOpc", "ListaParametros",
        "ListaParametrosPrima", "Parametro", "Tipo", "TipoFuncion",
        "Expresion", "ExpresionPrima", "Termino", "TerminoPrima",
        "Unario", "Primario", "LlamadaFuncionPrima", "Declaracion",
        "Asignacion", "ContinuarAsignacion", "ContinuarExpresion", "InicioSinId",
        "Comparacion", "ComparacionOpc", "OperadorComparacion", "ListaComparaciones",
        "ListaComparacionesPrima", "Conjuncion", "ConjuncionPrima", "ComparacionLogica",
        "Bloque", "ListaSentencias", "Sentencia", "SentenciaCondicional",
        "ElseOpcional", "SentenciaFor", "InicializacionFor", "ActualizacionFor",
        "SentenciaWhile", "DefinicionFuncion", "SentenciaRetorno", "Programa",
        "ElementoGlobal", "ContinuacionGlobal"
    };

    // Estos son los simbolos que llegan desde el analizador lexico.
    // TOKEN_EOF marca el final de la entrada.
    terminals = {
        "PUNCTUATION_COMMA", "TOKEN_IDENTIFIER", "OPERATOR_ASSIGN",
        "KEYWORD_INT", "KEYWORD_FLOAT", "KEYWORD_CHAR",
        "KEYWORD_STRING", "KEYWORD_VOID", "OPERATOR_PLUS",
        "OPERATOR_MINUS", "OPERATOR_MULT", "OPERATOR_DIV",
        "TOKEN_CONSTANT", "TOKEN_LITERAL", "PUNCTUATION_LPAREN",
        "PUNCTUATION_RPAREN", "PUNCTUATION_SEMICOLON", "OPERATOR_EQUAL",
        "OPERATOR_GREATER_EQUAL", "OPERATOR_LESS_EQUAL", "OPERATOR_GREATER",
        "OPERATOR_LESS", "OPERATOR_NOT_EQUAL", "OPERATOR_OR",
        "OPERATOR_AND", "OPERATOR_NOT", "PUNCTUATION_LBRACE",
        "PUNCTUATION_RBRACE", "KEYWORD_IF", "KEYWORD_ELSE",
        "KEYWORD_FOR", "KEYWORD_WHILE", "KEYWORD_RETURN",
        "TOKEN_EOF"
    };
}
