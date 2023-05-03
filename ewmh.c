#include <ewmh.h>
#include <main.h>
#include <xcb/xcb_ewmh.h>
#include <errno.h>
#include <stdio.h>


xcb_ewmh_connection_t *ewmh;


void ewmh_init() {
	ewmh = calloc(1, sizeof(xcb_ewmh_connection_t));
	if (xcb_ewmh_init_atoms_replies(ewmh, xcb_ewmh_init_atoms(wm.dpy, ewmh), NULL) == 0) {
		perror("ewmh init");
		exit(errno);
	}
}
