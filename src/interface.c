#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#include "callbacks.h"
#include "interface.h"

GtkWidget*
create_main_window (void)
{

	ui = glade_xml_new (PACKAGE_DATA_DIR "/" PACKAGE "/gdictthai.glade", NULL, NULL);

	if (!ui) exit (EXIT_FAILURE);

	GtkWidget *main_window = glade_xml_get_widget (ui, "main_window");
	GtkWidget *quit_menuitem = glade_xml_get_widget (ui, "quit_menuitem");
	GtkWidget *copy_menuitem = glade_xml_get_widget (ui, "copy_menuitem");
	GtkWidget *paste_menuitem = glade_xml_get_widget (ui, "paste_menuitem");
	GtkWidget *about_menuitem = glade_xml_get_widget (ui, "about_menuitem");
	GtkWidget *quit_toolbutton = glade_xml_get_widget (ui, "quit_toolbutton");
	GtkWidget *copy_toolbutton = glade_xml_get_widget (ui, "copy_toolbutton");
	GtkWidget *paste_toolbutton = glade_xml_get_widget (ui, "paste_toolbutton");
	GtkWidget *about_toolbutton = glade_xml_get_widget (ui, "about_toolbutton");
	GtkWidget *keyword_entry = glade_xml_get_widget (ui, "keyword_entry");
	GtkWidget *wordlist_treeview = glade_xml_get_widget (ui, "wordlist_treeview");

	/* connecting signals */
  g_signal_connect ((gpointer) main_window, "destroy",
                    G_CALLBACK (on_quit_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) quit_menuitem, "activate",
                    G_CALLBACK (on_quit_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) copy_menuitem, "activate",
                    G_CALLBACK (on_copy_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) paste_menuitem, "activate",
                    G_CALLBACK (on_paste_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) about_menuitem, "activate",
                    G_CALLBACK (on_about_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) copy_toolbutton, "clicked",
                    G_CALLBACK (on_copy_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) paste_toolbutton, "clicked",
                    G_CALLBACK (on_paste_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) about_toolbutton, "clicked",
                    G_CALLBACK (on_about_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) quit_toolbutton, "clicked",
                    G_CALLBACK (on_quit_menuitem_activate),
                    NULL);
  g_signal_connect ((gpointer) keyword_entry, "changed",
                    G_CALLBACK (on_keyword_entry_changed),
                    NULL);
  g_signal_connect ((gpointer) wordlist_treeview, "cursor_changed",
                    G_CALLBACK (on_treeview_cursor_changed),
                    NULL);

  return main_window;
}
