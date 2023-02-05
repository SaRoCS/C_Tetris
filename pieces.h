#ifndef pieces_h
#define pieces_h

typedef struct piece_struct {
    char shape[4][4];
    int useColor;
} piece;

int shapePiece(piece* p, int shape);

#endif