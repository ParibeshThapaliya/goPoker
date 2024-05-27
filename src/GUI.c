#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

#include "GUI.h"

// Global variables
GtkWidget *window;
GtkWidget *table;
GtkWidget *gametable;
GtkWidget *turncolor;
GtkWidget *startbtn;
GdkColor color;

//Edges table
GtkWidget *TableTop;
GtkWidget *TableBot;
GtkWidget *TableLeft;
GtkWidget *TableRight;

//Inside table
GtkWidget *TopRightFourTwo;
GtkWidget *BotRightFourTwo;
GtkWidget *TopLeftFourTwo;
GtkWidget *BotLeftFourTwo;
GtkWidget *TopLeftTwoTwo;
GtkWidget *TopRightTwoTwo;
GtkWidget *TopMiddle1;
GtkWidget *TopMiddle2;
GtkWidget *BotLeftTwoTwo;
GtkWidget *BotRightTwoTwo;
GtkWidget *BotMiddle1;
GtkWidget *BotMiddle2;
GtkWidget *MiniTop;
GtkWidget *MiniBot;
GtkWidget *MiniLeft;
GtkWidget *MiniRight;
GtkWidget *Middle1;
GtkWidget *Middle2;
GtkWidget *Middle3;

const char *RedBox = "./assets/table/redbox.png";
const char *GreenBox = "./assets/table/greenbox.png";

// Function declarations
void startbtnclicked(GtkWidget *widget, gpointer data);
GtkWidget* create_image_widget(const char *filepath, int width, int height);

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_title(GTK_WINDOW(window), "Poker");
    gtk_container_set_border_width(GTK_CONTAINER(window), WINDOW_BORDER);
    gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT);

    gdk_color_parse("#D2B48C", &color);
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

    table = gtk_table_new(WINDOW_HEIGHT, WINDOW_WIDTH, TRUE);
    gametable = gtk_table_new(13, 10, TRUE);

    turncolor = gtk_image_new_from_file(RedBox);
    gtk_table_attach(GTK_TABLE(table), turncolor, 20, 22, 4, 6, GTK_FILL, GTK_FILL, 0, 0);

    // Start button
    startbtn = gtk_button_new_with_label("Start");
    gtk_table_attach(GTK_TABLE(table), startbtn, 15, 19, 8, 10, GTK_FILL, GTK_FILL, 0, 0);
    g_signal_connect(startbtn, "clicked", G_CALLBACK(startbtnclicked), NULL);

    //Creating table edges
    TableTop = gtk_image_new_from_file("./assets/table/topleft.png");
    gtk_widget_set_size_request((GtkWidget *)TableTop, 650, 50);
    gtk_table_attach(GTK_TABLE(gametable), TableTop,  0, 13, 0, 1, GTK_FILL, GTK_FILL, 0, 0);
    TableBot = gtk_image_new_from_file("./assets/table/botleft.png");
    gtk_widget_set_size_request((GtkWidget *)TableBot, 650, 50);
    gtk_table_attach(GTK_TABLE(gametable), TableBot,  0, 13, 9, 10, GTK_FILL, GTK_FILL, 0, 0);
    TableLeft = gtk_image_new_from_file("./assets/table/leftside.png");
    gtk_widget_set_size_request((GtkWidget *)TableLeft, 50, 400);
    gtk_table_attach(GTK_TABLE(gametable), TableLeft,  0, 1, 1, 9, GTK_FILL, GTK_FILL, 0, 0);
    TableRight = gtk_image_new_from_file("./assets/table/rightside.png");
    gtk_widget_set_size_request((GtkWidget *)TableRight, 50, 400);
    gtk_table_attach(GTK_TABLE(gametable), TableRight,  12, 13, 1, 9, GTK_FILL, GTK_FILL, 0, 0);

    //Inner
    TopRightFourTwo = gtk_image_new_from_file("./assets/table/2by4square.png");
    gtk_widget_set_size_request((GtkWidget *)TopRightFourTwo, 100, 200);
    BotRightFourTwo = gtk_image_new_from_file("./assets/table/2by4square.png");
    gtk_widget_set_size_request((GtkWidget *)BotRightFourTwo, 100, 200);
    TopLeftFourTwo = gtk_image_new_from_file("./assets/table/2by4square.png");
    gtk_widget_set_size_request((GtkWidget *)TopLeftFourTwo, 100, 200);
    BotLeftFourTwo = gtk_image_new_from_file("./assets/table/2by4square.png");
    gtk_widget_set_size_request((GtkWidget *)BotLeftFourTwo, 100, 200);
    TopLeftTwoTwo = gtk_image_new_from_file("./assets/table/2by2square.png");
    gtk_widget_set_size_request((GtkWidget *)TopLeftTwoTwo, 100, 100);
    TopRightTwoTwo = gtk_image_new_from_file("./assets/table/2by2square.png");
    gtk_widget_set_size_request((GtkWidget *)TopRightTwoTwo, 100, 100);
    TopMiddle1 = gtk_image_new_from_file("./assets/table/2by2square.png");
    gtk_widget_set_size_request((GtkWidget *)TopMiddle1, 100, 100);
    TopMiddle2 = gtk_image_new_from_file("./assets/table/1by2square.png");
    gtk_widget_set_size_request((GtkWidget *)TopMiddle2, 50, 100);
    BotLeftTwoTwo = gtk_image_new_from_file("./assets/table/2by2square.png");
    gtk_widget_set_size_request((GtkWidget *)BotLeftTwoTwo, 100, 100);
    BotRightTwoTwo = gtk_image_new_from_file("./assets/table/2by2square.png");
    gtk_widget_set_size_request((GtkWidget *)BotRightTwoTwo, 100, 100);
    BotMiddle1 = gtk_image_new_from_file("./assets/table/2by2square.png");
    gtk_widget_set_size_request((GtkWidget *)BotMiddle1, 100, 100);
    BotMiddle2 = gtk_image_new_from_file("./assets/table/1by2square.png");
    gtk_widget_set_size_request((GtkWidget *)BotMiddle2, 50, 100);
    gtk_table_attach(GTK_TABLE(gametable), TopRightFourTwo,  10, 12, 1, 5, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), TopLeftFourTwo,  1, 3, 1, 5, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), BotRightFourTwo,  10, 12, 5, 9, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), BotLeftFourTwo,  1, 3, 5, 9, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), TopLeftTwoTwo,  3, 5, 1, 3, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), TopRightTwoTwo,  8, 10, 1, 3, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), TopMiddle1,  5, 7, 1, 3, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), TopMiddle2,  7, 8, 1, 3, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), BotLeftTwoTwo,  3, 5, 7, 9, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), BotRightTwoTwo,  8, 10, 7, 9, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), BotMiddle1,  5, 7, 7, 9, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), BotMiddle2,  7, 8, 7, 9, GTK_FILL, GTK_FILL, 0, 0);

    //middle for cards
    MiniTop = gtk_image_new_from_file("./assets/table/5by1square.png");
    MiniBot = gtk_image_new_from_file("./assets/table/5by1square.png");
    MiniLeft = gtk_image_new_from_file("./assets/table/1by4square.png");
    MiniRight =  gtk_image_new_from_file("./assets/table/1by4square.png");
    Middle1 = gtk_image_new_from_file("./assets/table/2by2square.png");
    Middle2 = gtk_image_new_from_file("./assets/table/2by2square.png");
    Middle3 = gtk_image_new_from_file("./assets/table/1by2square.png");
    gtk_widget_set_size_request((GtkWidget *)MiniTop, 250, 50);
    gtk_widget_set_size_request((GtkWidget *)MiniBot, 250, 50);
    gtk_widget_set_size_request((GtkWidget *)MiniLeft, 50, 200);
    gtk_widget_set_size_request((GtkWidget *)MiniRight, 50, 200);
    gtk_widget_set_size_request((GtkWidget *)Middle1, 100, 100);
    gtk_widget_set_size_request((GtkWidget *)Middle2, 100, 100);
    gtk_widget_set_size_request((GtkWidget *)Middle3, 50, 100);
    gtk_table_attach(GTK_TABLE(gametable), MiniTop,  4, 9, 3, 4, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), MiniBot,  4, 9, 6, 7, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), MiniLeft,  3, 4, 3, 7, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), MiniRight,  9, 10, 3, 7, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), Middle1,  4, 6, 4, 6, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), Middle2,  6, 8, 4, 6, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(gametable), Middle3,  8, 9, 4, 6, GTK_FILL, GTK_FILL, 0, 0);
    gtk_table_attach(GTK_TABLE(table), gametable, 1, 14, 3, 20, GTK_FILL, GTK_FILL, 0,0);
    gtk_container_add(GTK_CONTAINER(window), table);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), G_OBJECT(window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}

GtkWidget* create_image_widget(const char *filepath, int width, int height) {
    GtkWidget *image = gtk_image_new_from_file(filepath);
    if (!gtk_image_get_pixbuf(GTK_IMAGE(image))) {
        g_warning("Failed to load image: %s", filepath);
        image = gtk_image_new_from_icon_name("image-missing", GTK_ICON_SIZE_DIALOG);
    } else {
        g_print("Loaded image: %s with size %d x %d\n", filepath, width, height);
        gtk_widget_set_size_request(image, width, height);
    }
    return image;
}

//when start button clicked
void startbtnclicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(startbtn);
    gtk_image_set_from_file(GTK_IMAGE(turncolor), GreenBox);
}

