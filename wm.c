#include <wm.h>
#include <vector.h>
#include <ewmh.h>
#include <xcb/xcb.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>



unsigned int values[3];


void wm_init(wm_t* wm) {
	wm->dpy = xcb_connect(NULL, &wm->screen_id);

	if (xcb_connection_has_error(wm->dpy)) {
		perror("xcb_connect");
		exit(errno);
	}

	wm->screen = xcb_setup_roots_iterator(xcb_get_setup(wm->dpy)).data;

	unsigned int values[1] = { 33554431 |
		XCB_EVENT_MASK_STRUCTURE_NOTIFY    |
		XCB_EVENT_MASK_RESIZE_REDIRECT     |
		XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY |
		XCB_EVENT_MASK_RESIZE_REDIRECT
	};

	xcb_change_window_attributes(wm->dpy, wm->screen->root, XCB_CW_EVENT_MASK, values);

	xcb_flush(wm->dpy);

	wm->running = 1;
}


void wm_end(wm_t* wm) {
	xcb_disconnect(wm->dpy);
}
