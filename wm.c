#include <wm.h>
#include <vector.h>
#include <ewmh.h>
#include <main.h>
#include <xcb/xcb.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>



int top_gap = 0;
int bottom_gap = 0;
int left_gap = 0;
int right_gap = 0;


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

	wm->normal_windows = vec_init(xcb_window_t);
	wm->dock_windows = vec_init(xcb_window_t);

	wm->running = 1;
}


void wm_end(wm_t wm) {
	xcb_disconnect(wm.dpy);
}


void update_gaps(wm_t wm) {
	top_gap = 0;
	bottom_gap = 0;
	left_gap = 0;
	right_gap = 0;

	int scx = wm.screen->width_in_pixels / 2;
	int scy = wm.screen->height_in_pixels / 2;

	printf("dock windows:\n");
	vec_forall(wm.dock_windows, win) {
		xcb_get_geometry_cookie_t geom_cookie = xcb_get_geometry(wm.dpy, *win);
		xcb_get_geometry_reply_t* geom_reply = xcb_get_geometry_reply(wm.dpy, geom_cookie, NULL);

		int x = geom_reply->x;
		int y = geom_reply->y;
		int w = geom_reply->width;
		int h = geom_reply->height;

		int cx = x + w / 2;
		int cy = y + h / 2;

		printf("\tx: %d, y: %d, width: %d, height: %d\n", x,y,w,h);

		if (w > h) {
			if (cy < scy)
				top_gap += y + h;
			else
				bottom_gap += wm.screen->height_in_pixels - y;
		} else {
			if (cx < scx)
				left_gap += x + w;
			else
				right_gap += wm.screen->width_in_pixels - x;
		}
	}

	printf("\tl: %d  r: %d  t: %d  b: %d\n", left_gap, right_gap, top_gap, bottom_gap);
}


void update_configs(wm_t wm) {
	printf("normal windows:\n");
	vec_forall(wm.normal_windows, win) {
		xcb_get_geometry_cookie_t geom_cookie = xcb_get_geometry(wm.dpy, *win);
		xcb_get_geometry_reply_t* geom_reply = xcb_get_geometry_reply(wm.dpy, geom_cookie, NULL);

		printf("\tx: %d, y: %d, width: %d, height: %d\n", geom_reply->x, geom_reply->y, geom_reply->width, geom_reply->height);

		unsigned int mask =
			XCB_CONFIG_WINDOW_X	  |
			XCB_CONFIG_WINDOW_Y	  |
			XCB_CONFIG_WINDOW_WIDTH  |
			XCB_CONFIG_WINDOW_HEIGHT
		;

		unsigned int value[4] = {
			left_gap,
			top_gap,
			wm.screen->width_in_pixels - left_gap - right_gap,
			wm.screen->height_in_pixels - top_gap - bottom_gap
		};

		xcb_configure_window(wm.dpy, *win, mask, value);


		xcb_configure_notify_event_t resp;

		resp.response_type = XCB_CONFIGURE_NOTIFY;
		resp.event = *win;
		resp.window = *win;
		resp.x = value[0];
		resp.y = value[1];
		resp.width = value[2];
		resp.height = value[3];
		resp.border_width = 0;
		resp.override_redirect = 0;

		xcb_send_event(wm.dpy, 0, *win, XCB_EVENT_MASK_STRUCTURE_NOTIFY, (char*)&resp);
	}
}
