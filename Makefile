# Makefile para compilar proyectos p1 y p2 con GTK

# Especificar el compilador y las opciones de compilación
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
GTKFLAGS = `pkg-config --cflags --libs gtk+-3.0`

# Target predeterminado: compilar ambos proyectos
.PHONY: all clean
all: p1 p2

# Target para compilar proyecto1.c y generar el ejecutable llamado exe
p1: proyecto1.c
	$(CC) $(CFLAGS) $< -o exe $(GTKFLAGS)

# Target para compilar proyecto2.c y generar el ejecutable llamado exe
p2: proyecto2.c
	$(CC) $(CFLAGS) $< -o exe

# Target para limpiar los ejecutables generados
clean:
	rm -f exe
