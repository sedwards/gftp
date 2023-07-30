/***********************************************************************************/
/*  gftp-gtk.h - include file for the gftp gtk+ port                               */
/*  Copyright (C) 1998-2003 Brian Masney <masneyb@gftp.org>                        */
/*                                                                                 */
/*  Permission is hereby granted, free of charge, to any person obtaining a copy   */
/*  of this software and associated documentation files (the "Software"), to deal  */
/*  in the Software without restriction, including without limitation the rights   */
/*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      */
/*  copies of the Software, and to permit persons to whom the Software is          */
/*  furnished to do so, subject to the following conditions:                       */
/*                                                                                 */
/*  The above copyright notice and this permission notice shall be included in all */
/*  copies or substantial portions of the Software.                                */
/*                                                                                 */
/*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     */
/*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       */
/*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    */
/*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         */
/*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  */
/*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  */
/*  SOFTWARE.                                                                      */
/***********************************************************************************/

/* $Id$ */

#ifndef __GFTP_GTK_H
#define __GFTP_GTK_H

#include "../../lib/gftp.h"
#include "../uicommon/gftpui.h"
#include "../gtkcompat.h"
#include <pthread.h>

// comment out #if.. #endif 
#if GTK_MAJOR_VERSION > 2
#define TRANSFER_GTK_TREEVIEW 1
#endif


#define GFTP_MENU_ITEM_ASCII	1
#define GFTP_MENU_ITEM_BINARY	2
#define GFTP_MENU_ITEM_WIN1	3
#define GFTP_MENU_ITEM_WIN2	4

#define GFTP_IS_SAME_HOST_START_TRANS(wdata,trequest) \
  ((wdata) != NULL && (wdata)->request != NULL && \
  (wdata)->request->datafd > 0 && !(wdata)->request->always_connected && \
  !(wdata)->request->stopable && \
  compare_request (trequest, (wdata)->request, 0))

#define GFTP_IS_SAME_HOST_STOP_TRANS(wdata,trequest) \
  ((wdata) != NULL && (wdata)->request != NULL && \
  (wdata)->request->datafd < 0 && !(wdata)->request->always_connected && \
  (wdata)->request->cached && !(wdata)->request->stopable && \
  trequest->datafd > 0 && !trequest->always_connected && \
  compare_request (trequest, (wdata)->request, 0))

/* These are used for the TextEntryDialog function. I have these types to make
   it easier for creating dialogs with GTK+ 2.0 */

typedef enum gftp_dialog_button_tag
{
  gftp_dialog_button_create,
  gftp_dialog_button_change,
  gftp_dialog_button_connect,
  gftp_dialog_button_rename,
  gftp_dialog_button_ok
} gftp_dialog_button;

typedef struct gftp_window_data_tag
{
  GtkWidget *dir_combo, /* Entry widget/history for the user to enter  a directory */
            *dirinfo_label,  /* protocol and dir info */
            *listbox; 		/* Our listbox showing the files */
  unsigned int sorted : 1,	/* Is the output sorted? */
               show_selected : 1, /* Show only selected files */
               *histlen;	/* Pointer to length of history */
  char *filespec;		/* Filespec for the listbox */
  gftp_request * request;	/* The host that we are connected to */
  GList * files,		/* Files in the listbox */
        ** history;		/* History of the directories */
  GtkBuilder *ifactory; 	/* This is for the menus that will
                                   come up when you right click */
  pthread_t tid;		/* Thread for the stop button */
  char *prefix_col_str;
} gftp_window_data;


typedef struct _gftpui_gtk_thread_data
{
  void * (*func) (void *);
  gftpui_callback_data * cdata;
} gftpui_gtk_thread_data;


#if !defined(TRANSFER_GTK_TREEVIEW)
typedef struct gftp_graphic_tag
{
  char * filename;
  GdkPixmap * pixmap;
  GdkBitmap * bitmap;
} gftp_graphic;
#endif

typedef struct gftp_dialog_data_tag
{
  GtkWidget * dialog,
            * checkbox,
            * edit;
  /* the dialog is destroyed but these vars
   * are available to yesfunc() and nofunc() */
  char * entry_text;
  int checkbox_is_ticked;

  void (*yesfunc) ();
  gpointer yespointer;

  void (*nofunc) ();
  gpointer nopointer;
} gftp_dialog_data;


typedef struct gftp_viewedit_data_tag 
{
   char *filename,              /* File we are viewing/editing currently */
        *remote_filename;       /* The filename on the remote computer */
   struct stat st;              /* Vital file statistics */
   pid_t pid;                   /* Our process id */
   char **argv;                 /* Our arguments we passed to execvp. We will 
                                   free it when the process terminates. This 
                                   is the safest place to free this */
   unsigned int view : 1,       /* View or edit this file */
                rm : 1,         /* Delete this file after we're done with it */
                dontupload : 1; /* Don't upload this file after we're done
				   editing it */
   gftp_window_data * fromwdata, /* The window we are viewing this file in */
                    * towdata;
   gftp_request * torequest;
} gftp_viewedit_data;


typedef struct gftp_textcomboedt_widget_data_tag
{
  GtkWidget * combo,
            * text;
  gftp_config_vars * cv;
  char * custom_edit_value;
} gftp_textcomboedt_widget_data;


typedef struct gftp_options_dialog_data_tag
{
  GtkWidget * dialog,
            * notebook,
            * box,
            * table;
  unsigned int tbl_col_num,
               tbl_row_num;
  gftp_option_type_enum last_option;
  gftp_bookmarks_var * bm;
} gftp_options_dialog_data;

extern GtkWindow *main_window;
extern gftp_window_data window1, window2, * other_wdata, * current_wdata;
extern GtkWidget * stop_btn, * hostedit, * useredit, * passedit,
                 * portedit, * logwdw, * dlwdw, * toolbar_combo_protocol,
                 * gftpui_command_widget, * download_left_arrow,
                 * upload_right_arrow, * openurl_btn;
extern GtkAdjustment * logwdw_vadj;
extern GtkTextMark * logwdw_textmark;
extern int local_start, remote_start, trans_start;
extern GHashTable * graphic_hash_table;
extern GHashTable * pixbuf_hash_table;

extern GtkActionGroup * menus;
extern GtkBuilder * factory;

extern pthread_mutex_t log_mutex;
extern pthread_t main_thread_id;
extern GList * viewedit_processes;

extern intptr_t gftp_gtk_colored_msgs;


/* bookmarks.c */
void run_bookmark 				( gpointer data );

void add_bookmark 				( gpointer data );

void edit_bookmarks 				( gpointer data );

void build_bookmarks_menu			( void );

/* chmod_dialog.c */ 
void chmod_dialog 				( gpointer data );

/* dnd.c */
void openurl_get_drag_data 			( GtkWidget * widget, 
						  GdkDragContext * context, 
						  gint x,
						  gint y, 
						  GtkSelectionData * selection_data, 
						  guint info, 
						  guint32 clk_time, 
						  gpointer data );

void listbox_drag 				( GtkWidget * widget, 
						  GdkDragContext * context,
						  GtkSelectionData * selection_data, 
						  guint info, 
						  guint32 clk_time, 
						  gpointer data );

void listbox_get_drag_data 			( GtkWidget * widget, 
						  GdkDragContext * context, 
						  gint x,
						  gint y, 
						  GtkSelectionData * selection_data, 
						  guint info, 
						  guint32 clk_time, 
						  gpointer data );

/* gftp-gtk.c */
void gftp_gtk_init_request 			( gftp_window_data * wdata );

void toolbar_hostedit (void);

void stop_button				( GtkWidget * widget,
						  gpointer data );

void gftpui_show_or_hide_command 		( void );

void on_activate_colored_msgs_cb (GtkToggleAction * checkb);

void _gftp_menu_exit (GtkWidget * widget, gpointer data);

void gftp_gtk_refresh (gftp_window_data * wdata);

void navi_up_directory (gftp_window_data * wdata);

void openurl_dialog (gpointer data);

/* listbox.c */
GtkWidget * create_listbox 			(gftp_window_data *wdata);

void listbox_add_columns 			(gftp_window_data *wdata);

void listbox_clear           			(gftp_window_data *wdata);

void listbox_deselect_all    			(gftp_window_data *wdata);

void * listbox_get_selected_files 		(gftp_window_data *wdata, int only_one);

int  listbox_num_selected    			(gftp_window_data *wdata);

void listbox_save_column_width (gftp_window_data *local, gftp_window_data *remote);

void listbox_select_all      			(gftp_window_data *wdata);

void listbox_select_all_files 			(gftp_window_data *wdata);

void listbox_select_row      			(gftp_window_data *wdata, int n);

void listbox_set_default_column_width 		(gftp_window_data *wdata);

void listbox_sort_rows 				(gpointer data, gint column);

void listbox_update_filelist 			(gftp_window_data *wdata);

/* gtkui.c */
void gftpui_run_command 			( GtkWidget * widget,
						  gpointer data );

void gftpui_run_function_callback 		( gftp_window_data * wdata,
						  gftp_dialog_data * ddata );

void gftpui_run_function_cancel_callback 	( gftp_window_data * wdata,
						  gftp_dialog_data * ddata );

void gftpui_mkdir_dialog 			( gpointer data );

void gftpui_rename_dialog			( gpointer data );

void gftpui_site_dialog 			( gpointer data );

int gftpui_run_chdir 				( gpointer uidata,
						  char *directory );

void gftpui_chdir_dialog 			( gpointer data );

char * gftpui_gtk_get_utf8_file_pos 		( gftp_file * fle );

/* menu_items.c */
void change_filespec 				( gpointer data );

void save_directory_listing 			( gpointer data );

void show_selected				( gpointer data );

gboolean dir_combo_keycb (GtkWidget * widget, GdkEventKey *event, gpointer data);

void clearlog 					( gpointer data );

void viewlog 					( gpointer data );

void savelog 					( gpointer data );

void clear_cache				( gpointer data );

void compare_windows 				( gpointer data );

void about_dialog 				( gpointer data );
void delete_dialog 				( gpointer data );

/* misc-gtk.c */
void remove_files_window			( gftp_window_data * wdata );

void ftp_log					( gftp_logging_level level,
						  gftp_request * request,
						  const char *string,
						  ... ) GFTP_LOG_FUNCTION_ATTRIBUTES;

void update_window_info				( void );

void update_window				( gftp_window_data * wdata );

#if !defined(TRANSFER_GTK_TREEVIEW)
gftp_graphic * open_xpm (GtkWidget * widget,  char *filename);
void gftp_free_pixmap   (char *filename); 
void gftp_get_pixmap    (GtkWidget * widget,  char *filename, 
                         GdkPixmap ** pix,    GdkBitmap ** bitmap );
#endif

GdkPixbuf *       gftp_get_pixbuf (char *filename);

int check_status				( char *name,
						  gftp_window_data * wdata,
						  unsigned int check_other_stop,
						  unsigned int only_one,
						  unsigned int at_least_one,
						  unsigned int func );

void add_history 				( GtkWidget * widget, 
						  GList ** history, 
						  unsigned int *histlen, 
						  const char *str );

int check_reconnect 				( gftp_window_data * wdata );

void TextEntryDialog (GtkWindow * parent_window,       /* nullable */
                      char * title,   char * infotxt,
                      char * deftext, int passwd_item,
                      char * checktext, 
                      gftp_dialog_button okbutton, void (*okfunc) (), void *okptr,
                      void (*cancelfunc) (), void *cancelptr);

void YesNoDialog (GtkWindow * parent_window,              /* nullable */
                  char * title,       char * infotxt, 
                  void (*yesfunc) (), gpointer yespointer, 
                  void (*nofunc) (),  gpointer nopointer);

void display_cached_logs			( void );

char * get_image_path 				( char *filename);

void set_window_icon (GtkWindow *window, char *icon_name);
void glist_to_combobox (GList *list, GtkWidget *combo);
void populate_combo_and_select_protocol (GtkWidget *combo, char * selected_protocol);
GtkMenuItem * new_menu_item (GtkMenu * menu, char * label, char * icon_name,
                             gpointer activate_callback, gpointer callback_data);

/* options_dialog.c */
void options_dialog 				( gpointer data );

void gftp_gtk_setup_bookmark_options 		( GtkWidget * notebook,
						  gftp_bookmarks_var * bm );

void gftp_gtk_save_bookmark_options 		( void );

/* platform_specific.c */
void gftp_gtk_platform_specific_init		( void );

/* transfer.c */
extern struct transfer_tview_t transfer_tview;
#ifdef TRANSFER_GTK_TREEVIEW
void transfer_tview_append (gftpui_common_curtrans_data *transdata,
                            gftp_file *tempfle, char *filename, char *tinfo);
#endif

GtkWidget *transfer_list_create 		(void);

void transfer_list_save_column_width 		(void);

int  gftp_gtk_list_files				( gftp_window_data * wdata );

int gftp_gtk_connect					( gftp_window_data * wdata,
						  gftp_request * request );

gint update_downloads 				( gpointer data );

void get_files 					( gpointer data );

void put_files 					( gpointer data );

void transfer_window_files 			( gftp_window_data * fromwdata,
						  gftp_window_data * towdata );

int gftp_gtk_get_subdirs 			( gftp_transfer * transfer );

void *do_getdir_thread 				( void * data );

void start_transfer				( gpointer data );

void stop_transfer				( gpointer data );

void skip_transfer				( gpointer data );

void remove_file_transfer 			( gpointer data );

void move_transfer_up				( gpointer data );

void move_transfer_down				( gpointer data );

/* view_dialog.c */
void edit_dialog 				( gpointer data );

void view_dialog 				( gpointer data );

void view_file 					( char *filename, 
						  int fd, 
						  unsigned int viewedit, 
						  unsigned int del_file, 
						  unsigned int start_pos, 
						  unsigned int dontupload,
						  char *remote_filename, 
						  gftp_window_data * wdata );

//
//  CreateMenu Rewrite
//  FIXME: Move to menu_callbacks.h
extern void on_local_openurl_dialog (void);
extern void on_remote_openurl_dialog (void);
extern void on_local_gftpui_disconnect (void);
extern void on_remote_gftpui_disconnect (void);
extern void on_local_change_filespec (void);
extern void on_remote_change_filespec (void);
extern void on_local_show_selected (void);
void on_remote_show_selected (void);
void on_local_navi_up_directory (void);
void on_remote_navi_up_directory (void);
void on_local_selectall (void);
void on_remote_selectall (void);
void on_local_selectallfiles (void);
void on_remote_selectallfiles (void);
void on_local_deselectall (void);
void on_remote_deselectall (void);
void on_local_save_directory_listing (void);
void on_remote_save_directory_listing (void);
void on_local_gftpui_site_dialog (void);
void on_remote_gftpui_site_dialog (void);
void on_local_gftpui_chdir_dialog (void);
void on_remote_gftpui_chdir_dialog (void);
void on_local_chmod_dialog (void);
void on_remote_chmod_dialog (void);
void on_local_gftpui_mkdir_dialog (void);
void on_remote_gftpui_mkdir_dialog (void);
void on_local_gftpui_rename_dialog (void);
void on_remote_gftpui_rename_dialog (void);
void on_local_delete_dialog (void);
void on_remote_delete_dialog (void);
void on_local_edit_dialog(void);
void on_remote_edit_dialog(void);
void on_local_view_dialog (void);
void on_remote_view_dialog (void);
void on_local_gftp_gtk_refresh (void);
void on_remote_gftp_gtk_refresh (void);

// ===
// FIXME:
// When all of the legacy menu stuff is moved out of gftp-gtk.c
// This should be moved to where-ever we stick the legacy 
// Code until it can be disabled/removed

  static inline GtkActionEntry menu_items[] =
  {
    //  name                    stock_id               "label"                  accel             tooltip  callback
    { "FTPMenu",              NULL,                  N_("g_FTP"),             NULL,                NULL, NULL                   },
    { "FTPPreferences",       "gtk-preferences",     N_("_Preferences..."),   NULL,                NULL, G_CALLBACK(options_dialog) },
    { "FTPQuit",              "gtk-quit",            N_("_Quit"),             "<control>Q",        NULL, G_CALLBACK(_gftp_menu_exit)  },

    { "LocalMenu",            NULL,                  N_("_Local"),            NULL,                NULL, NULL },
    { "LocalOpenLocation",    "gtk-open",            N_("_Open Location..."), "<control><shift>O", NULL, G_CALLBACK(on_local_openurl_dialog) },
    { "LocalDisconnect",      "gtk-close",           N_("D_isconnect"),       "<control><shift>I", NULL, G_CALLBACK(on_local_gftpui_disconnect) },
    { "LocalChangeFilespec",  NULL,                  N_("Change _Filespec"),  "<control><shift>F", NULL, G_CALLBACK(on_local_change_filespec) },
    { "LocalShowSelected",    NULL,                  N_("_Show selected"),    NULL,                NULL, G_CALLBACK(on_local_show_selected) },
    { "LocalNavigateUp",      NULL,                  N_("Navigate _Up"),      "<ctrl><alt>Up",     NULL, G_CALLBACK(on_local_navi_up_directory) },
    { "LocalSelectAll",       NULL,                  N_("Select _All"),       "<control><shift>A", NULL, G_CALLBACK(on_local_selectall) },
    { "LocalSelectAllFiles",  NULL,                  N_("Select All Files"),  NULL,                NULL, G_CALLBACK(on_local_selectallfiles) },
    { "LocalDeselectAll",     NULL,                  N_("Deselect All"),      NULL,                NULL, G_CALLBACK(on_local_deselectall) },
    { "LocalSaveDirectoryListing", NULL,             N_("Save Directory Listing..."), NULL,        NULL, G_CALLBACK(on_local_save_directory_listing) },
    { "LocalSendSITECommand", NULL,                  N_("Send SITE Command.."),NULL,               NULL, G_CALLBACK(on_local_gftpui_site_dialog) },
    { "LocalChangeDirectory", NULL,                  N_("_Change Directory"), NULL,                NULL, G_CALLBACK(on_local_gftpui_chdir_dialog) },
    { "LocalPermissions",     NULL,                  N_("_Permissions..."),   "<control><shift>P", NULL, G_CALLBACK(on_local_chmod_dialog) },
    { "LocalNewFolder",       NULL,                  N_("_New Folder..."),    "<control><shift>N", NULL, G_CALLBACK(on_local_gftpui_mkdir_dialog) },
    { "LocalRename",          NULL,                  N_("Rena_me..."),        "<control><shift>M", NULL, G_CALLBACK(on_local_gftpui_rename_dialog) },
    { "LocalDelete",          NULL,                  N_("_Delete..."),        "<control><shift>D", NULL, G_CALLBACK(on_local_delete_dialog) },
    { "LocalEdit",            NULL,                  N_("_Edit..."),          "<control><shift>E", NULL, G_CALLBACK(on_local_edit_dialog) },
    { "LocalView",            NULL,                  N_("_View..."),          "<control><shift>L", NULL, G_CALLBACK(on_local_view_dialog) },
    { "LocalRefresh",         "gtk-refresh",         N_("_Refresh"),          "<control><shift>R", NULL, G_CALLBACK(on_local_gftp_gtk_refresh) },

    { "RemoteMenu",           NULL,                  N_("_Remote"),            NULL,               NULL, NULL },
    { "RemoteOpenLocation",   "gtk-open",            N_("_Open Location..."), "<control>O",        NULL, G_CALLBACK(on_remote_openurl_dialog) },
    { "RemoteDisconnect",     "gtk-close",           N_("D_isconnect"),       "<control>I",        NULL, G_CALLBACK(on_remote_gftpui_disconnect) },
    { "RemoteChangeFilespec", NULL,                  N_("Change _Filespec"),  "<control>F",        NULL, G_CALLBACK(on_remote_change_filespec) },
    { "RemoteShowSelected",   NULL,                  N_("_Show selected"),    NULL,                NULL, G_CALLBACK(on_remote_show_selected) },
    { "RemoteNavigateUp",     NULL,                  N_("Navigate _Up"),      "<alt>Up",           NULL, G_CALLBACK(on_remote_navi_up_directory) },
    { "RemoteSelectAll",      NULL,                  N_("Select _All"),       "<control>A",        NULL, G_CALLBACK(on_remote_selectall) },
    { "RemoteSelectAllFiles", NULL,                  N_("Select All Files"),  NULL,                NULL, G_CALLBACK(on_remote_selectallfiles) },
    { "RemoteDeselectAll",    NULL,                  N_("Deselect All"),      NULL,                NULL, G_CALLBACK(on_remote_deselectall) },
    { "RemoteSaveDirectoryListing", NULL,            N_("Save Directory Listing..."), NULL,        NULL, G_CALLBACK(on_remote_save_directory_listing) },
    { "RemoteSendSITECommand",NULL,                  N_("Send SITE Command.."),NULL,               NULL, G_CALLBACK(on_remote_gftpui_site_dialog) },
    { "RemoteChangeDirectory",NULL,                  N_("_Change Directory"), NULL,                NULL, G_CALLBACK(on_remote_gftpui_chdir_dialog) },
    { "RemotePermissions",    NULL,                  N_("_Permissions..."),   "<control>P",        NULL, G_CALLBACK(on_remote_chmod_dialog) },
    { "RemoteNewFolder",      NULL,                  N_("_New Folder..."),    "<control>N",        NULL, G_CALLBACK(on_remote_gftpui_mkdir_dialog) },
    { "RemoteRename",         NULL,                  N_("Rena_me..."),        "<control>M",        NULL, G_CALLBACK(on_remote_gftpui_rename_dialog) },
    { "RemoteDelete",         NULL,                  N_("_Delete..."),        "<control>D",        NULL, G_CALLBACK(on_remote_delete_dialog) },
    { "RemoteEdit",           NULL,                  N_("_Edit..."),          "<control>E",        NULL, G_CALLBACK(on_remote_edit_dialog) },
    { "RemoteView",           NULL,                  N_("_View..."),          "<control>L",        NULL, G_CALLBACK(on_remote_view_dialog) },
    { "RemoteRefresh",        "gtk-refresh",         N_("_Refresh"),          "<control>R",        NULL, G_CALLBACK(on_remote_gftp_gtk_refresh) },

    { "BookmarksMenu",        NULL,                  N_("_Bookmarks"),        NULL,                NULL, NULL },
    { "BookmarksAddBookmark", "gtk-add",             N_("Add _Bookmark"),     "<control>B",        NULL, G_CALLBACK(add_bookmark) },
    { "BookmarksEditBookmarks",NULL,                 N_("Edit Bookmarks"),    NULL,                NULL, G_CALLBACK(edit_bookmarks) },

    { "TransferMenu",         NULL,                  N_("_Transfer"),         NULL,                NULL, NULL },
    { "TransferStart",        NULL,                  N_("_Start"),            NULL,                NULL, G_CALLBACK(start_transfer) },
    { "TransferStop",         "gtk-stop",            N_("St_op"),             NULL,                NULL, G_CALLBACK(stop_transfer) },
    { "TransferSkipCurrentFile",NULL,                N_("Skip _Current File"),NULL,                NULL, G_CALLBACK(skip_transfer) },
    { "TransferRemoveFile",   "gtk-delete",          N_("_Remove File"),      NULL,                NULL, G_CALLBACK(remove_file_transfer) },
    { "TransferMoveFileUp",   "gtk-go-up",           N_("Move File _Up"),     NULL,                NULL, G_CALLBACK(move_transfer_up) },
    { "TransferMoveFileDown", "gtk-go-down",         N_("Move File _Down"),   NULL,                NULL, G_CALLBACK(move_transfer_down) },
    { "TransferRetrieveFiles",NULL,                  N_("_Retrieve Files"),   "<control>R",        NULL, G_CALLBACK(get_files) },
    { "TransferPutFiles",    NULL,                   N_("_Put Files"),        "<control>U",        NULL, G_CALLBACK(put_files) },

    { "LogMenu",             NULL,                   N_("L_og"),              NULL,                NULL, NULL },
    { "LogClear",            "gtk-clear",            N_("_Clear"),            NULL,                NULL, G_CALLBACK(clearlog) },
    { "LogView",             NULL,                   N_("_View"),             NULL,                NULL, G_CALLBACK(viewlog) },
    { "LogSave",             "gtk-save",             N_("_Save..."),          NULL,                NULL, G_CALLBACK(savelog) },

    { "ToolsMenu",           NULL,                   N_("Tool_s"),            NULL,                NULL, NULL },
    { "ToolsCompareWindows", NULL,                   N_("C_ompare Windows"),  NULL,                NULL, G_CALLBACK(compare_windows) },
    { "ToolsClearCache",     "gtk-clear",            N_("_Clear Cache"),      NULL,                NULL, G_CALLBACK(clear_cache) },

    { "HelpMenu",            NULL,                   N_("_Help"),             NULL,                NULL, NULL },
    { "HelpAbout",           "gtk-about",            N_("_About"),            NULL,                NULL, G_CALLBACK(about_dialog) },
  };

  static inline GtkToggleActionEntry menu_check_colormsg[] = {
    { "FTPColorMsg", NULL, N_("Colored messages"), "<control><alt>C", NULL,
      G_CALLBACK (on_activate_colored_msgs_cb), FALSE }, //FALSE: need a constant element
  };

  static inline GtkRadioActionEntry menu_radio_window[] = {
    { "FTPWindow1", NULL, N_("Window _1"), "<control>1", NULL, GFTP_MENU_ITEM_WIN1 },
    { "FTPWindow2", NULL, N_("Window _2"), "<control>2", NULL, GFTP_MENU_ITEM_WIN2 },
  };
  static inline GtkRadioActionEntry menu_radio_mode[] = {
    { "FTPAscii",  NULL, N_("_Ascii"),  NULL, NULL, GFTP_MENU_ITEM_ASCII },
    { "FTPBinary", NULL, N_("_Binary"), NULL, NULL, GFTP_MENU_ITEM_BINARY },
  };


#endif

