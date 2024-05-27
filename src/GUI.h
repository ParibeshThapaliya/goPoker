#ifndef GUI_H
#define GUI_H

#define SQUARE_SIZE 100
#define WINDOW_WIDTH (12*SQUARE_SIZE)
#define WINDOW_HEIGHT (8*SQUARE_SIZE)
#define WINDOW_BORDER 10

//initialize gtk application
void init_gui(int *argc, char ***argv);

//create main window
GtkWidget* create_main_window(void);

//update game state in GUI
void update_game_state(void);

//display message to user
void show_message(const char *message);

#endif //GUI_H
