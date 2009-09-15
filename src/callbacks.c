#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "callbacks.h"
#include "interface.h"

#include "dictionary.h"


void
on_keyword_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
	/* get keyword -> search */
	gchar *keyword = (gchar *) gtk_editable_get_chars (editable, 0, -1);
	gchar *meaning = NULL;
	if (keyword != NULL)
	{
		/* to lowercase */
		int len = strlen (keyword);
		int i;
		for (i = 0; i < len; i++)
		{
			keyword [i] = tolower (keyword [i]); 
		}

		/* check if it is ascii */
		if (isalpha (keyword[0]))
		{
			meaning = (gchar *) dictionary_search (keyword);
		}
	}

	/* clear the text buffer */
	GtkWidget *meaning_textview = glade_xml_get_widget (ui, "meaning_textview");
	GtkTextBuffer *text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (meaning_textview));
	gtk_text_buffer_set_text (text_buffer, "", -1);
	gtk_text_view_set_buffer (GTK_TEXT_VIEW (meaning_textview), text_buffer);

	/* if the meaning exists, put it in the text buffer */
	if (meaning != NULL) 
	{
		/* convert to UTF-8 */
		gsize len;
		gchar *meaning_utf8 = g_convert (meaning, strlen (meaning), "UTF-8", "TIS-620", NULL, &len, NULL);
		gchar *first_match_word = (gchar *) dictionary_get_first_matched_word ();

		/* put to the text buffer */
		GtkTextIter iter;
		gtk_text_buffer_get_iter_at_offset (text_buffer, &iter, 0);
		gtk_text_buffer_insert_with_tags_by_name (text_buffer, &iter, first_match_word, -1, "keyword", NULL);
		gtk_text_buffer_insert (text_buffer, &iter, "\n\t", -1);
		gtk_text_buffer_insert (text_buffer, &iter, meaning_utf8, len);
		gtk_text_view_set_buffer (GTK_TEXT_VIEW (meaning_textview), text_buffer);

		g_free (meaning_utf8);
	}
	g_free (meaning);

	/* update word list */	
	GtkWidget *wordlist_treeview = glade_xml_get_widget (ui, "wordlist_treeview");
	GtkListStore *list_store = GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (wordlist_treeview)));
	
	/* detach the list */
	g_object_ref (list_store);
	gtk_tree_view_set_model (GTK_TREE_VIEW (wordlist_treeview), NULL);

	/* update the list */
	int items = 0;
	gtk_list_store_clear (list_store);
	GtkTreeIter iter;
	gchar *word = (gchar *) dictionary_get_next_word ();
	while (word != NULL) 
	{
		gtk_list_store_append (list_store, &iter);
		gtk_list_store_set (list_store, &iter, 0, word, -1);
		word = (gchar *) dictionary_get_next_word ();
		items++;
	}
	
	/* re-attach the list */
	gtk_tree_view_set_model (GTK_TREE_VIEW (wordlist_treeview), GTK_TREE_MODEL (list_store));
	g_object_unref (list_store);

	/* update status bar */
	GtkWidget *statusbar = glade_xml_get_widget (ui, "statusbar");
	guint context_id = gtk_statusbar_get_context_id (GTK_STATUSBAR (statusbar), "GDictThai Status");
	if (keyword != NULL && strlen (keyword) > 0) {
		gchar match_items[24];
		g_sprintf (match_items, "%d words matched", items);
		gtk_statusbar_pop (GTK_STATUSBAR (statusbar), context_id);
		gtk_statusbar_push (GTK_STATUSBAR (statusbar), context_id, match_items);
	} else {
		gtk_statusbar_pop (GTK_STATUSBAR (statusbar), context_id);
		gtk_statusbar_push (GTK_STATUSBAR (statusbar), context_id, "Ready");
	}
}


void
on_treeview_cursor_changed             (GtkTreeView     *treeview,
                                        gpointer         user_data)
{
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;

	selection = gtk_tree_view_get_selection (treeview);
	if (gtk_tree_selection_get_selected (selection, &model, &iter))
	{
		gchar *keyword;
		gchar *meaning;
		gtk_tree_model_get (model, &iter, 0, &keyword, -1);

		GtkWidget *keyword_entry = glade_xml_get_widget (ui, "keyword_entry");
		gtk_entry_set_text (GTK_ENTRY (keyword_entry), keyword);
	}
}


void
on_quit_menuitem_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	dictionary_close ();
	g_object_unref (G_OBJECT (ui));
  gtk_main_quit ();
}


void
on_copy_menuitem_activate              (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *meaning_textview = glade_xml_get_widget (ui, "meaning_textview");
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (meaning_textview));

	GtkClipboard *clipboard = gtk_clipboard_get (GDK_NONE);
	gtk_text_buffer_copy_clipboard (buffer, clipboard);
}


void
on_paste_menuitem_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkClipboard *clipboard = gtk_clipboard_get (GDK_NONE);
	GtkWidget *editable = glade_xml_get_widget (ui, "keyword_entry");
	gtk_editable_delete_text (GTK_EDITABLE (editable), 0, -1);
	gtk_editable_paste_clipboard (GTK_EDITABLE (editable));
}

void
on_about_menuitem_activate             (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
	GtkWidget *about_dialog = glade_xml_get_widget (ui, "about_dialog");
	gtk_dialog_run (GTK_DIALOG (about_dialog));
	gtk_widget_hide (about_dialog);
}
