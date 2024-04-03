#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Función para escribir un token en el archivo de salida
void escribirToken(FILE *output, const char *token) {
    fprintf(output, "%s", token);
}

int main() {
    FILE *archivo;
    FILE *salida;
    archivo = fopen("fuente.txt", "r");
    salida = fopen("output.txt", "w");

    if (archivo == NULL || salida == NULL) {
        perror("Error al abrir el archivo");
        return 1;
    }
  
    // Define el estado inicial y los estados posibles
    enum { INICIAL, BOOLEAN_T, BOOLEAN_F, STRING, NUMBER, PR_NULL } estado = INICIAL;

    char caracter;

    while ((caracter = fgetc(archivo)) != EOF) {
        switch (estado) {
            case INICIAL:
                if (caracter == '{') {
                    escribirToken(salida, "L_LLAVE ");
                }
                if (caracter == '}') {
                    escribirToken(salida, "R_LLAVE ");
                }
                if (caracter == '[') {
                    escribirToken(salida, "L_CORCHETE ");
                }
                if (caracter == ']') {
                    escribirToken(salida, "R_CORCHETE ");
                }
                if (caracter == '"') {
                    estado = STRING;
                }
                if(caracter == ':') {
                    escribirToken(salida, "DOS_PUNTOS ");
                } 
                if (caracter == ',') {
                    escribirToken(salida, "COMA ");
                }
                if (caracter == ' ') {
                    escribirToken(salida, " ");
                }
                if (caracter == '\n') {
                    escribirToken(salida, "\n");
                }
                if (caracter == 'n' || caracter == 'N') {
                    estado = PR_NULL;
                }
                if (caracter == 't' || caracter == 'T') {
                    estado = BOOLEAN_T;
                }
                if(caracter == 'f' || caracter == 'F'){
                    estado = BOOLEAN_F;
                }
                if (isdigit(caracter)) {
                    estado = NUMBER;
                }
            break;
            case STRING:
                if (caracter == '"') {
                    escribirToken(salida, "STRING ");
                    estado = INICIAL;
                }
            break;
            case NUMBER:
                if (!isdigit(caracter)){
                    if(caracter == '.' || caracter == 'e' || caracter == 'E'){
                        estado = INICIAL;
                    } else {
                        escribirToken(salida, "NUMBER ");
                        if(caracter == ','){
                            escribirToken(salida, "COMA ");
                        }else if(caracter == '\n'){
                            escribirToken(salida, "\n");
                        }else if(caracter == ' '){
                            escribirToken(salida, " ");
                        }else {
                            printf("ERROR DE SINTAXIS");
                            return 0;
                        }
                        estado = INICIAL;
                    }
                }
            break;
            case BOOLEAN_T:
                if (caracter == 'e' || caracter == 'E'){
                    escribirToken(salida, "PR_TRUE ");
                    estado = INICIAL;
                }
            break;
            case BOOLEAN_F:
                if (caracter == 'e' || caracter == 'E'){
                    escribirToken(salida, "PR_FALSE ");
                    estado = INICIAL;
                }
            break;
            case PR_NULL:
                if (caracter == 'l' || caracter == 'L'){
                    escribirToken(salida, "PR_NULL ");
                    estado = INICIAL;
                }
            break;
        }
    }

    fclose(archivo);
    fclose(salida);

    return 0;
}
