#ifndef _PIECES_H
#define _PIECES_H

#define NUM_OF_PIECES 	2
#define ROTATIONS	4
#define PROWS		6
#define PCOLS		6

typedef unsigned short uint16_t;

typedef const char (piece_t)[PCOLS];

extern const char tetris[NUM_OF_PIECES][ROTATIONS][PROWS][PCOLS];

enum Pieces{
	PIECE_T,
	PIECE_L,
	PIECE_LM,
	PIECE_I,
	PIECE_N,
	PIECE_NM,
	PIECE_O
};

enum Rotations{
	ROTATION_NORMAL,
	ROTATION_CWISE,
	ROTATION_ANTI_CWISE,
	ROTATION_FLIPPED
};

typedef struct __piece{
	enum Pieces piece;
	enum Rotations rotation;
	uint16_t y_start;
	uint16_t x_start;
}Piece;

#endif
