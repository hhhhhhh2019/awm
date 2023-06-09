#include <main.h>
#include <wm.h>
#include <vector.h>
#include <ewmh.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


wm_t wm;



char* XCB_LUT_ERRORS_CSTR[]  = {[XCB_REQUEST]="XCB_REQUEST",[XCB_VALUE]="XCB_VALUE",[XCB_WINDOW]="XCB_WINDOW",[XCB_PIXMAP]="XCB_PIXMAP",[XCB_ATOM]="XCB_ATOM",[XCB_CURSOR]="XCB_CURSOR",[XCB_FONT]="XCB_FONT",[XCB_MATCH]="XCB_MATCH",[XCB_DRAWABLE]="XCB_DRAWABLE",[XCB_ACCESS]="XCB_ACCESS",[XCB_ALLOC]="XCB_ALLOC",[XCB_COLORMAP]="XCB_COLORMAP",[XCB_G_CONTEXT]="XCB_G_CONTEXT",[XCB_ID_CHOICE]="XCB_ID_CHOICE",[XCB_NAME]="XCB_NAME",[XCB_LENGTH]="XCB_LENGTH",[XCB_IMPLEMENTATION]="XCB_IMPLEMENTATION"};

char* XCB_LUT_OPCODES_CSTR[] = {[XCB_CREATE_WINDOW]="XCB_CREATE_WINDOW",[XCB_CHANGE_WINDOW_ATTRIBUTES]="XCB_CHANGE_WINDOW_ATTRIBUTES",[XCB_GET_WINDOW_ATTRIBUTES]="XCB_GET_WINDOW_ATTRIBUTES",[XCB_DESTROY_WINDOW]="XCB_DESTROY_WINDOW",[XCB_DESTROY_SUBWINDOWS]="XCB_DESTROY_SUBWINDOWS",[XCB_CHANGE_SAVE_SET]="XCB_CHANGE_SAVE_SET",[XCB_REPARENT_WINDOW]="XCB_REPARENT_WINDOW",[XCB_MAP_WINDOW]="XCB_MAP_WINDOW",[XCB_MAP_SUBWINDOWS]="XCB_MAP_SUBWINDOWS",[XCB_UNMAP_WINDOW]="XCB_UNMAP_WINDOW",[XCB_UNMAP_SUBWINDOWS]="XCB_UNMAP_SUBWINDOWS",[XCB_CONFIGURE_WINDOW]="XCB_CONFIGURE_WINDOW",[XCB_CIRCULATE_WINDOW]="XCB_CIRCULATE_WINDOW",[XCB_GET_GEOMETRY]="XCB_GET_GEOMETRY",[XCB_QUERY_TREE]="XCB_QUERY_TREE",[XCB_INTERN_ATOM]="XCB_INTERN_ATOM",[XCB_GET_ATOM_NAME]="XCB_GET_ATOM_NAME",[XCB_CHANGE_PROPERTY]="XCB_CHANGE_PROPERTY",[XCB_DELETE_PROPERTY]="XCB_DELETE_PROPERTY",[XCB_GET_PROPERTY]="XCB_GET_PROPERTY",[XCB_LIST_PROPERTIES]="XCB_LIST_PROPERTIES",[XCB_SET_SELECTION_OWNER]="XCB_SET_SELECTION_OWNER",[XCB_GET_SELECTION_OWNER]="XCB_GET_SELECTION_OWNER",[XCB_CONVERT_SELECTION]="XCB_CONVERT_SELECTION",[XCB_SEND_EVENT]="XCB_SEND_EVENT",[XCB_GRAB_POINTER]="XCB_GRAB_POINTER",[XCB_UNGRAB_POINTER]="XCB_UNGRAB_POINTER",[XCB_GRAB_BUTTON]="XCB_GRAB_BUTTON",[XCB_UNGRAB_BUTTON]="XCB_UNGRAB_BUTTON",[XCB_CHANGE_ACTIVE_POINTER_GRAB]="XCB_CHANGE_ACTIVE_POINTER_GRAB",[XCB_GRAB_KEYBOARD]="XCB_GRAB_KEYBOARD",[XCB_UNGRAB_KEYBOARD]="XCB_UNGRAB_KEYBOARD",[XCB_GRAB_KEY]="XCB_GRAB_KEY",[XCB_UNGRAB_KEY]="XCB_UNGRAB_KEY",[XCB_ALLOW_EVENTS]="XCB_ALLOW_EVENTS",[XCB_GRAB_SERVER]="XCB_GRAB_SERVER",[XCB_UNGRAB_SERVER]="XCB_UNGRAB_SERVER",[XCB_QUERY_POINTER]="XCB_QUERY_POINTER",[XCB_GET_MOTION_EVENTS]="XCB_GET_MOTION_EVENTS",[XCB_TRANSLATE_COORDINATES]="XCB_TRANSLATE_COORDINATES",[XCB_WARP_POINTER]="XCB_WARP_POINTER",[XCB_SET_INPUT_FOCUS]="XCB_SET_INPUT_FOCUS",[XCB_GET_INPUT_FOCUS]="XCB_GET_INPUT_FOCUS",[XCB_QUERY_KEYMAP]="XCB_QUERY_KEYMAP",[XCB_OPEN_FONT]="XCB_OPEN_FONT",[XCB_CLOSE_FONT]="XCB_CLOSE_FONT",[XCB_QUERY_FONT]="XCB_QUERY_FONT",[XCB_QUERY_TEXT_EXTENTS]="XCB_QUERY_TEXT_EXTENTS",[XCB_LIST_FONTS]="XCB_LIST_FONTS",[XCB_LIST_FONTS_WITH_INFO]="XCB_LIST_FONTS_WITH_INFO",[XCB_SET_FONT_PATH]="XCB_SET_FONT_PATH",[XCB_GET_FONT_PATH]="XCB_GET_FONT_PATH",[XCB_CREATE_PIXMAP]="XCB_CREATE_PIXMAP",[XCB_FREE_PIXMAP]="XCB_FREE_PIXMAP",[XCB_CREATE_GC]="XCB_CREATE_GC",[XCB_CHANGE_GC]="XCB_CHANGE_GC",[XCB_COPY_GC]="XCB_COPY_GC",[XCB_SET_DASHES]="XCB_SET_DASHES",[XCB_SET_CLIP_RECTANGLES]="XCB_SET_CLIP_RECTANGLES",[XCB_FREE_GC]="XCB_FREE_GC",[XCB_CLEAR_AREA]="XCB_CLEAR_AREA",[XCB_COPY_AREA]="XCB_COPY_AREA",[XCB_COPY_PLANE]="XCB_COPY_PLANE",[XCB_POLY_POINT]="XCB_POLY_POINT",[XCB_POLY_LINE]="XCB_POLY_LINE",[XCB_POLY_SEGMENT]="XCB_POLY_SEGMENT",[XCB_POLY_RECTANGLE]="XCB_POLY_RECTANGLE",[XCB_POLY_ARC]="XCB_POLY_ARC",[XCB_FILL_POLY]="XCB_FILL_POLY",[XCB_POLY_FILL_RECTANGLE]="XCB_POLY_FILL_RECTANGLE",[XCB_POLY_FILL_ARC]="XCB_POLY_FILL_ARC",[XCB_PUT_IMAGE]="XCB_PUT_IMAGE",[XCB_GET_IMAGE]="XCB_GET_IMAGE",[XCB_POLY_TEXT_8]="XCB_POLY_TEXT_8",[XCB_POLY_TEXT_16]="XCB_POLY_TEXT_16",[XCB_IMAGE_TEXT_8]="XCB_IMAGE_TEXT_8",[XCB_IMAGE_TEXT_16]="XCB_IMAGE_TEXT_16",[XCB_CREATE_COLORMAP]="XCB_CREATE_COLORMAP",[XCB_FREE_COLORMAP]="XCB_FREE_COLORMAP",[XCB_COPY_COLORMAP_AND_FREE]="XCB_COPY_COLORMAP_AND_FREE",[XCB_INSTALL_COLORMAP]="XCB_INSTALL_COLORMAP",[XCB_UNINSTALL_COLORMAP]="XCB_UNINSTALL_COLORMAP",[XCB_LIST_INSTALLED_COLORMAPS]="XCB_LIST_INSTALLED_COLORMAPS",[XCB_ALLOC_COLOR]="XCB_ALLOC_COLOR",[XCB_ALLOC_NAMED_COLOR]="XCB_ALLOC_NAMED_COLOR",[XCB_ALLOC_COLOR_CELLS]="XCB_ALLOC_COLOR_CELLS",[XCB_ALLOC_COLOR_PLANES]="XCB_ALLOC_COLOR_PLANES",[XCB_FREE_COLORS]="XCB_FREE_COLORS",[XCB_STORE_COLORS]="XCB_STORE_COLORS",[XCB_STORE_NAMED_COLOR]="XCB_STORE_NAMED_COLOR",[XCB_QUERY_COLORS]="XCB_QUERY_COLORS",[XCB_LOOKUP_COLOR]="XCB_LOOKUP_COLOR",[XCB_CREATE_CURSOR]="XCB_CREATE_CURSOR",[XCB_CREATE_GLYPH_CURSOR]="XCB_CREATE_GLYPH_CURSOR",[XCB_FREE_CURSOR]="XCB_FREE_CURSOR",[XCB_RECOLOR_CURSOR]="XCB_RECOLOR_CURSOR",[XCB_QUERY_BEST_SIZE]="XCB_QUERY_BEST_SIZE",[XCB_QUERY_EXTENSION]="XCB_QUERY_EXTENSION",[XCB_LIST_EXTENSIONS]="XCB_LIST_EXTENSIONS",[XCB_CHANGE_KEYBOARD_MAPPING]="XCB_CHANGE_KEYBOARD_MAPPING",[XCB_GET_KEYBOARD_MAPPING]="XCB_GET_KEYBOARD_MAPPING",[XCB_CHANGE_KEYBOARD_CONTROL]="XCB_CHANGE_KEYBOARD_CONTROL",[XCB_GET_KEYBOARD_CONTROL]="XCB_GET_KEYBOARD_CONTROL",[XCB_BELL]="XCB_BELL",[XCB_CHANGE_POINTER_CONTROL]="XCB_CHANGE_POINTER_CONTROL",[XCB_GET_POINTER_CONTROL]="XCB_GET_POINTER_CONTROL",[XCB_SET_SCREEN_SAVER]="XCB_SET_SCREEN_SAVER",[XCB_GET_SCREEN_SAVER]="XCB_GET_SCREEN_SAVER",[XCB_CHANGE_HOSTS]="XCB_CHANGE_HOSTS",[XCB_LIST_HOSTS]="XCB_LIST_HOSTS",[XCB_SET_ACCESS_CONTROL]="XCB_SET_ACCESS_CONTROL",[XCB_SET_CLOSE_DOWN_MODE]="XCB_SET_CLOSE_DOWN_MODE",[XCB_KILL_CLIENT]="XCB_KILL_CLIENT",[XCB_ROTATE_PROPERTIES]="XCB_ROTATE_PROPERTIES",[XCB_FORCE_SCREEN_SAVER]="XCB_FORCE_SCREEN_SAVER",[XCB_SET_POINTER_MAPPING]="XCB_SET_POINTER_MAPPING",[XCB_GET_POINTER_MAPPING]="XCB_GET_POINTER_MAPPING"};



void loop();
void ev_error(xcb_generic_error_t*);
void ev_map_request(xcb_map_request_event_t*);
void ev_configure_request(xcb_configure_request_event_t*);
void ev_create(xcb_create_notify_event_t*);
void ev_destroy(xcb_destroy_notify_event_t*);

char is_managing(xcb_window_t);
void manage_window(xcb_window_t);

void focus(xcb_drawable_t);


int main() {
	wm_init(&wm);
	ewmh_init();
	loop();
	wm_end(wm);
}


void loop() {
	xcb_generic_event_t* ev;

	while (wm.running) {
		while (ev = xcb_poll_for_event(wm.dpy)) {
			switch (ev->response_type & ~0x80) {
				case 0:
					ev_error((xcb_generic_error_t*)ev);
					break;
				case XCB_CREATE_NOTIFY:
					printf("create\n");
					break;
				case XCB_DESTROY_NOTIFY:
					printf("destory\n");
					ev_destroy((xcb_destroy_notify_event_t*)ev);
					break;
				case XCB_CONFIGURE_REQUEST:
					printf("configure requset\n");
					ev_create((xcb_create_notify_event_t*)ev);
					ev_configure_request((xcb_configure_request_event_t*)ev);
					break;
				case XCB_CONFIGURE_NOTIFY:
					printf("configure notify\n");
					break;
				case XCB_MAP_REQUEST:
					printf("map requset\n");
					ev_map_request((xcb_map_request_event_t*)ev);
					break;
				case XCB_UNMAP_NOTIFY:
					printf("unmap\n");
					break;
				case XCB_CLIENT_MESSAGE:
					printf("client message\n");
					break;
				case XCB_PROPERTY_NOTIFY:
					printf("property\n");
					break;
				case XCB_MAPPING_NOTIFY:
					printf("mapping\n");
					break;

				free(ev);
			}
			xcb_flush(wm.dpy);
		}
	}
}


void ev_error(xcb_generic_error_t* ev) {
	printf("Error: %s %s %d %d\n", XCB_LUT_ERRORS_CSTR[ev->error_code], XCB_LUT_OPCODES_CSTR[ev->major_code], ev->minor_code, ev->resource_id);
}


void ev_map_request(xcb_map_request_event_t* ev) {
	xcb_map_window(wm.dpy, ev->window);
}

void ev_configure_request(xcb_configure_request_event_t* ev) {
	xcb_atom_t type = 0;

	xcb_get_property_cookie_t prop_cookie = xcb_get_property(wm.dpy, 0, ev->window, ewmh->_NET_WM_WINDOW_TYPE, XCB_ATOM_ATOM, 0, ~0);
	xcb_get_property_reply_t *prop_reply = xcb_get_property_reply(wm.dpy, prop_cookie, NULL);

	if (prop_reply) {
		type = ((xcb_atom_t*)xcb_get_property_value(prop_reply))[0];

		free(prop_reply);
	}


	printf("%d\n", type);


	if (type == 0 || type == ewmh->_NET_WM_WINDOW_TYPE_NORMAL) {
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

		xcb_configure_window(wm.dpy, ev->window, mask, value);


		xcb_configure_notify_event_t resp;

		resp.response_type = XCB_CONFIGURE_NOTIFY;
		resp.event = ev->window;
		resp.window = ev->window;
		resp.x = value[0];
		resp.y = value[1];
		resp.width = value[2];
		resp.height = value[3];
		resp.border_width = 0;
		resp.override_redirect = 0;

		xcb_send_event(wm.dpy, 0, ev->window, XCB_EVENT_MASK_STRUCTURE_NOTIFY, (char*)&resp);


		vec_forall(wm.normal_windows, i) {
			if (*i == ev->window)
				return;
		}

		vec_push(wm.normal_windows, ev->window);
	} else if (type == ewmh->_NET_WM_WINDOW_TYPE_DOCK) {
		char managing = 0;

		vec_forall(wm.dock_windows, i) {
			if (*i == ev->window) {
				managing = 1;
				break;
			}
		}

		if (managing == 0)
			vec_push(wm.dock_windows, ev->window);

		update_gaps(wm);
		update_configs(wm);
	}
}


void ev_create(xcb_create_notify_event_t* ev) {
	//printf("%s\n", get_window_property(ev->window, "_NET_WM_WINDOW_TYPE"));
}


void ev_destroy(xcb_destroy_notify_event_t* ev) {
	int id = 0;

	vec_forall(wm.dock_windows, i) {
		if (*i == ev->window) {
			vec_del(wm.dock_windows, id);
			update_gaps(wm);
			update_configs(wm);
			return;
		}

		id++;
	}


	id = 0;

	vec_forall(wm.normal_windows, i) {
		if (*i == ev->window) {
			vec_del(wm.normal_windows, id);
			return;
		}

		id++;
	}
}



void focus(xcb_drawable_t window) {
	if ((window != 0) && (window != wm.screen->root))
		xcb_set_input_focus(wm.dpy, XCB_INPUT_FOCUS_POINTER_ROOT, window, XCB_CURRENT_TIME);
}
