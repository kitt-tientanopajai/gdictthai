#include <gtk/gtk.h>

void
on_keyword_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_treeview_cursor_changed             (GtkTreeView     *treeview,
                                        gpointer         user_data);

void
on_meaning_textview_copy_clipboard      (GtkTextView     *textview,
                                        gpointer         user_data);

void
on_quit_menuitem_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_copy_menuitem_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_paste_menuitem_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

void
on_about_menuitem_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data);

