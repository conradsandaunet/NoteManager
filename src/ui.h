#ifndef UI_H
#define UI_H

#include "notes.h"

void print_menu(void);
int get_menu_choice(void);

void handle_create_note(NoteList *list);
void handle_list_notes(const NoteList *list);
void handle_view_note(const NoteList *list);
void handle_search_notes(const NoteList *list);
void handle_remove_note(NoteList *list);

#endif


