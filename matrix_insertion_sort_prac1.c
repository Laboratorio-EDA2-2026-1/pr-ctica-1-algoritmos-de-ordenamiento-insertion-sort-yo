#include <stdio.h>
#include <stdlib.h>

/*
 * EJERCICIO:
 * Se quiere definir un programa que, dada una matriz cuadrada con valores enteros,
 * devuelva una permutación de los valores de modo que:
 *
 * 1. Cada renglón esté ordenado de menor a mayor.
 * 2. Todos los elementos del segundo renglón (de arriba hacia abajo)
 *    sean mayores que los del primero, los del tercero mayores que los del segundo, etc.
 *
 * Regla importante:
 * - Cuando se ordenan los elementos de un renglón, por cada elemento de dicho renglón,
 *   se mueven también todos los elementos que se encuentran por debajo en la misma columna.
 *
 * INSTRUCCIONES:
 * - Completa la función sort_matrix() que debe modificar la matriz en su lugar.
 * - Puedes escribir funciones auxiliares si lo deseas.
 * - NO cambies la firma de sort_matrix().
 */

void sort_matrix(int **matrix, int n, int **matrix2) { // int **matrix2: retorna la matriz matrix2 para poder usarla afuera de la función (para imprimir)
    // TODO: Implementa aquí el algoritmo.
    // Necesitarás el método de inserción,
    // pero recuerda aplicar la regla de mover toda la columna.

    int i, j, k, x, y, salida2, cambio;

    for (i = 0; i < n; i++) { 
        for (j = 1; j < n; j++) { // empieza desde el segundo elemento
            x = matrix[i][j]; // elemento a insertar
            k = j - 1;
            
            // Desplaza los elementos mayores hacia la derecha
            while (k >= 0 && matrix[i][k] > x) {
                matrix[i][k+1] = matrix[i][k]; // mueve elemento mayor
                // Propaga el movimiento hacia abajo en la columna
                for (int r = i+1; r < n; r++) {
                    y = matrix[r][k+1];
                    matrix[r][k+1] = matrix[r][k];
                    matrix[r][k] = y;
                }
                k--;
            }
            matrix[i][k+1] = x; // coloca el elemento en su posición correcta
        }
    }

    // Esta parte del código ordena toda la matriz de mayor a menor siguiendo las instrucciones anteriores: si se intercambian dos valores tambien se cambian los elementos que estan debajo
    // Copia la matriz ya parcialmente ordenada "matrix" dentro de "matrix2" para seguir trabajado con ella 
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matrix2[i][j] = matrix[i][j];
        }
    }

    salida2 = 1; // bandera que asegura que el ciclo se ejecute y continúe mientras haya cambios
    while (salida2) {
        salida2 = 0; // reinicia al inicio del ciclo
        
        for (i = 0; i < n-1; i++) { 
            for (j = 0; j < n; j++) { 
                if (matrix2[i][n-1] > matrix2[i+1][j]) { // último de fila i > elemento de fila i+1
                    // Intercambia los elementos
                    x = matrix2[i][n-1];
                    matrix2[i][n-1] = matrix2[i+1][j];
                    matrix2[i+1][j] = x;

                    salida2 = 1; // como hubo un cambio, hay que seguir verificando

                    // Reordenar cada fila usando Insertion Sort
                    for (int ii = 0; ii < n; ii++) {
                        for (int jj = 1; jj < n; jj++) {
                            x = matrix2[ii][jj];
                            k = jj - 1;
                            while (k >= 0 && matrix2[ii][k] > x) {
                                matrix2[ii][k+1] = matrix2[ii][k];
                                // Propagar hacia abajo
                                for (int r = ii+1; r < n; r++) {
                                    y = matrix2[r][k+1];
                                    matrix2[r][k+1] = matrix2[r][k];
                                    matrix2[r][k] = y;
                                }
                                k--;
                            }
                            matrix2[ii][k+1] = x;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n = 3;
    // Reserva dinámica de la matriz
    int **matrix = (int **)malloc(n * sizeof(int *));
    int **matrix2 = malloc(n * sizeof(int *)); // se reserva memoria para la segunda matriz (matrix2)
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
        matrix2[i] = malloc(n * sizeof(int)); // Se reserva memoria para "n" enteros 
    }

    // Ejemplo de entrada
    int ejemplo[3][3] = {
        {4, 7, 2},
        {9, 5, 6},
        {8, 1, 3}
    };

    // Copiar ejemplo a la matriz dinámica
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ejemplo[i][j];
        }
    }

    printf("Matriz original:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Llamada a la función que deben completar
    sort_matrix(matrix, n, matrix2);

    printf("\nMatriz ordenada:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    //Imprime la matriz totalmente ordenada matrix2
    printf("\nMatriz totalmente ordenada:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix2[i][j]);
        }
        printf("\n");
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(matrix2[i]);
    }
    free(matrix);
    free(matrix2);

    return 0;
}