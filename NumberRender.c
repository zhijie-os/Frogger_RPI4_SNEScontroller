//
// Created by jimxu on 3/17/2021.
//

#include "NumberRender.h"
#include "Seg7Simulator.h"

/**
 * @brief  Takes the number param, convert to truth value, pass to 7 segment renderer
 * @note
 * @retval None
 */
void numberRender(short *canvas, int k, int x, int y) {
    if (k == 1) {
        SegSimulator(0, 1, 1, 0, 0, 0, 0, x, y);
    } else if (k == 2) {
        SegSimulator(1, 1, 0, 1, 1, 0, 1, x, y);
    } else if (k == 3) {
        SegSimulator(1, 1, 0, 1, 0, 0, 1, x, y);
    } else if (k == 4) {
        SegSimulator(0, 1, 1, 0, 0, 1, 1, x, y);
    } else if (k == 5) {
        SegSimulator(1, 0, 1, 1, 0, 1, 1, x, y);

    } else if (k == 6) {
        SegSimulator(1, 0, 1, 1, 1, 1, 1, x, y);

    } else if (k == 7) {
        SegSimulator(1, 1, 1, 0, 0, 0, 0, x, y);

    } else if (k == 8) {
        SegSimulator(1, 1, 1, 1, 1, 1, 1, x, y);

    } else if (k == 9) {
        SegSimulator(1, 1, 1, 1, 0, 1, 1, x, y);

    } else if (k == 0) {
        SegSimulator(1, 1, 1, 1, 1, 1, 0, x, y);

    }
};
