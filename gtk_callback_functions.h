static void menu_event(GtkWidget *widget,gpointer data){
    //Label Pointer//
    const char *label = gtk_menu_item_get_label(GTK_MENU_ITEM(widget));
    if(strcmp(label,"Easy")==0 || strcmp(label,"Medium")==0 || strcmp(label,"Hard")==0){
        if(strcmp(label,"Easy")==0) play(EASY);
        if(strcmp(label,"Medium")==0) play(MEDIUM);
        if(strcmp(label,"Hard")==0) play(HARD);
        load_gpuzzle(matrix.puzzle); // learn
        copy_box1_to_box2(matrix.puzzle,current.puzzle); // learn
    }
    else if(strcmp(label,"Rules")==0 || strcmp(label,"About")==0 ){
        if(strcmp(label,"About")==0){
            open_dialog("Mini Project of C using GTK library \nBy Anish Dangol\nSecond Semester\nRoll No: 02");
        }
        if(strcmp(label,"Rules")==0){
           open_dialog("Rule 1: Each row must contain the numbers from 1 to 9 without repetitions\nRule 2: Each column must contain the numbers from 1 to 9 without repetitions\nRule 3: The digits can only occur once per block\n\nNotes:\nEach puzzle has a unique solution.\nPress the play button and select the difficulty level to get started.\n\nGoodluck, Have Fun!");
        }
    }
    else if(strcmp(label,"Open")==0){
        GtkWidget *dialog;
        dialog = gtk_file_chooser_dialog_new("Choose a File",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,"_Cancel",GTK_RESPONSE_CANCEL,"_Ok",GTK_RESPONSE_OK,NULL);
        gtk_widget_show_all(dialog);
        gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
        if(resp==GTK_RESPONSE_OK){
            open_progress(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
            load_gpuzzle(current.puzzle);
        }
        gtk_widget_destroy(dialog);
    }
    else if(strcmp(label,"Save")==0){
        load_puzzle(current.puzzle);
        GtkWidget *dialog;
        dialog = gtk_file_chooser_dialog_new("Save",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_SAVE,"_Cancel",GTK_RESPONSE_CANCEL,"_Ok",GTK_RESPONSE_OK,NULL);
        int save_flag = 0;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(strcmp(gtk_entry_get_text(GTK_ENTRY(gmatrix[i][j]))," ")!=0){
                    save_flag = 1;
                    break;
                }
            }
            if(save_flag) break;
        }
        if(save_flag){
            gtk_widget_show_all(dialog);
            gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
            if(resp == GTK_RESPONSE_OK){
                save_progress(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
                gtk_widget_destroy(dialog);
            }
            else{
                gtk_widget_destroy(dialog);
            }
        }
        else open_dialog("Empty file cannot be saved");
    }
}

void solve_gtk_sudoku(GtkWidget *widget,gpointer data){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            char data[2];
            strcpy(data,"0");
            sprintf(data,"%d",matrix.solution[i][j]);
            gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),data);
        }
    }
}
void reset(GtkWidget *widget,gpointer){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(matrix.puzzle[i][j]!=0){
                char data[2];
                strcpy(data,"0");
                sprintf(data,"%d",matrix.puzzle[i][j]);
                gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j]),data);
            }
            else gtk_entry_set_text(GTK_ENTRY(gmatrix[i][j])," ");
        }
    }
}

void check_gtk_sudoku(GtkWidget *widget,gpointer data){
    load_puzzle(current.puzzle);
    int finished_flag = 1;
    int error_check_flag = 0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(current.puzzle[i][j]==0) finished_flag=0;
            else if(current.puzzle[i][j]!=matrix.solution[i][j]) {
                error_check_flag=1;
                break;
            }
        }
        if(error_check_flag) break;
    }
    if(finished_flag){
        open_dialog("Congratulations!, You have solved the sudoku");
        return;
    }
    if(error_check_flag) open_dialog("Your sudoku is incorrect");
    else   open_dialog("Well done! The progress you have made so far is correct.");
}
void hint_gtk_sudoku(GtkWidget *widget,gpointer data){
    load_puzzle(current.puzzle);
    get_a_hint(&current);
}
