//
// Created by jimxu on 3/17/2021.
//

#include "Seg7Simulator.h"

int WIDTH;
int LENGTH;

// TODO: pass the canvas to this function so that it can draw on the spot using 7 seg display

/**
 * @brief  Render the letters / numbers through CharRender, NumberRender drivers, parameters of each segment is passed
 * as int of 0 / 1 to determine whether render the Segment or not. first 7 param for segments, last 2 param for
 * location of render
 * @note
 * @retval None
 */
void SegSimulator(int a, int b, int c, int d, int e, int f, int g, int x, int y) {

    int temp_x = 0;
    int temp_y = 0;

    WIDTH = 10;
    LENGTH = 50;

    // Order: A G D F B E C, horizontal then vertical

    if(a){
        // Draw left to right, top to bottom
        for (int i = x + temp_x; i < x + temp_x + LENGTH; i++) {
            for (int j = y + temp_y; j < y + temp_y + WIDTH; j++) {
                // TODO: Paint COLOR_CODE at the pixel of (i, j) on canvas
            }
        }
    }

    // Add displacement to y, to move cursor down
    temp_y += LENGTH;

    if(g){
        // Draw left to right, top to bottom
        for (int i = x + temp_x; i < x + temp_x + LENGTH; i++) {
            for (int j = y + temp_y; j < y + temp_y + WIDTH; j++) {
                // TODO: Paint COLOR_CODE at the pixel of (i, j) on canvas
            }
        }
    }

    temp_y += LENGTH;

    if(d){
        // Draw left to right, top to bottom
        for (int i = x + temp_x; i < x + temp_x + LENGTH; i++) {
            for (int j = y + temp_y; j < y + temp_y + WIDTH; j++) {
                // TODO: Paint COLOR_CODE at the pixel of (i, j) on canvas
            }
        }
    }

    // reset to draw vertical
    temp_x = 0;
    temp_y = 0;

    if(f){
        // Draw left to right, top to bottom
        for (int i = x + temp_x; i < x + temp_x + LENGTH; i++) {
            for (int j = y + temp_y; j < y + temp_y + WIDTH; j++) {
                // TODO: Paint COLOR_CODE at the pixel of (i, j) on canvas
            }
        }
    }

    temp_x += LENGTH;

    if(b){
        // Draw left to right, top to bottom
        for (int i = x + temp_x; i < x + temp_x + LENGTH; i++) {
            for (int j = y + temp_y; j < y + temp_y + WIDTH; j++) {
                // TODO: Paint COLOR_CODE at the pixel of (i, j) on canvas
            }
        }
    }

    temp_y += LENGTH;
    temp_x = 0;

    if(e){
        // Draw left to right, top to bottom
        for (int i = x + temp_x; i < x + temp_x + LENGTH; i++) {
            for (int j = y + temp_y; j < y + temp_y + WIDTH; j++) {
                // TODO: Paint COLOR_CODE at the pixel of (i, j) on canvas
            }
        }
    }

    temp_x += LENGTH;

    if(c){
        // Draw left to right, top to bottom
        for (int i = x + temp_x; i < x + temp_x + LENGTH; i++) {
            for (int j = y + temp_y; j < y + temp_y + WIDTH; j++) {
                // TODO: Paint COLOR_CODE at the pixel of (i, j) on canvas
            }
        }
    }

}

