#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "ui.h"
#include "util.h"

void print_menu(void) {

    printf("==== NoteManager ====\n");
    printf("1. Create note\n");
    printf("2. List notes\n");
    printf("3. View note\n");
    printf("4. Search notes\n");
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

    printf("Search: ");
    read_line(query, sizeof(query));
    
    if (query[0] == '\0') {
        printf("Search query cannot be empty.\n");
        return;
    }

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

    handle_list_notes(list);

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

void handle_create_note(NoteList *list) {

    Note note;

    if (list == NULL) {
        return;
    }

    printf("Title: ");
    read_line(note.title, sizeof(note.title));

    printf("Tags: ");
    read_line(note.tags, sizeof(note.tags));

    generate_timestamp(note.created_at, sizeof(note.created_at));

    printf("Content (write [END] on a new line to finish): \n");
    note.content = read_multiline_input();

    note.filename[0] = '\0';

    if (!add_note(list, &note)) {
        printf("Failed to add note.\n");
        free(note.content);
        return;
    }

    free(note.content);

    printf("Note added successfully.\n");
}

void handle_view_note(const NoteList *list) {

    char buffer[32];
    size_t index;

    if (list == NULL || list->count == 0) {
        printf("No notes available.\n");
        return;
    }

    handle_list_notes(list);

    printf("Enter note index to view: ");
    read_line(buffer, sizeof(buffer));

    if (buffer[0] == '\0') {
        printf("Input cannot be empty.\n");
        return;
    }

    index = (size_t)strtoul(buffer, NULL, 10);

    if (index >= list->count) {
        printf("Invalid note index.\n");
        return;
    }

    view_note(list, index);
}