#include "plot.h"
#include "tree.h"
#include <stdio.h>
#include "settings.h"

static const int rows = 25;
static const int cols = 80;

void plot(){
	if(!function){
		printf("\n");
		printf("No Function defined!\n");
		printf("\n");
		return;
	}
	char screen[rows][cols];
	double i_steps = (settings.v_view_hi - settings.v_view_lo) / rows;
	double j_steps = (settings.h_view_hi - settings.h_view_lo) / cols;

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			screen[i][j] = ' ';
		}
	}

	if(settings.draw_axis){
		int j = (0 - settings.h_view_lo) / j_steps;
		if(j >= 0 && j < cols){
			for(int i = 0; i < rows; i++){
				screen[i][j] = '|';
			}
		}

		int i = (0 - settings.v_view_lo) / i_steps;
		if(i >= 0 && i < rows){
			for(int j = 0; j < cols; j++){
				screen[i][j] = '-';
			}
		}

		if((j >= 0 && j < cols) && (i >= 0 && i < rows)){
			screen[i][j] = '+';
		}
	}

	for(int j = 0; j < cols; j++){
		double x = j * j_steps + settings.h_view_lo;
		double y = eval(function, x);
		int i = (y - settings.v_view_lo) / i_steps;
		if(i >= 0 && i < rows){
			screen[i][j] = '*';
		}
	}

	printf("\n");
	for(int i = rows-1; i >= 0; i--){
		for(int j = 0; j < cols; j++){
			printf("%c", screen[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
