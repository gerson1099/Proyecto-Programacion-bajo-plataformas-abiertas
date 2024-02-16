# Proyectos de Programación con GTK+ y Gnuplot

Este repositorio contiene dos proyectos desarrollados en C:

1. **Proyecto 1:** Un juego de Tic Tac Toe (Tres en línea) utilizando la biblioteca gráfica GTK+.
2. **Proyecto 2:** Un programa que compara dos funciones cuadráticas con un porcentaje de error permitido, utilizando Gnuplot para la visualización.

## Proyecto 1: Tic Tac Toe (Tres en línea)

### Descripción
Un juego simple de Tic Tac Toe para dos jugadores, implementado en C con GTK+ para la interfaz de usuario.

### Compilación y Ejecución

#### Compilación
Para compilar el proyecto 1, utiliza el comando:

```bash
make p1
```

## Proyecto 1: Comparación de Funciones Cuadráticas

### Descripción
Este programa recibe dos funciones cuadráticas y un porcentaje de error permitido. Calcula un subdominio donde la diferencia entre ambas funciones no supera el porcentaje de error especificado por el usuario. Utiliza Gnuplot para graficar las curvas de las funciones cuadráticas y resalta el subdominio encontrado donde la diferencia está dentro del límite de error permitido.


### Compilación y Ejecución

#### Compilación
Para compilar el proyecto 2, utiliza el comando:

```bash
make p2
```

### Ejecucion 
Para ejecutar cualquiera de los dos programas después de compilarlo, usa:
```bash
./exe
```

# Requisitos

- **GCC (GNU Compiler Collection):** Para la compilación de ambos proyectos.
- **GTK+ 3.0 o superior:** Necesario para el Proyecto 1.
- **Gnuplot:** Requerido para el Proyecto 2, para la generación de gráficos.

# Instrucciones Generales

- El código fuente del **Proyecto 1** se encuentra en `proyecto1.c`.
- El código fuente del **Proyecto 2** se encuentra en `proyecto2.c`.
- Ambos proyectos se compilan a un ejecutable denominado `exe` mediante los comandos específicos `make p1` y `make p2` en el Makefile incluido.


