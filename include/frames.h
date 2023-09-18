#ifndef MEWO_FRAMES_H
#define MEWO_FRAMES_H

#include <stdint.h>
#include "mewo.h"


#define _FDATA_BODY_SIT_ROWS (17)
#define _FDATA_BODY_SIT_COLS (4)
uint8_t _FDATA_BODY_SIT[_FDATA_BODY_SIT_ROWS][_FDATA_BODY_SIT_COLS] = {
    {0x00, 0x20, 0x00},
    {0x40, 0x10, 0x00},
    {0x80, 0x08, 0xc0},
    {0x80, 0x04, 0xa0},
    {0x80, 0x04, 0x90},
    {0x80, 0x02, 0x48},
    {0x80, 0x42, 0x28},
    {0x40, 0x42, 0x28},
    {0x44, 0x42, 0x28},
    {0x44, 0x42, 0x48},
    {0x44, 0x83, 0x90},
    {0x24, 0x82, 0x20},
    {0x24, 0x87, 0xc0},
    {0x1b, 0x78, 0x00}
};
mewo_frame_info MEWO_BODY_SIT = {
    .fdata = (uint8_t **) _FDATA_BODY_SIT,
    .num_rows = _FDATA_BODY_SIT_ROWS,
    .num_cols = _FDATA_BODY_SIT_COLS,
    .y_offset = 0,
    .x_offset = 0
};


// Head frames

#define _FDATA_HEAD_FORWARD_ROWS (17)
#define _FDATA_HEAD_FORWARD_COLS (4)
uint8_t _FDATA_HEAD_FORWARD[_FDATA_HEAD_FORWARD_ROWS][_FDATA_HEAD_FORWARD_COLS] = {
    {0x00, 0xff, 0x80, 0x00},
    {0x03, 0x00, 0x60, 0x00},
    {0xfc, 0x00, 0x1f, 0x80},
    {0x80, 0x00, 0x00, 0x80},
    {0x98, 0x00, 0x0c, 0x80},
    {0x44, 0x00, 0x11, 0x00},
    {0x48, 0x00, 0x09, 0x00},
    {0x20, 0x00, 0x02, 0x00},
    {0x10, 0x00, 0x04, 0x00},
    {0x11, 0x80, 0xc4, 0x00},
    {0x12, 0xc1, 0x64, 0x00},
    {0x13, 0xc1, 0xe4, 0x00},
    {0x09, 0x80, 0xc8, 0x00},
    {0x08, 0x08, 0x08, 0x00},
    {0x04, 0x00, 0x10, 0x00},
    {0x03, 0x80, 0xe0, 0x00},
    {0x00, 0x7f, 0x00, 0x00}
};
mewo_frame_info MEWO_HEAD_FORWARD = {
    .fdata = (uint8_t **) _FDATA_HEAD_FORWARD,
    .num_rows = _FDATA_HEAD_FORWARD_ROWS,
    .num_cols = _FDATA_HEAD_FORWARD_COLS,
    .y_offset = 0,
    .x_offset = 0
};

#define _FDATA_HEAD_SIDE_ROWS (18)
#define _FDATA_HEAD_SIDE_COLS (4)
uint8_t _FDATA_HEAD_SIDE[_FDATA_HEAD_SIDE_ROWS][_FDATA_HEAD_SIDE_COLS] = {
    {0x00, 0x0a, 0x00},
    {0x00, 0x15, 0x00},
    {0x00, 0x29, 0x00},
    {0x03, 0xf0, 0x80},
    {0x0c, 0x02, 0x80},
    {0x10, 0x04, 0x80},
    {0x20, 0x01, 0x40},
    {0x20, 0x00, 0x40},
    {0x27, 0x00, 0x20},
    {0x4b, 0x80, 0x20},
    {0x4f, 0x00, 0x20},
    {0x46, 0x00, 0x20},
    {0x80, 0x00, 0x20},
    {0xcc, 0x00, 0x40},
    {0x90, 0x00, 0x40},
    {0x4e, 0x00, 0x80},
    {0x20, 0x03, 0x00},
    {0x1f, 0xfc, 0x00}
};
mewo_frame_info MEWO_HEAD_SIDE = {
    .fdata = (uint8_t **) _FDATA_HEAD_SIDE,
    .num_rows = _FDATA_HEAD_SIDE_ROWS,
    .num_cols = _FDATA_HEAD_SIDE_COLS,
    .y_offset = 0,
    .x_offset = 0
};

#endif