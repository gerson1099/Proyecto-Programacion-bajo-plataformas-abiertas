/* 
Estudiantes: José Andrés Rodríguez Vásquez B46007
             Gerson Cuadra Obando C22492
             Victor Jaffeth Sandoval Sandoval C07370

Este programa de C recibe dos funciones cuadráticas cualesquiera de la
forma ax^2+bx+c y un porcentaje de error (0-100 %), y encuentra el subdominio
donde la diferencia entre ambas funciones no supera el porcentaje de error.
El dominio de ambas funciones no es continuo, es: [-100000,100000] en pasos
de 0.1. Este script también muestra una figura con ambas curvas y el subdominio
encontrado (rectas verdes).
*/

// Incluir bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Se define la estructura de la función cuadrática 
typedef struct {
    double a, b, c;
} FuncionCuadratica;

// Se define una estructura para los datos a ingresar
typedef struct {
    FuncionCuadratica funcionF;
    FuncionCuadratica funcionG;
    double por_error;
} DatosCoeficientes;

// Mensaje de bienvenida y solicitar coeficientes y % de error
DatosCoeficientes solicitar() {
    DatosCoeficientes datos;
    // Mensaje de bienvenida y funcionamiento del programa
    printf("Bienvenido, este programa se encargará de calcular el subdominio");
    printf(" donde la diferencia entre dos polinomios cuadráticos cumpla con");
    printf(" un porcentaje error, así como también mostrar la gráfica con ambas");
    printf(" curvas y dicho subdominio. Para esto debes ingresar primero los");
    printf(" coeficientes y seguidamente el porcentaje de error. Los");
    printf(" polinomios deben ser de la forma: \n \n");
    printf("ax^2+bx+c \n");
    printf("dx^2+ex+f \n \n");
    printf("Iniciemos. \n");

    // Solicitar al usuario los coeficientes para la función F(x)
    printf("Ingrese los coeficientes para la función F(x):\n");
    printf("Coeficiente a: ");
    scanf("%lf", &datos.funcionF.a);
    printf("Coeficiente b: ");
    scanf("%lf", &datos.funcionF.b);
    printf("Coeficiente c: ");
    scanf("%lf", &datos.funcionF.c);

    // Solicitar al usuario los coeficientes para la función G(x)
    printf("\nIngrese los coeficientes para la función G(x):\n");
    printf("Coeficiente d: ");
    scanf("%lf", &datos.funcionG.a);
    printf("Coeficiente e: ");
    scanf("%lf", &datos.funcionG.b);
    printf("Coeficiente f: ");
    scanf("%lf", &datos.funcionG.c);

    // Solicitar al usuario el porcentaje de error (0-100)
    do {
        printf("\nIngrese un porcentaje de error entre 0 y 100: ");
        scanf("%lf", &datos.por_error);
    } while (datos.por_error < 0 || datos.por_error > 100); // Verificar que se encuentre en el rango (0-100)

    // Devuelve la información solicitada al usuario
    return datos;
}

// Crear el dominio x
void crear_dominio(double *x, int n) {
    double valor_inicial = -100000.0;
    for (int i = 0; i < n; i++) {
        x[i] = valor_inicial + i * 0.1;
    }
}

// Calcular las imágenes de F(x) y G(x)
void calcular_imagenes(double *x, double *fx, double *gx, int n, FuncionCuadratica funcionF, FuncionCuadratica funcionG) {
    for (int i = 0; i < n; i++) {
        fx[i] = funcionF.a * x[i] * x[i] + funcionF.b * x[i] + funcionF.c;
        gx[i] = funcionG.a * x[i] * x[i] + funcionG.b * x[i] + funcionG.c;
    }
}

// Se define la función para encontrar el índice de la raíz
int indice_raiz(double *vector1, double *vector2, int tamano) {
    double minima_diferencia = __DBL_MAX__; // Inicializa con un valor muy grande
    int indice_minima_diferencia = -1; // Inicia indefinido

    for (int i = 0; i < tamano; i++) {
        double diferencia = fabs(vector1[i] - vector2[i]);
        if (diferencia < minima_diferencia) { // Si la diferencia es menor
            minima_diferencia = diferencia; // Actualiza la mínima diferencia
            indice_minima_diferencia = i; // Indice de la raíz
        }
    }

    // Devuelve al índice de la raíz
    return indice_minima_diferencia;
}

// Encontrar el subdominio
// Extremo derecho
double ext_der(int indice, double imagen_gx, double por_error, double *x, double *fx, double *gx) {
    double ext_der = 0.0;
    int contador = indice; // Empezar desde la raíz
    for (int i = 0; i < 2000001; i++) {
        double error = fabs(imagen_gx) * 100.0 * fabs(fabs(fx[contador] - gx[contador]) / fx[contador]); // Calcular el error

        if (error > por_error) { // Si se supera el error
            ext_der = x[contador]; // Se guarda el extremo derecho
            break;
        }

        contador++; // Aumentar el contador (valor 'x')
    }

    // Devuelve el extremo derecho
    return ext_der;
}

// Extremo izquierdo
double ext_izq(int indice, double imagen_gx, double por_error, double *x, double *fx, double *gx) {
    double ext_izq = 0.0;
    int contador2 = indice; // Empezar desde la raíz
    for (int i = 0; i < 2000001; i++) {
        double error = fabs(imagen_gx) * 100.0 * fabs(fabs(fx[contador2] - gx[contador2]) / fx[contador2]); // Calcular el error

        if (error > por_error) { // Si se supera el error
            ext_izq = x[contador2]; // Se guarda el extremo izquierdo
            break;
        }

        contador2--; // Disminuir el contador (valor 'x')
    }

    // Devuelve el extremo izquierdo
    return ext_izq;
}

// Función para imprimir los resultados en pantalla
void imprimir_resultados(double raiz, double por_error, double ext_izq, double ext_der) {
    char porcentaje[20]; // Array para almacenar el porcentaje como string
    sprintf(porcentaje, "%.2f %%", por_error); // Convertir porcentaje a string

    // Imprimir los resultados en pantalla
    printf("La raíz es: %.2f\n", raiz);
    printf("El subdominio que cumple con el %.2f de error es: [%.2f, %.2f]\n", por_error, ext_izq, ext_der);

}

// Se crea la función para guardar los datos (2 mil datos)
void guardar_datos(double *x, double *fx, double *gx, int indice, int n) {
    // Abrir el archivo en modo de escritura
    FILE *archivo = fopen("datos.txt", "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }

    // Definir los índices de inicio y fin para el rango a guardar
    int indice_inicio = indice - 1000; // Mil valores antes de la raíz
    int indice_fin = indice + 1000; // Mil valores después de la raíz

    // Asegurarse de que los índices estén dentro de los límites del arreglo
    if (indice_inicio < 0) {
        indice_inicio = 0;
    }
    if (indice_fin >= n) {
        indice_fin = n - 1;
    }

    // Guardar los datos en el archivo
    for (int i = indice_inicio; i <= indice_fin; i++) {
        fprintf(archivo, "%lf %lf %lf\n", x[i], fx[i], gx[i]);
    }

    // Cerrar el archivo
    fclose(archivo);
}

// Crear la función para graficar los resultados
void graficar(double izquierda, double derecha, double imagen_gx) {
    // Abrir un canal de comunicación con Gnuplot
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe == NULL) { // Verificar si hay un error al abrir Gnuplot
        printf("Error al iniciar Gnuplot.\n");
        exit(EXIT_FAILURE);
    }

    // Calcular los límites de la gráfica
    double centro_x = (derecha + izquierda) / 2; // Centrar la gráfica con la raíz
    double rango_x = derecha - izquierda; // Rango a mostrar a partir de la raíz
    double rango_y = 10; // Rango a mostrar en el eje y

    // Límites de la gráfica (aumentar el rango de los límites)
    double lim_x_der = centro_x + (3 * rango_x);
    double lim_x_izq = centro_x - (3 * rango_x);
    double lim_y_sup = imagen_gx + (3 * rango_y);
    double lim_y_inf = imagen_gx - (3 * rango_y);

    // Configurar título y ejes
    fprintf(gnuplotPipe, "set title 'Gráfica del subdominio'\n");
    fprintf(gnuplotPipe, "set xlabel 'x'\n");
    fprintf(gnuplotPipe, "set ylabel 'y'\n");

    // Graficar F(x), G(x) y las líneas verticales del subdominio
    fprintf(gnuplotPipe, "plot 'datos.txt' using 1:2 with lines title 'F(x)' lc rgb 'blue', 'datos.txt' using 1:3 with lines title 'G(x)' lc rgb 'red', '-' with lines title 'x = %.2f' lc rgb 'green', '-' with lines title 'x = %.2f' lc rgb 'green'\n", izquierda, derecha);
    fprintf(gnuplotPipe, "%lf %lf\n%lf %lf\ne\n", izquierda, lim_y_inf, izquierda, lim_y_sup);
    fprintf(gnuplotPipe, "%lf %lf\n%lf %lf\ne\n", derecha, lim_y_inf, derecha, lim_y_sup);
    
    // Establecer los límites de la gráfica
    fprintf(gnuplotPipe, "set xrange [%.2f:%.2f]\n", lim_x_izq, lim_x_der); // Cambia el rango del eje X
    fprintf(gnuplotPipe, "set yrange [%.2f:%.2f]\n", lim_y_inf, lim_y_sup); // Cambia el rango del eje Y

    // Cerrar Gnuplot
    fprintf(gnuplotPipe, "replot\n"); // Actualizar la gráfica
    fprintf(gnuplotPipe, "pause -1\n"); // Esperar antes de cerrar la ventana
    fprintf(gnuplotPipe, "exit\n"); 
    pclose(gnuplotPipe);
}

// Función principal del programa
int main() {
    // Solicitar al usuario los coeficientes y el porcentaje de error
    DatosCoeficientes datos = solicitar();

    // Definir el tamaño del dominio y los vectores de imágenes
    const int n = 2000001;
    double *x = malloc(n * sizeof(double));
    double *fx = malloc(n * sizeof(double));
    double *gx = malloc(n * sizeof(double));

    // Crear el dominio
    crear_dominio(x, n);

    // Calcular las imágenes de F(x) y G(x)
    calcular_imagenes(x, fx, gx, n, datos.funcionF, datos.funcionG);

    // Encontrar el índice de la raíz
    int indice = indice_raiz(fx, gx, n);

    // Encontrar la raíz
    double raiz = x[indice];

    // Encontrar la imagen de G(x) en la raíz
    double imagen_gx = gx[indice];

    // Encontrar el subdominio
    double izquierda = ext_izq(indice, imagen_gx, datos.por_error, x, fx, gx);
    double derecha = ext_der(indice, imagen_gx, datos.por_error, x, fx, gx);

    // Imprimir los resultados
    imprimir_resultados(raiz, datos.por_error, izquierda, derecha);

    // Guardar los datos en un archivo para su posterior graficación
    guardar_datos(x, fx, gx, indice, n);

    // Graficar los resultados
    graficar(izquierda, derecha, imagen_gx);

    // Liberar memoria asignada a los vectores
    free(x);
    free(fx);
    free(gx);

    return 0;
}
