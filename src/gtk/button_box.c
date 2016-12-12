/* Button Boxes
 *
 * The Button Box widgets are used to arrange buttons with padding.
 */

/* Boxes are going away in favor of grids. At some point we should switch too */

#include <gtk/gtk.h>

#define gtk_box_new gtk_hbox_new

/* Our usual callback function */
static void callback( GtkWidget *widget,
                     gpointer   data )
{
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

static GtkWidget *icon_label_box( gchar     *stock_icon_name,
                                 gchar     *label_text )
{
    GtkWidget *box;
    GtkWidget *label;
    GdkPixbuf *icon;
    GtkWidget *image;
    
    /* Create box for image and label */
    box = gtk_box_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 2);
    
    /* Load theme */
    GtkIconTheme *icon_theme;
    icon_theme = gtk_icon_theme_get_default ();
    
    /* stock icon from theme */
    icon = gtk_icon_theme_load_icon (icon_theme, stock_icon_name, 48, 0, NULL);
    image = gtk_image_new_from_pixbuf (icon);
    
    /* From local file if not from theme */
    // image = gtk_image_new_from_file ("some filename");
    
    /* Create a label for the button */
    label = gtk_label_new (label_text);
    
    /* Pack the image and label into the box */
    gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 3);
    gtk_box_pack_end (GTK_BOX (box), label, FALSE, FALSE, 3);
    
    gtk_widget_show (image);
    gtk_widget_show (label);
    
    return box;
}


static GtkWidget *
create_inventory_bbox (gint  horizontal,
	     char *title, 
	     gint  spacing,
	     gint  layout)
{
  GtkWidget *frame;
  GtkWidget *bbox;
  GtkWidget *button;
    
  frame = gtk_frame_new (title);

  if (horizontal)
    bbox = gtk_hbutton_box_new ();
  else
    bbox = gtk_vbutton_box_new ();

  gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
  gtk_container_add (GTK_CONTAINER (frame), bbox);
    
 //////////////////////////////////////////////
  /* Providers and Instances */
    GtkWidget *instance_button;
    GtkWidget *box;
    
    /* Create a instance button */
    instance_button = gtk_button_new ();
    
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (instance_button, "clicked",
                      G_CALLBACK (callback), (gpointer) "cool button");
    
    /* This calls our box creating function */
    box = icon_label_box ("network-idle", "Providers and Instances");
    
    /* Pack and show all our widgets */
    gtk_container_add (GTK_CONTAINER (instance_button), box);
    gtk_container_add (GTK_CONTAINER (bbox), instance_button);
    
 //////////////////////////////////////
    
    
    //////////////////////////////////////////////
    /* Providers and Instances */
    GtkWidget *networks_button;
 
    /* Create a networks button */
    networks_button = gtk_button_new ();
    
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (networks_button, "clicked",
                      G_CALLBACK (callback), (gpointer) "cool button");
    
    /* This calls our box creating function */
    box = icon_label_box ("network-wired", "Cloud Networks");
    
    /* Pack and show all our widgets */
    gtk_container_add (GTK_CONTAINER (networks_button), box);
    gtk_container_add (GTK_CONTAINER (bbox), networks_button);
    
    //////////////////////////////////////
    
    //////////////////////////////////////////////
    /* Drives */
    GtkWidget *drives_button;
    
    /* Create a networks button */
    drives_button = gtk_button_new ();
    
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (drives_button, "clicked",
                      G_CALLBACK (callback), (gpointer) "cool button");
    
    /* This calls our box creating function */
    box = icon_label_box ("drive-multidisk", "Cloud Storge");
    
    /* Pack and show all our widgets */
    gtk_container_add (GTK_CONTAINER (drives_button), box);
    gtk_container_add (GTK_CONTAINER (bbox), drives_button);
    
    //////////////////////////////////////
    
    
    
#if 0
    /* stock buttons */
    gtk_button_box_set_layout (GTK_BUTTON_BOX (bbox), layout);
    gtk_box_set_spacing (GTK_BOX (bbox), spacing);
    
    button = gtk_button_new_from_stock (GTK_STOCK_OK);
    gtk_container_add (GTK_CONTAINER (bbox), button);
    
    button = gtk_button_new_from_stock (GTK_STOCK_CANCEL);
    gtk_container_add (GTK_CONTAINER (bbox), button);

    button = gtk_button_new_from_stock (GTK_STOCK_HELP);
    gtk_container_add (GTK_CONTAINER (bbox), button);
#endif
    
  return frame;
}


static GtkWidget *
create_admin_bbox (gint  horizontal,
             char *title,
             gint  spacing,
             gint  layout)
{
    GtkWidget *frame;
    GtkWidget *bbox;
    GtkWidget *button;
    
    frame = gtk_frame_new (title);
    
    if (horizontal)
        bbox = gtk_hbutton_box_new ();
    else
        bbox = gtk_vbutton_box_new ();
    
    gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
    gtk_container_add (GTK_CONTAINER (frame), bbox);
    
    //////////////////////////////////////////////
    /* Python Command Prompt */
    GtkWidget *python_cmd_button;
    GtkWidget *box;
    
    /* Create a instance button */
    python_cmd_button = gtk_button_new ();
    
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (python_cmd_button, "clicked",
                      G_CALLBACK (callback), (gpointer) "cool button");
    
    /* This calls our box creating function */
    box = icon_label_box ("utilities-terminal", "Python Console");
    
    /* Pack and show all our widgets */
    gtk_container_add (GTK_CONTAINER (python_cmd_button), box);
    gtk_container_add (GTK_CONTAINER (bbox), python_cmd_button);
    
    //////////////////////////////////////
    
    //////////////////////////////////////////////
    /* PowerShell Command Prompt */
    GtkWidget *ps_cmd_button;
  
    
    /* Create a instance button */
    ps_cmd_button = gtk_button_new ();
    
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (ps_cmd_button, "clicked",
                      G_CALLBACK (callback), (gpointer) "cool button");
    
    /* This calls our box creating function */
    box = icon_label_box ("utilities-terminal-symbolic", "Powershell Console");
    
    /* Pack and show all our widgets */
    gtk_container_add (GTK_CONTAINER (ps_cmd_button), box);
    gtk_container_add (GTK_CONTAINER (bbox), ps_cmd_button);
    
    //////////////////////////////////////

    //////////////////////////////////////////////
    /* System Monitor */
    GtkWidget *instance_button;
    
    /* Create a instance button */
    instance_button = gtk_button_new ();
    
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (instance_button, "clicked",
                      G_CALLBACK (callback), (gpointer) "cool button");
    
    /* This calls our box creating function */
    box = icon_label_box ("utilities-system-monitor", "Monitoring");
    
    /* Pack and show all our widgets */
    gtk_container_add (GTK_CONTAINER (instance_button), box);
    gtk_container_add (GTK_CONTAINER (bbox), instance_button);
    
    //////////////////////////////////////
    
    
    //////////////////////////////////////////////
    /* Application Settings */
    GtkWidget *settings_button;
    
    
    /* Create a instance button */
    settings_button = gtk_button_new ();
    
    /* Connect the "clicked" signal of the button to our callback */
    g_signal_connect (settings_button, "clicked",
                      G_CALLBACK (callback), (gpointer) "cool button");
    
    /* This calls our box creating function */
    box = icon_label_box ("emblem-system", "Multicloud Settings");
    
    /* Pack and show all our widgets */
    gtk_container_add (GTK_CONTAINER (settings_button), box);
    gtk_container_add (GTK_CONTAINER (bbox), settings_button);
    
    //////////////////////////////////////
    
    return frame;
}

static GtkWidget *
create_misc_bbox (gint  horizontal,
                   char *title,
                   gint  spacing,
                   gint  layout)
{
    GtkWidget *frame;
    GtkWidget *bbox;
    GtkWidget *button;
    
    frame = gtk_frame_new (title);
    
    if (horizontal)
        bbox = gtk_hbutton_box_new ();
    else
        bbox = gtk_vbutton_box_new ();
    
    gtk_container_set_border_width (GTK_CONTAINER (bbox), 5);
    gtk_container_add (GTK_CONTAINER (frame), bbox);
    
    //////////////////////////////////////

    button = gtk_button_new_from_stock (GTK_STOCK_HELP);
    gtk_container_add (GTK_CONTAINER (bbox), button);
    
    return frame;
}

GtkWidget *
do_button_box ()
{
  GtkWidget *window = NULL;
  GtkWidget *main_vbox;
  GtkWidget *vbox;
  GtkWidget *hbox;
  GtkWidget *grid;
  GtkWidget *frame_horz;
  GtkWidget *frame_vert;
	
    /* We want to show text with our buttons */
 //   GtkSettings *default_settings = gtk_settings_get_default();
 //   g_object_set(default_settings, "gtk-button-images", TRUE, NULL);
    
    
 // if (!window)
 // {
#if 0
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_screen (GTK_WINDOW (window),
			   gtk_widget_get_screen (do_widget));
    gtk_window_set_title (GTK_WINDOW (window), "Button Boxes");
    
    g_signal_connect (window, "destroy",
		      G_CALLBACK (gtk_widget_destroyed),
		      &window);
#endif
    window = gtk_frame_new (NULL);

    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    main_vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), main_vbox);
    
    frame_horz = gtk_frame_new ("Horizontal Button Boxes");
    gtk_box_pack_start (GTK_BOX (main_vbox), frame_horz, TRUE, TRUE, 10);
    
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (vbox), 10);
    gtk_container_add (GTK_CONTAINER (frame_horz), vbox);

    gtk_box_pack_start (GTK_BOX (vbox), 
			create_inventory_bbox (TRUE, "Inventories", 1, GTK_BUTTONBOX_CENTER),
			TRUE, TRUE, 0);

//    gtk_box_pack_start (GTK_BOX (vbox),
//			create_monitoring_bbox (TRUE, "Monitoring", 1, GTK_BUTTONBOX_CENTER),
//			create_bbox (TRUE, "Monitoring", 40, GTK_BUTTONBOX_EDGE),
//			TRUE, TRUE, 5);
    
    gtk_box_pack_start (GTK_BOX (vbox),
			create_admin_bbox (TRUE, "Administration", 1, GTK_BUTTONBOX_CENTER),
//			create_admin_bbox (TRUE, "Administration", 1, GTK_BUTTONBOX_START),
			TRUE, TRUE, 5);
    
    gtk_box_pack_start (GTK_BOX (vbox), 
			create_misc_bbox (TRUE, "Misc", 1, GTK_BUTTONBOX_CENTER),
			TRUE, TRUE, 5);

      
/* Vertical Button Boxes
 
    frame_vert = gtk_frame_new ("Vertical Button Boxes");
    gtk_box_pack_start (GTK_BOX (main_vbox), frame_vert, TRUE, TRUE, 10);
    
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (hbox), 10);
    gtk_container_add (GTK_CONTAINER (frame_vert), hbox);

    gtk_box_pack_start (GTK_BOX (hbox), 
			create_bbox (FALSE, "Spread", 30, GTK_BUTTONBOX_SPREAD),
			TRUE, TRUE, 0);

    gtk_box_pack_start (GTK_BOX (hbox), 
			create_bbox (FALSE, "Edge", 30, GTK_BUTTONBOX_EDGE),
			TRUE, TRUE, 5);

    gtk_box_pack_start (GTK_BOX (hbox), 
			create_bbox (FALSE, "Start", 30, GTK_BUTTONBOX_START),
			TRUE, TRUE, 5);

    gtk_box_pack_start (GTK_BOX (hbox), 
			create_bbox (FALSE, "End", 30, GTK_BUTTONBOX_END),
			TRUE, TRUE, 5);
*/
       
 // }
#if 0
  if (!gtk_widget_get_visible (window))
    {
      gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);
      gtk_widget_show_all (window);
    }
  else
    {	 
      gtk_widget_destroy (window);
      window = NULL;
    }
#endif
  return window;
}
