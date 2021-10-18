#include <stdint.h>
#include "graphics.h"
#include "pieces.h"
#include "screen.h"

const enum Colors color_map[PCOLORS] = {
        COLOR_BLACK,
        COLOR_RED,
        COLOR_GREEN,
        COLOR_BLUE,
        COLOR_CYAN,
        COLOR_YELLOW,
        COLOR_MAGENTA
};

void show_new_piece(Window* win, Piece* p){

	piece_t *piece_arr = tetris[p->piece][p->rotation];
	
	//start location relative to the Window
	p->y_start = 2;
	p->x_start = (win->width - PCOLS) / 2 ;

	for(uint16_t i = 0; i < PROWS; i++){
		wmove(win, p->y_start + i, p->x_start);
		for(uint16_t j = 0; j < PCOLS; j++){
			wwrite_pixel(win, color_map[(*(piece_arr + i))[j]]);
		}
	}
}

void move_piece_down(Window *win, Piece *p){

	uint16_t py_end = p->y_start + PROWS - 1; //position of the last row in the piece to be moved

	uint16_t new_row, old_row;
	uint16_t col;

	for(uint16_t i = 0; i < PROWS; i++){
		new_row = win->width * (py_end - i + 1);
		old_row = new_row - win->width;

		for(uint16_t j = 0; j < PCOLS; j++){
			col = p->x_start + j;
			win->win_buff[new_row + col] = win->win_buff[old_row + col];
			win->win_buff[old_row + col] = 0;
		}
	}

	++p->y_start;

}

void move_piece_right(Window* win, Piece *p){

	/* 01100 0000
	 * 01100 0000
	 * 00100 0000
	 */

	uint16_t px_end = p->x_start + PCOLS - 1;

	piece_t *piece_arr = tetris[p->piece][p->rotation];

	for(uint16_t j = 1; j <= PCOLS; j++){
		
		for(uint16_t i = 0; i < PROWS; i++){

			if( (*(piece_arr + i))[PCOLS - j] > 0){
				win->win_buff[((p->y_start + i) * win->width) + px_end - j + 1]=
					color_map[(*(piece_arr + i))[PCOLS - j]];
				win->win_buff[((p->y_start + i) * win->width) + px_end - j]=0;
			}
		}
	}
	p->x_start++;
}
void move_piece_left(Window* win, Piece *p){

	/* 0000 01100
	 * 0000 01100
	 * 0000 00100
	 */

	piece_t *piece_arr = tetris[p->piece][p->rotation];

	for(uint16_t j = 0; j < PCOLS; j++){
		
		for(uint16_t i = 0; i < PROWS; i++){

			if( (*(piece_arr + i))[j] > 0){
				win->win_buff[((p->y_start + i) * win->width) + p->x_start + j-1]=
					win->win_buff[((p->y_start + i) * win->width) + p->x_start + j];
				win->win_buff[((p->y_start + i) * win->width) + p->x_start + j] = 0;
			}
		}
	}
	p->x_start--;
}

