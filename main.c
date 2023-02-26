//everything starting with a "GTK" is a data type in the GTK Library


#include<gtk/gtk.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


//Global Variables
#define N 9
#define M 3

//user-defined header file
#include "gtk_callback_functions.h"


//structure named sudoku// points to the memory address of the variable's pointer
struct sudoku{
    int **puzzle;
    int **solution;
};

//display // not fully implemented
GtkWidget *gmatrix[N][N];
GtkWidget *window;



// open dialog function
//passes "const char* str" as string argument
// labels and dialogs

void open_dialog(const char* str){
    GtkWidget *label, *dialog, *content_area;
    // flags in buttons to destroy the label area
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons("Sudoku",GTK_WINDOW(window),flags,"Ok",GTK_RESPONSE_NONE,NULL);

    //content is extracted from label in callback header file
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    //string for new label
    label = gtk_label_new(str);
    g_signal_connect_swapped(dialog,"response",G_CALLBACK(gtk_widget_destroy),dialog);
    //display content of the label
    gtk_container_add(GTK_CONTAINER(content_area),label);
    //display full dialog
    gtk_widget_show_all(dialog);
}



//how many integers passed, what passed
int main(int argc,char *argv[]){


//pointer to the array variables
    char *File[4] = {"New","Save","Open","Quit"};
    char *New_File[3] = {"Easy","Medium","Hard"};
    char *Help[2] = {"Rules","About"};

    //main display
    gtk_init(&argc,&argv);
    GtkWidget *vbox, *hbox, *file_menu, *help_menu, *new_menu, *menu_item, *menu_bar, *button;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window),"Sudoku");

    //initial menu bar display
    menu_bar = gtk_menu_bar_new();
    //adding label to it
    menu_item = gtk_menu_item_new_with_label("FILE");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);
    file_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),file_menu);

    menu_item = gtk_menu_item_new_with_label("HELP");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),menu_item);
    help_menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),help_menu);




//Menu Section
    for(int i=0;i<4;i++){
            // menu
        menu_item = gtk_menu_item_new_with_label(File[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(file_menu),menu_item);
        //sub menu for new
        if(i==0){
            new_menu = gtk_menu_new();
            gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item),new_menu);
        }

    }
    for(int i=0;i<3;i++){
        menu_item = gtk_menu_item_new_with_label(New_File[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(new_menu),menu_item);

    }
    for(int i=0;i<2;i++){
        menu_item = gtk_menu_item_new_with_label(Help[i]);
        gtk_menu_shell_append(GTK_MENU_SHELL(help_menu),menu_item);
        g_signal_connect(menu_item,"activate",G_CALLBACK(menu_event),NULL);
    }



    //model to put arguments
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);

    for(int i=0;i<N;i++){
        hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
        for(int j=0;j<N;j++){
            gmatrix[i][j] = gtk_entry_new();
            //char length of the box
            gtk_entry_set_max_length(GTK_ENTRY(gmatrix[i][j]),1);
            //width length of box
            gtk_entry_set_width_chars(GTK_ENTRY(gmatrix[i][j]),2);
            // h margin
            gtk_box_pack_start(GTK_BOX(hbox),gmatrix[i][j],0,0,0);
        }
        //v margin
        gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,1);
    }
    //initial value of all box inputs
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),"  ");
        }
    }



    // buttons // callback not yet implemented
    button = gtk_button_new_with_label("Solve");
    g_signal_connect(button,"clicked",G_CALLBACK(solve_gtk_sudoku),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,5);

    button = gtk_button_new_with_label("Reset");
    g_signal_connect(button,"clicked",G_CALLBACK(reset),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,5);

    button = gtk_button_new_with_label("Hint");
    g_signal_connect(button,"clicked",G_CALLBACK(hint_gtk_sudoku),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,5);

    button = gtk_button_new_with_label("Check");
    g_signal_connect(button,"clicked",G_CALLBACK(check_gtk_sudoku),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),button,0,0,5);



    //display of the whole graphics
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show_all(window);
    gtk_main();

return 0;
}
