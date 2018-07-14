#ifndef SETTINGS_H
#define SETTINGS_H

typedef struct _settings{
	double h_view_lo;
	double h_view_hi;
	double v_view_lo;
	double v_view_hi;
	int integral_steps;
	int draw_axis;
	int connect_dots;
} settings_t;

extern settings_t settings;

void show_settings();
void set_h_view(double lo, double hi);
void set_v_view(double lo, double hi);
void set_draw_axis(int value);
void set_connect_dots(int value);
void set_integral_steps(int steps);
void reset_settings();

#endif
