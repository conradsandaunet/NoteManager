#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "notes.h"
#include "util.h"

void init_note_list(NoteList *list) {

    if (list == NULL) {
        return;
    }

    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
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

int search_notes(const NoteList *list, const char *query)
{
    size_t i;
    int matches = 0;
    char *query_lower;

    if (list == NULL || query == NULL)
        return 0;

    if (*query == '\0')
        return 0;

    query_lower = str_to_lower(query);
    if (query_lower == NULL)
        return 0;

    for (i = 0; i < list->count; i++) {
        const Note *note = &list->items[i];
        char *title_lower = str_to_lower(note->title);
        char *tags_lower = str_to_lower(note->tags);
        char *content_lower = str_to_lower(note->content);

        if ((title_lower != NULL && strstr(title_lower, query_lower) != NULL) ||
            (tags_lower != NULL && strstr(tags_lower, query_lower) != NULL) ||
            (content_lower != NULL && strstr(content_lower, query_lower) != NULL)) {
            printf("[%zu] %s\n", i, note->title);
            matches++;
        }

        free(title_lower);
        free(tags_lower);
        free(content_lower);
    }

    free(query_lower);
    return matches;
}

void view_note(NoteList *list, size_t index) {

    const Note *note;

    if (list == NULL) {
        printf("Note list is NULL.\n");
        return;
    }

    if (index >= list->count) {
        printf("Invalid note index.\n");
        return;
    }

    note = &list->items[index];

    printf("\n==== Note %zu ====\n", index);
    printf("Title: %s\n", note->title);
    printf("Tags: %s\n", note->tags);
    printf("Created: %s\n", note->created_at);
    printf("Filename: %s\n", note->filename);

    printf("\nContent:\n");
    if (note->content != NULL && note->content[0] != '\0')
        printf("%s", note->content);
    else
        printf("(empty)\n");

    if (note->content != NULL) {
        size_t len = strlen(note->content);
        if (len > 0 && note->content[len -1] != '\n');
            printf("\n");
    }

    printf("\n");
}