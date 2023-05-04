#include <ewmh.h>
#include <main.h>
#include <xcb/xcb_ewmh.h>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


xcb_ewmh_connection_t *ewmh;


void ewmh_init() {
	ewmh = calloc(1, sizeof(xcb_ewmh_connection_t));

	if (xcb_ewmh_init_atoms_replies(ewmh, xcb_ewmh_init_atoms(wm.dpy, ewmh), NULL) == 0) {
		perror("Can't initialize EWMH atoms.\n");
		exit(errno);
	}
}


char* get_window_property(xcb_window_t win, char* name) {


	/*printf("id: %u\n", win);

	xcb_intern_atom_cookie_t atom_cookie = xcb_intern_atom(wm.dpy, 0, strlen(name), name);
	xcb_intern_atom_reply_t* atom_reply = xcb_intern_atom_reply(wm.dpy, atom_cookie, NULL);


	atom_reply->atom = ewmh->_NET_WM_WINDOW_TYPE;

	xcb_get_property_cookie_t property = xcb_get_property(wm.dpy, 0, win, atom_reply->atom, XCB_ATOM_ATOM, 0, ~0);
	xcb_get_property_reply_t* reply = xcb_get_property_reply(wm.dpy, property, NULL);

	if (reply == NULL) {
		printf("reply == NULL\n");
		return "";
	}

	int len = xcb_get_property_value_length(reply);

	printf("%d\n", len);

	/*xcb_get_atom_name_reply_t *reply_name = xcb_get_atom_name_reply(wm.dpy, xcb_get_atom_name(wm.dpy, atom), NULL);
	char* atom_name = xcb_get_atom_name_name(reply_name);

	//printf("---\n%s\n---\n", atom_name);* /

	free(atom_reply);
	free(reply);

	return "";*/
}
