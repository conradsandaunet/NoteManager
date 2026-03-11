#include <stdio.h>
#include <string.h>
#include "ui.h"

void print_menu(void) {

    printf("==== NoteManager ====\n");
    printf("1. Create note\n");
    printf("2. List notes\n");
    printf("3. View note\n");
    printf("4. Search notes");
    printf("5. Remove note\n");
    printf("0. Quit\n");
}

int get_menu_choice(void) {

    int choice;

    printf("Choose: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n');

        return -1;
    }

    while (getchar() != '\n');

    return choice;
}

void handle_list_notes(const NoteList *list) {

    size_t i;

    if (list == NULL || list->count == 0) {
        printf("No notes found.\n");
        return;
    }

    for (i = 0; i < list->count; i++) {
        printf("[%zu] %s (%s)\n", i, list->items[i].title, list->items[i].created_at);
    }
}

void handle_search_notes(const NoteList *list) {

    char query[128];
    int matches;

    printf("Search: \n");
    if (fgets(query, sizeof(query), stdin) == NULL) {
        return;
    }

    query[strcspn(query, "\n")] = '\0';

    matches = search_notes(list, query);

    if (matches == 0)
        printf("No matches found.\n");
    else
        printf("%d match(es) found.\n", matches);
}

void handle_remove_note(NoteList *list) {

    size_t index;

    if (list == NULL || list->count == 0) {
        printf("No notes to remove.\n");
        return;
    }

    handle_list_notes(&list);

    printf("Enter index to remove: ");
    if(scanf("%zu", &index) != 1) {
        while (getchar() != '\n');

        printf("Invalid input.\n");
        return;
    }

    while (getchar() != '\n');

    if (index >= list->count) {
        printf("Invalid index.\n");
        return;
    }

    remove_note(list, index);
    printf("Note removed.\n");
}