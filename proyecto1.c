/* 
Estudiantes: José Andrés Rodríguez Vásquez B46007
             Gerson Cuadra Obando C22492
             Victor Jaffeth Sandoval Sandoval C07370

Este programa de C el código comienza con la inclusión de las bibliotecas 
necesarias para el proyecto, específicamente `<gtk/gtk.h>` para GTK+ y `<stdio.h>` 
para operaciones de entrada y salida estándar. Inicializamos el estado del juego con
todos los botones del tablero como `NULL` y establecemos el primer jugador en 'X'.
*/




#include <gtk/gtk.h>
#include <stdio.h>

typedef struct {
    GtkWidget *buttons[3][3]; // Matriz de botones para el tablero
    char currentPlayer;       // 'X' o 'O'
} GameState;

GameState gameState = {
    {
        {NULL, NULL, NULL},
        {NULL, NULL, NULL},
        {NULL, NULL, NULL}
    },
    'X'
}; // Inicialización del estado del juego

GtkApplication *app; // Declarar app como variable global

// Función para reiniciar el juego
void reset_game() {
    // Reiniciar el estado del juego
    gameState.currentPlayer = 'X';

    // Limpiar el tablero (resetear etiquetas de los botones)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gtk_button_set_label(GTK_BUTTON(gameState.buttons[i][j]), "");
        }
    }
}

// Función para mostrar un mensaje en pantalla con opción de reiniciar
void show_message_with_restart(const char *message) {
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_NONE,
                                    "%s", message);
    
    // Añadir el botón "Reiniciar" al diálogo
    gtk_dialog_add_button(GTK_DIALOG(dialog), "Reiniciar", 1);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    
    if (result == 1) {
        reset_game(); // Reiniciar el juego si se selecciona "Reiniciar"
    }

    gtk_widget_destroy(dialog);
}

// Función para revisar si hay un ganador
char check_winner() {
    char board[3][3] = {{0}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            const char *label = gtk_button_get_label(GTK_BUTTON(gameState.buttons[i][j]));
            board[i][j] = label[0]; // 'X', 'O', o '\0' (nulo) si el botón está vacío
        }
    }

    // Revisar filas, columnas y diagonales para encontrar un ganador
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '\0') {
            show_message_with_restart(g_strdup_printf("¡El ganador es %c!", board[i][0]));
            return board[i][0];
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '\0') {
            show_message_with_restart(g_strdup_printf("¡El ganador es %c!", board[0][i]));
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '\0') {
        show_message_with_restart(g_strdup_printf("¡El ganador es %c!", board[0][0]));
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '\0') {
        show_message_with_restart(g_strdup_printf("¡El ganador es %c!", board[0][2]));
        return board[0][2];
    }

    // Verificar si hay empate
    int emptyCount = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '\0') {
                emptyCount++;
            }
        }
    }
    if (emptyCount == 0) {
        show_message_with_restart("¡Empate!");
        return 'T';  // 'T' representa empate
    }

    return '\0'; // No hay ganador aún
}

// Callback para manejar clics en los botones
static void button_clicked(GtkWidget *button, gpointer) {
    // Si el botón ya está marcado, no hacer nada
    const char *label = gtk_button_get_label(GTK_BUTTON(button));
    if (g_strcmp0(label, "") == 0) {
        // Marcar el botón con el jugador actual
        gtk_button_set_label(GTK_BUTTON(button), gameState.currentPlayer == 'X' ? "X" : "O");

        // Verificar si hay un ganador después del movimiento
        char winner = check_winner();
        if (winner != '\0' && winner != 'T') {
            // printf("El ganador es %c\n", winner); // Comentado para mostrar el mensaje con show_message_with_restart
            // Aquí podrías también mostrar un diálogo o realizar alguna acción para indicar el fin del juego
        }

        // Cambiar el jugador
        gameState.currentPlayer = (gameState.currentPlayer == 'X') ? 'O' : 'X';
    }
}

static void activate(GtkApplication *app, gpointer) {
    GtkWidget *window;
    GtkWidget *grid;
    int i, j;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Tic Tac Toe");
    gtk_window_set_default_size(GTK_WINDOW(window), 240, 240); // Tamaño inicial de la ventana
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);       // Bloquear la redimensión de la ventana

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            gameState.buttons[i][j] = gtk_button_new_with_label("");
            gtk_widget_set_size_request(gameState.buttons[i][j], 80, 80);  // Aumentar el tamaño de los botones
            g_signal_connect(gameState.buttons[i][j], "clicked", G_CALLBACK(button_clicked), NULL);
            gtk_grid_attach(GTK_GRID(grid), gameState.buttons[i][j], j, i, 1, 1);
        }
    }

    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    app = gtk_application_new("org.example.tictactoe", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
