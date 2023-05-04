#ifndef EWMH_H
#define EWMH_H


#include <xcb/xcb_ewmh.h>
#include <xcb/xcb.h>


extern xcb_ewmh_connection_t *ewmh;


void ewmh_init();
char* get_window_property(xcb_window_t, char*);


#endif // EWMH_H
