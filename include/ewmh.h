#ifndef EWMH_H
#define EWMH_H


#include <xcb/xcb_ewmh.h>


extern xcb_ewmh_connection_t *ewmh;


void ewmh_init();


#endif // EWMH_H
