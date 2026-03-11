#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notes.h"
#include "ui.h"
#include "util.h"


int main () {

   NoteList list;
   int choice;

   init_note_list(&list);

   do {
        print_menu();
        choice = get_menu_choice();

        switch(choice) {
            case 1:
                handle_create_note(&list);
                break;
            case 2:
                handle_list_notes(&list);
                break;
            case 3:
                printf("View note:\n");
                break;
            case 4:
                printf("Search notes:\n");
                break;
            case 5:
                handle_remove_note(&list);
                break;
            case 0:
                printf("Quiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
   } while (choice != 0);

   free_note_list(&list);
   return 0;
}