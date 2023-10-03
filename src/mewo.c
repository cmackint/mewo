#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "mewo.h"
#include "frames.h"
#include "transforms.h"

#define SEC_PER_DAY (86400)
#define SEC_PER_HOUR (3600)

#define SLEEP_X_POS (10)

void _handle_sit(mewo *m);
void _handle_walk(mewo *m);
void _handle_sleep(mewo *m);
void _handle_state(mewo *m);

void _check_sleep_transition();

void mewo_init(mewo *m, mewo_config *config, uint64_t time_ms) {
    m->config = config;
    m->time_ms;
    m->last_trans_ms = time_ms;
    m->state = MEWO_STATE_SIT;

    memset(m->vbuffer, 0, sizeof(m->vbuffer));
    mewo_frames_init();
}

void mewo_tick(mewo *m, uint64_t time_ms) {
    m->time_ms = time_ms;
    _handle_state(m);
    mewo_refresh(m);
}

bool mewo_get_pixel(mewo *m, int x, int y) {
    if (x >= 0 && x < MEWO_DISPLAY_COLS && y >= 0 && y < MEWO_DISPLAY_ROWS) {
        return m->vbuffer[y][x];
    } else {
        return false;
    }
}

void mewo_set_body_frame(mewo *m, mewo_body_frame frame) {
    m->body_frame = frame;
    m->stale = true;
}

void mewo_set_head_frame(mewo *m, mewo_head_frame frame) {
    m->head_frame = frame;
    m->stale = true;
}

void _load_bitmap(mewo *m, int start_x, int start_y, uint8_t *fdata, int num_rows, int num_cols) {
    // Iterate through the frame pixels by row/col
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            uint8_t pix8 = fdata[row * num_cols + col];
            for (int bit_index = 0; bit_index < 8; bit_index++) {
                if (pix8 & (1 << bit_index)) {
                    // Convert the pixel coordinates from frame row/col to x/y
                    int x = start_x + col * 8 + (7 - bit_index);
                    int y = start_y + num_rows - (row+1);

                    if (y >= 0 && y < MEWO_DISPLAY_ROWS && x >= 0 && x < MEWO_DISPLAY_COLS) {
                        m->vbuffer[y][x] = true;
                    }
                }
            }
        }
    }
}

void mewo_refresh(mewo *m) {
    if (!m->stale) {
        return;
    }

    memset(m->vbuffer, 0, sizeof(m->vbuffer));

    switch (m->body_frame) {
        case MEWO_BODY_FRAME_WALK_A_LEFT:
            // TODO
            m->body_frame_info = &MEWO_BODY_WALK_A_LEFT;
            break;
        case MEWO_BODY_FRAME_WALK_A_RIGHT:
            // TODO
            m->body_frame_info = &MEWO_BODY_WALK_A_RIGHT;
            break;
        case MEWO_BODY_FRAME_WALK_B_LEFT:
            // TODO
            m->body_frame_info = &MEWO_BODY_SIT;
            break;
        case MEWO_BODY_FRAME_WALK_B_RIGHT:
            // TODO
            m->body_frame_info = &MEWO_BODY_SIT;
            break;
        case MEWO_BODY_FRAME_SIT:
            m->body_frame_info = &MEWO_BODY_SIT;
            break;
        case MEWO_BODY_FRAME_SIT_TAIL:
            // TODO
            m->body_frame_info = &MEWO_BODY_SIT;
            break;
        case MEWO_BODY_FRAME_SLEEP:
            // TODO
            m->body_frame_info = &MEWO_BODY_SIT;
            break;
    }

    int body_x = m->x_pos + m->body_frame_info->x_offset;
    int body_y = m->body_frame_info->y_offset;
    _load_bitmap(m, body_x, body_y, m->body_frame_info->fdata, m->body_frame_info->num_rows, m->body_frame_info->num_cols);

    switch (m->head_frame) {
        case MEWO_HEAD_FRAME_FORWARD:
            m->head_frame_info = &MEWO_HEAD_FORWARD;
            break;
        case MEWO_HEAD_FRAME_FORWARD_BLINK:
            // TODO
            m->head_frame_info = &MEWO_HEAD_FORWARD;
            break;
        case MEWO_HEAD_FRAME_SIDE_LEFT:
            m->head_frame_info = &MEWO_HEAD_SIDE_LEFT;
            break;
        case MEWO_HEAD_FRAME_SIDE_RIGHT:
            // TODO: Mirror
            m->head_frame_info = &MEWO_HEAD_SIDE_RIGHT;
            break;
    }
            
    int head_x = body_x + X_OFFSETS[m->body_frame][m->head_frame];
    int head_y = body_y + Y_OFFSETS[m->body_frame][m->head_frame];
    _load_bitmap(m, head_x, head_y, m->head_frame_info->fdata, m->head_frame_info->num_rows, m->head_frame_info->num_cols);

    m->stale = false;
}

void _handle_state(mewo *m) {
    switch (m->state) {
        case MEWO_STATE_SIT:
            _handle_sit(m);
            break;
        case MEWO_STATE_WALK:
            _handle_walk(m);
            break;
        case MEWO_STATE_SLEEP:
            _handle_sleep(m);
            break;
    }
}

void _handle_sit(mewo *m) {
    // Check for bed time
    if (m->time_ms >= m->config->sleep_time_ms) {
        m->state = MEWO_STATE_WALK;
        return;
    }

    // Occasionally move tail
    if (rand() % 10 == 0) {
        switch (m->body_frame) {
            case MEWO_BODY_FRAME_SIT:
                m->body_frame = MEWO_BODY_FRAME_SIT_TAIL;
                break;
            case MEWO_BODY_FRAME_SIT_TAIL:
            default:
                m->body_frame = MEWO_BODY_FRAME_SIT;
                break;
        }
    }

    // Ocassionally move head to random direction
    if (rand() % 10 == 0) {
        switch (rand() % 3) {
            case 0: 
                m->head_frame = MEWO_HEAD_FRAME_FORWARD;
                break;
            case 1: 
                m->head_frame = MEWO_HEAD_FRAME_SIDE_LEFT;
                break;
            case 2:
                m->head_frame = MEWO_HEAD_FRAME_SIDE_RIGHT;
                break;
        }
    }
}

void _handle_walk(mewo *m) {
    if (m->time_ms >= m->config->sleep_time_ms) {
        // Set the speed to walk to bed
        if (m->x_pos > SLEEP_X_POS) {
            // Walk to the left
            m->x_speed = -1;
        } else if (m->x_pos < SLEEP_X_POS) {
            // Walk to the right
            m->x_speed = 1;
        } else {
            m->x_speed = 0;
            m->state = MEWO_STATE_SLEEP;
            return;
        }
    } else {
        // Set the speed to walk back + forth
        if (m->x_pos <= 0) {
            m->x_speed = 1;
        } else if (m->x_pos >= MEWO_DISPLAY_COLS-1) {
            m->x_speed = -1;
        } else {
            m->x_speed = 1;
        }
        // TODO: Make this more interesting
    }

    // Set next body frame
    if (m->x_speed < 0 ) {
        switch (m->body_frame) {
            case MEWO_BODY_FRAME_WALK_B_LEFT:
                m->body_frame = MEWO_BODY_FRAME_WALK_A_LEFT;
                break;
            case MEWO_BODY_FRAME_WALK_A_LEFT:
            default:
                m->body_frame = MEWO_BODY_FRAME_WALK_B_LEFT;
                break;
        }
    } else {
         switch (m->body_frame) {
            case MEWO_BODY_FRAME_WALK_B_RIGHT:
                m->body_frame = MEWO_BODY_FRAME_WALK_A_RIGHT;
                break;
            case MEWO_BODY_FRAME_WALK_A_RIGHT:
            default:
                m->body_frame = MEWO_BODY_FRAME_WALK_B_RIGHT;
                break;
        }
    }

    // Set next head frame
    m->head_frame = m->head_frame;
}

void _handle_sleep(mewo *m) {
    if (m->time_ms >= m->config->wakeup_time_ms) {
        m->state = MEWO_STATE_SIT;
        return;
    }
}
