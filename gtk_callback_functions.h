void menu_event(GtkWidget *widget){
    const char *label = gtk_menu_item_get_label(GTK_MENU_ITEM(widget));
  if(strcmp(label,"Rules")==0 || strcmp(label,"About")==0 ){
        if(strcmp(label,"About")==0){
            open_dialog("Project: Sudoku Generator and Solver Using C with GTK Library\nName: Anish Dangol\nRoll number: 02\nSecond Semester");
        }
        if(strcmp(label,"Rules")==0){
           open_dialog("Rule 1: Each row must contain the numbers from 1 to 9, without repetitions\nRule 2: Each column must contain the numbers from 1 to 9, without repetitions\nRule 3: The digits can only occur once per block\nEach puzzle has a unique solution\n\nPress the play button and select the difficulty level to get started\nGoodluck and Have Fun!");

        }
    }
}
void reset(GtkWidget *widget,gpointer){
  //function to reset the puzzle
  printf("Reset not yet implemented\n");
}
void solve_gtk_sudoku(GtkWidget *widget,gpointer data){
    //function to solve the puzzle
     printf("Solve not yet implemented\n");
}
void check_gtk_sudoku(GtkWidget *widget,gpointer data){
     printf("Check not yet implemented\n");
    //function to check the steps
}
void hint_gtk_sudoku(GtkWidget *widget,gpointer data){
   //LOAD PUZZLE
    printf("Hint not yet implemented\n");
}
