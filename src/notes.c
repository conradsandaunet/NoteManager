#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notes.h"

int init_note_list(NoteList *list) {

    if (list == NULL) {
        return 0;
    }

    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
    
    return 1;

}

void free_note_list(NoteList *list) {

    if (list == NULL) {
        return;
    }
    
    free(list->items);
    list->items = NULL;
    list->capacity = 0;
    list->count = 0;
}

int add_note(NoteList *list, const Note *note) {

    Note *new_notes;
    size_t new_capacity;

    if (list == NULL || note == NULL) {
        return 0;
    }

    if (list->count >= list->capacity) {
        if(list->capacity == 0) {
            new_capacity = 4;
        } else {
            new_capacity = list->capacity * 2;
        }

        new_notes = realloc(list->items, new_capacity * sizeof(Note)); 

        if (new_notes == NULL) {
            return 0;
        }

        list->items = new_notes;
        list->capacity = new_capacity;
    }

    list->items[list->count] = *note;
    if (note->content) {
        list->items[list->count].content = _strdup(note->content);
    }


    list->count++;

    return 1;
}

void remove_note(NoteList *list, size_t index) {

    size_t i;


    if (list == NULL) {
        return;
    }

    if (index >= list->count)
        return;

    free(list->items[index].content);

    for (i = index; i < list->count - 1; i++) {
        list->items[i] = list->items[i + 1];
    }

    list->count--;
}

int search_notes(const NoteList *list, const char *query) {

        
}