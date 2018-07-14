#include "settings.h"
#include <stdio.h>

settings_t settings = {-6.5, 6.5, -3.5, 3.5, 1000, 1, 0};

static const char* on_off(int value){
	if(value){
		return "ON";
	}
	return "OFF";
}

void show_settings(){
	printf("\n" );
	printf("h_view_lo: %f\n", settings.h_view_lo);
	printf("h_view_hi: %f\n", settings.h_view_hi);
	printf("v_view_lo: %f\n", settings.v_view_lo);
	printf("v_view_hi: %f\n", settings.v_view_hi);
	printf("integral_steps: %d\n", settings.integral_steps);
	printf("\n");
	printf("Draw Axis: %s.\n", on_off(settings.draw_axis));
	printf("Connect Dots: %s.\n", on_off(settings.connect_dots));
	printf("\n" );
}

void set_h_view(double lo, double hi){
	settings.h_view_lo = lo;
	settings.h_view_hi = hi;
}

void set_v_view(double lo, double hi){
	settings.v_view_lo = lo;
	settings.v_view_hi = hi;
}

void set_draw_axis(int value){
	settings.draw_axis = value;
}

void set_connect_dots(int value){
	settings.connect_dots = value;
}

void set_integral_steps(int steps){
	settings.integral_steps = steps;
}

void reset_settings(){
	settings.h_view_lo = -6.5;
	settings.h_view_hi = 6.5;
	settings.v_view_lo = -3.5;
	settings.v_view_hi = 3.5;
	settings.integral_steps = 1000;
	settings.draw_axis = 1;
	settings.connect_dots = 0;
}
