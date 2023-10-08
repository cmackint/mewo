#include <stdint.h>
#include "frames.h"

int X_OFFSETS[MEWO_BODY_FRAME_LEN][MEWO_HEAD_FRAME_LEN] = {
    {-7, 0, -3, -8},
    {14, 0, 18, 12},
    {-8, 0, -4, -10},
    {7, 0, 11, 4},
    {-6, 0, -2, -8},
    {-6, 0, -2, -8},
    {0, 0, 0, 0}
};

int Y_OFFSETS[MEWO_BODY_FRAME_LEN][MEWO_HEAD_FRAME_LEN] = {
    {13, 0, 13, 13},
    {13, 0, 13, 13},
    {13, 0, 13, 13},
    {13, 0, 13, 13},
    {13, 0, 13, 13},
    {13, 0, 13, 13},
    {0, 0, 0, 0}
};

// Body frames

#define _FDATA_BODY_SIT_ROWS (14)
#define _FDATA_BODY_SIT_COLS (3)
uint8_t _FDATA_BODY_SIT[_FDATA_BODY_SIT_ROWS * _FDATA_BODY_SIT_COLS] = {
    0x00, 0x20, 0x00,
    0x40, 0x10, 0x00,
    0x80, 0x08, 0xc0,
    0x80, 0x04, 0xa0,
    0x80, 0x04, 0x90,
    0x80, 0x02, 0x48,
    0x80, 0x42, 0x28,
    0x40, 0x42, 0x28,
    0x44, 0x42, 0x28,
    0x44, 0x42, 0x48,
    0x44, 0x83, 0x90,
    0x24, 0x82, 0x20,
    0x24, 0x87, 0xc0,
    0x1b, 0x78, 0x00
};
mewo_body_frame_info MEWO_BODY_SIT = {
    .fdata = _FDATA_BODY_SIT,
    .num_rows = _FDATA_BODY_SIT_ROWS,
    .num_cols = _FDATA_BODY_SIT_COLS,
    .y_offset = 0,
    .x_offset = 6
};


#define _FDATA_BODY_SIT_TAIL_ROWS (14)
#define _FDATA_BODY_SIT_TAIL_COLS (3)
uint8_t _FDATA_BODY_SIT_TAIL[_FDATA_BODY_SIT_TAIL_ROWS * _FDATA_BODY_SIT_TAIL_COLS] = {
    0x00, 0x20, 0x00,
    0x40, 0x10, 0x00,
    0x80, 0x08, 0x08,
    0x80, 0x04, 0x14,
    0x80, 0x04, 0x14,
    0x80, 0x02, 0x14,
    0x80, 0x42, 0x24,
    0x40, 0x42, 0x24,
    0x44, 0x42, 0x28,
    0x44, 0x42, 0x48,
    0x44, 0x83, 0x90,
    0x24, 0x82, 0x20,
    0x24, 0x87, 0xc0,
    0x1b, 0x78, 0x00
};
mewo_body_frame_info MEWO_BODY_SIT_TAIL = {
    .fdata = _FDATA_BODY_SIT_TAIL,
    .num_rows = _FDATA_BODY_SIT_TAIL_ROWS,
    .num_cols = _FDATA_BODY_SIT_TAIL_COLS,
    .y_offset = 0,
    .x_offset = 6
};



#define _FDATA_BODY_WALK_A_ROWS (20)
#define _FDATA_BODY_WALK_A_COLS (4)
uint8_t _FDATA_BODY_WALK_A_LEFT[_FDATA_BODY_WALK_A_ROWS * _FDATA_BODY_WALK_A_COLS] = {
    0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x02, 0x80,
    0x00, 0x00, 0x02, 0x80,
    0x00, 0x00, 0x02, 0x80,
    0x00, 0x00, 0x04, 0x80,
    0x00, 0x00, 0x05, 0x00,
    0x20, 0x40, 0x09, 0x00,
    0x40, 0x3f, 0xf2, 0x00,
    0x40, 0x00, 0x04, 0x00,
    0x80, 0x00, 0x04, 0x00,
    0x80, 0x00, 0x04, 0x00,
    0x80, 0x00, 0x08, 0x00,
    0x80, 0x00, 0x08, 0x00,
    0x88, 0x04, 0x08, 0x00,
    0x88, 0x04, 0x08, 0x00,
    0x8f, 0xc2, 0x10, 0x00,
    0x94, 0x3e, 0x30, 0x00,
    0x94, 0x02, 0x50, 0x00,
    0x94, 0x02, 0x50, 0x00,
    0x78, 0x01, 0xe0, 0x00
};
mewo_body_frame_info MEWO_BODY_WALK_A_LEFT = {
    .fdata = _FDATA_BODY_WALK_A_LEFT,
    .num_rows = _FDATA_BODY_WALK_A_ROWS,
    .num_cols = _FDATA_BODY_WALK_A_COLS,
    .y_offset = 0,
    .x_offset = 7
};
uint8_t _FDATA_BODY_WALK_A_RIGHT[_FDATA_BODY_WALK_A_ROWS * _FDATA_BODY_WALK_A_COLS];
mewo_body_frame_info MEWO_BODY_WALK_A_RIGHT;


#define _FDATA_BODY_WALK_B_ROWS (20)
#define _FDATA_BODY_WALK_B_COLS (3)
uint8_t _FDATA_BODY_WALK_B_LEFT[_FDATA_BODY_WALK_B_ROWS * _FDATA_BODY_WALK_B_COLS] = {
    0x00, 0x00, 0x02,
    0x00, 0x00, 0x05,
    0x00, 0x00, 0x05,
    0x00, 0x00, 0x05,
    0x00, 0x00, 0x09,
    0x00, 0x00, 0x0a,
    0x40, 0x80, 0x12,
    0x80, 0x7f, 0xe4,
    0x80, 0x00, 0x08,
    0x80, 0x00, 0x08,
    0x80, 0x00, 0x08,
    0x80, 0x00, 0x10,
    0x80, 0x00, 0x10,
    0x44, 0x04, 0x10,
    0x44, 0x04, 0x08,
    0xa7, 0x82, 0x08,
    0xa4, 0x7d, 0x88,
    0xa4, 0x01, 0x48,
    0xa4, 0x01, 0x48,
    0x78, 0x00, 0xf0
};
mewo_body_frame_info MEWO_BODY_WALK_B_LEFT = {
    .fdata = _FDATA_BODY_WALK_B_LEFT,
    .num_rows = _FDATA_BODY_WALK_B_ROWS,
    .num_cols = _FDATA_BODY_WALK_B_COLS,
    .y_offset = 0,
    .x_offset = 8
};
uint8_t _FDATA_BODY_WALK_B_RIGHT[_FDATA_BODY_WALK_B_ROWS * _FDATA_BODY_WALK_B_COLS];
mewo_body_frame_info MEWO_BODY_WALK_B_RIGHT;


// Head frames

#define _FDATA_HEAD_FORWARD_ROWS (17)
#define _FDATA_HEAD_FORWARD_COLS (4)
uint8_t _FDATA_HEAD_FORWARD[_FDATA_HEAD_FORWARD_ROWS * _FDATA_HEAD_FORWARD_COLS] = {
    0x00, 0xff, 0x80, 0x00,
    0x03, 0x00, 0x60, 0x00,
    0xfc, 0x00, 0x1f, 0x80,
    0x80, 0x00, 0x00, 0x80,
    0x98, 0x00, 0x0c, 0x80,
    0x44, 0x00, 0x11, 0x00,
    0x48, 0x00, 0x09, 0x00,
    0x20, 0x00, 0x02, 0x00,
    0x10, 0x00, 0x04, 0x00,
    0x11, 0x80, 0xc4, 0x00,
    0x12, 0xc1, 0x64, 0x00,
    0x13, 0xc1, 0xe4, 0x00,
    0x09, 0x80, 0xc8, 0x00,
    0x08, 0x08, 0x08, 0x00,
    0x04, 0x00, 0x10, 0x00,
    0x03, 0x80, 0xe0, 0x00,
    0x00, 0x7f, 0x00, 0x00
};
mewo_head_frame_info MEWO_HEAD_FORWARD = {
    .fdata = _FDATA_HEAD_FORWARD,
    .num_rows = _FDATA_HEAD_FORWARD_ROWS,
    .num_cols = _FDATA_HEAD_FORWARD_COLS
};

#define _FDATA_HEAD_SIDE_ROWS (18)
#define _FDATA_HEAD_SIDE_COLS (3)
uint8_t _FDATA_HEAD_SIDE_LEFT[_FDATA_HEAD_SIDE_ROWS * _FDATA_HEAD_SIDE_COLS] = {
    0x00, 0x0a, 0x00,
    0x00, 0x15, 0x00,
    0x00, 0x29, 0x00,
    0x03, 0xf0, 0x80,
    0x0c, 0x02, 0x80,
    0x10, 0x04, 0x80,
    0x20, 0x01, 0x40,
    0x20, 0x00, 0x40,
    0x27, 0x00, 0x20,
    0x4b, 0x80, 0x20,
    0x4f, 0x00, 0x20,
    0x46, 0x00, 0x20,
    0x80, 0x00, 0x20,
    0xcc, 0x00, 0x40,
    0x90, 0x00, 0x40,
    0x4e, 0x00, 0x80,
    0x20, 0x03, 0x00,
    0x1f, 0xfc, 0x00
};
mewo_head_frame_info MEWO_HEAD_SIDE_LEFT = {
    .fdata = _FDATA_HEAD_SIDE_LEFT,
    .num_rows = _FDATA_HEAD_SIDE_ROWS,
    .num_cols = _FDATA_HEAD_SIDE_COLS
};
uint8_t _FDATA_HEAD_SIDE_RIGHT[_FDATA_HEAD_SIDE_ROWS * _FDATA_HEAD_SIDE_COLS];
mewo_head_frame_info MEWO_HEAD_SIDE_RIGHT;


void mewo_frames_init() {
    mirror_x(_FDATA_HEAD_SIDE_LEFT, _FDATA_HEAD_SIDE_RIGHT, _FDATA_HEAD_SIDE_ROWS, _FDATA_HEAD_SIDE_COLS);
    MEWO_HEAD_SIDE_RIGHT = (mewo_head_frame_info) {
        .fdata = _FDATA_HEAD_SIDE_RIGHT,
        .num_rows = _FDATA_HEAD_SIDE_ROWS,
        .num_cols = _FDATA_HEAD_SIDE_COLS
    };

    mirror_x(_FDATA_BODY_WALK_A_LEFT, _FDATA_BODY_WALK_A_RIGHT, _FDATA_BODY_WALK_A_ROWS, _FDATA_BODY_WALK_A_COLS);
    MEWO_BODY_WALK_A_RIGHT = (mewo_body_frame_info) {
        .fdata = _FDATA_BODY_WALK_A_RIGHT,
        .num_rows = _FDATA_BODY_WALK_A_ROWS,
        .num_cols = _FDATA_BODY_WALK_A_COLS,
        .y_offset = 0,
        .x_offset = -5
    };
    
    mirror_x(_FDATA_BODY_WALK_B_LEFT, _FDATA_BODY_WALK_B_RIGHT, _FDATA_BODY_WALK_B_ROWS, _FDATA_BODY_WALK_B_COLS);
    MEWO_BODY_WALK_B_RIGHT = (mewo_body_frame_info) {
        .fdata = _FDATA_BODY_WALK_B_RIGHT,
        .num_rows = _FDATA_BODY_WALK_B_ROWS,
        .num_cols = _FDATA_BODY_WALK_B_COLS,
        .y_offset = 0,
        .x_offset = 3
    };
}
