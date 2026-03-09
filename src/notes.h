#ifndef NOTES_H
#define NOTES_H

#include <stddef.h>

#define MAX_TITLE 128
#define MAX_TAGS 128
#define MAX_FILENAME 128

typedef struct {

    char title[MAX_TITLE];
    char tags[MAX_TAGS];
    char created_at[32];
    char filename[MAX_FILENAME];
    char *content;

} Note;

typedef struct {

    Note *items;
    size_t count;
    size_t capacity;

} NoteList;

void init_note_list(NoteList *list);
void free_note_list(NoteList *list);
int add_note(NoteList *list, const Note *note);
void remove_note(NoteList *list, size_t index);
int search_notes(const NoteList * list, const char *query);

#endif
