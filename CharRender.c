//
// Created by jimxu on 3/17/2021.
//

#include "CharRender.h"
#include "Seg7Simulator.h"


/**
 * @brief  Pass the 7 segment truth value to segment render, only have 5 letters so far
 * @note
 * @retval None
 */
void CharRender(short *canvas, char k, int x, int y) {
    if (k == 'P') {
        SegSimulator(1, 1, 0, 0, 1, 1, 1, x, y);
    } else if (k == 'A') {
        SegSimulator(1, 1, 1, 0, 1, 1, 1, x, y);
    } else if (k == 'U') {
        SegSimulator(0, 1, 1, 1, 1, 1, 0, x, y);
    } else if (k == 'S') {
        SegSimulator(1, 0, 1, 1, 0, 1, 1, x, y);
    } else if (k == 'E') {
        SegSimulator(1, 0, 0, 1, 1, 1, 1, x, y);
    }
};
