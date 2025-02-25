#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>

#define SQUARE_SIZE 100
#define WINDOW_WIDTH (12 * SQUARE_SIZE)
#define WINDOW_HEIGHT (8 * SQUARE_SIZE)
#define WINDOW_BORDER 10
 static void destroy(GtkWidget *widget, gpointer data);

// initialize gtk application
void init_gui( GtkWidget **main_window);
enum GameState
{
    MENU,
    GAME
};
void load_image(GtkWidget *window, char *file);
struct Player
{
    GtkWidget *Player_Name;
    GtkWidget *playerCurrentBet;
    GtkWidget *player_hand;
    GtkWidget *playerPot;
};
struct MENUSCENE
{
    GtkWidget *name_feild;
    GtkWidget *connect_button;
    GtkWidget *poker_text;
};
struct GAMESCENE
{
    GtkWidget *poker_table;
    struct Player Players[4];
    GtkWidget *common_cards;
};

#endif // GUI_H
