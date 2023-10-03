#ifndef MEWO_H
#define MEWO_H

#include <stdint.h>
#include <stdbool.h>

#define MEWO_DISPLAY_COLS (128)
#define MEWO_DISPLAY_ROWS (64)

typedef enum {
    MEWO_STATE_SIT,
    MEWO_STATE_WALK,
    MEWO_STATE_SLEEP,
} mewo_state;

typedef struct {
    uint8_t *fdata;
    int num_rows;
    int num_cols;
    int y_offset;
    int x_offset;
} mewo_frame_info;

typedef enum {
    MEWO_BODY_FRAME_WALK_A_LEFT,
    MEWO_BODY_FRAME_WALK_A_RIGHT,
    MEWO_BODY_FRAME_WALK_B_LEFT,
    MEWO_BODY_FRAME_WALK_B_RIGHT,
    MEWO_BODY_FRAME_SIT,
    MEWO_BODY_FRAME_SIT_TAIL,
    MEWO_BODY_FRAME_SLEEP,
} mewo_body_frame;

typedef enum {
    MEWO_HEAD_FRAME_FORWARD,
    MEWO_HEAD_FRAME_FORWARD_BLINK,
    MEWO_HEAD_FRAME_SIDE_LEFT,
    MEWO_HEAD_FRAME_SIDE_RIGHT
} mewo_head_frame;

typedef struct {
    char *name;
    uint64_t wakeup_time_ms;
    uint64_t sleep_time_ms;
} mewo_config;

typedef struct {
    mewo_config *config;
    uint64_t time_ms;
    mewo_state state;
    uint64_t last_trans_ms;
    uint16_t x_pos;
    int16_t x_speed;
    mewo_body_frame body_frame;
    mewo_frame_info *body_frame_info;
    mewo_head_frame head_frame;
    mewo_frame_info *head_frame_info;
    bool stale;
    bool vbuffer[MEWO_DISPLAY_ROWS][MEWO_DISPLAY_COLS];
} mewo;

void mewo_init(mewo *m, mewo_config *config, uint64_t time_ms);

/**
 * time_sec: Number of seconds into current day. [0, 86400)
*/
void mewo_tick(mewo *m, uint64_t time_ms);

void mewo_refresh(mewo *m);

bool mewo_get_pixel(mewo *m, int row_index, int col_index);

void mewo_set_body_frame(mewo *m, mewo_body_frame frame);

void mewo_set_head_frame(mewo *m, mewo_head_frame frame);

#endif
