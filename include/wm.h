#ifndef WM_H
#define WM_H


#include <xcb/xcb.h>


#define MAXLEN 256


extern int top_gap;
extern int bottom_gap;
extern int left_gap;
extern int right_gap;


typedef struct {
	xcb_connection_t* dpy;
	int screen_id;
	xcb_screen_t* screen;

	xcb_window_t* normal_windows;
	xcb_window_t* dock_windows;

	char running;
} wm_t;


typedef enum {
	STATE_NORMAL,
	STATE_FLOATING,
	STATE_FULLSCREEN
} client_state_t;


typedef enum {
	WM_FLAG_MODAL = 1 << 0,
	WM_FLAG_HIDDEN = 1 << 1,
	WM_FLAG_STICKY = 1 << 2
} wm_flags_t;


typedef struct {
	char class_name[MAXLEN];
	char instance_name[MAXLEN];
	char name[MAXLEN];

	client_state_t state;
	wm_flags_t flags;
} client_t;


void wm_init(wm_t*);
void wm_end(wm_t);

void update_gaps(wm_t);
void update_configs(wm_t);


#endif // WM_H
