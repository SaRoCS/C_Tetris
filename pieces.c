#include <stdio.h>
#include <stdlib.h>
#include "pieces.h"

int shapePiece(piece* p, int shape){
    //default populate with blank array
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            p->shape[i][j] = '*';
        }
    } 
    //add blocks at different positions depending on the shape to make and assign color
    switch (shape){
        case 0://o
            p->shape[0][0] = 'o';
            p->shape[0][1] = 'o';
            p->shape[1][0] = 'o';
            p->shape[1][1] = 'o';

            p->useColor = 7;
            break;
        case 1://s
            p->shape[0][1] = 's';
            p->shape[0][2] = 's';
            p->shape[1][0] = 's';
            p->shape[1][1] = 's';

            p->useColor = 1;
            break;
        case 2://z
            p->shape[0][0] = 'z';
            p->shape[0][1] = 'z';
            p->shape[1][1] = 'z';
            p->shape[1][2] = 'z';

            p->useColor = 2;
            break;
        case 3://t
            p->shape[0][1] = 't';
            p->shape[1][0] = 't';
            p->shape[1][1] = 't';
            p->shape[1][2] = 't';

            p->useColor = 3;
            break;
        case 4://l
            p->shape[0][2] = 'l';
            p->shape[1][0] = 'l';
            p->shape[1][1] = 'l';
            p->shape[1][2] = 'l';

            p->useColor = 4;
            break;
        case 5://j
            p->shape[0][0] = 'j';
            p->shape[1][0] = 'j';
            p->shape[1][1] = 'j';
            p->shape[1][2] = 'j';

            p->useColor = 5;
            break;
        case 6://i
            p->shape[0][0] = 'i';
            p->shape[0][1] = 'i';
            p->shape[0][2] = 'i';
            p->shape[0][3] = 'i';

            p->useColor = 6;
            break;
        default:
            return -1;
    }
    return 1;
}