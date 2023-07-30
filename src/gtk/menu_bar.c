#include "gftp-gtk.h"

/* gFTP | Local | Remote | Bookmarks | Transfer | Log | Tools | Help */

/* FIXME: We will have to deal with translation at some point*/

/* Example */  
/*
  GtkWidget *menubar;
  GtkWidget *fileMenu;
  GtkWidget *fileMi;
  GtkWidget *quitMi;

  menubar = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();

  fileMi = gtk_menu_item_new_with_label("File");
  quitMi = gtk_menu_item_new_with_label("Quit");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
*/

GtkWidget *
CreateMenuBar (GtkWidget * parent)
{
  GtkWidget *menubar;
  GtkWidget *menu_gFTP, *menu_Local, *menu_Remote, *menu_Bookmarks,
            *menu_Transfer, *menu_Log, *menu_Tools, *menu_Help;

  menubar = gtk_menu_bar_new();

  menu_gFTP  = gtk_menu_item_new_with_label("gFTP");
  menu_Local = gtk_menu_item_new_with_label("Local");
  menu_Remote = gtk_menu_item_new_with_label("Remote");
  menu_Bookmarks = gtk_menu_item_new_with_label("Bookmarks");
  menu_Transfer = gtk_menu_item_new_with_label("Transfer");
  menu_Log = gtk_menu_item_new_with_label("Log");
  menu_Tools = gtk_menu_item_new_with_label("Tools");
  menu_Help = gtk_menu_item_new_with_label("Help");

  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_gFTP);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Local);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Remote);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Bookmarks);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Transfer);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Log);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Tools);
  gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menu_Help);

  return menubar; 
}
