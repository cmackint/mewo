#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "mewo.h"
#include "frames.h"

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
}

void mewo_tick(mewo *m, uint64_t time_ms) {
    m->time_ms = time_ms;
    _handle_state(m);
    mewo_refresh(m);
}

bool mewo_get_pixel(mewo *m, int row_index, int col_index) {
    return m->vbuffer[row_index][col_index];
}

void mewo_set_body_frame(mewo *m, mewo_body_frame frame) {
    m->body_frame = frame;
    m->stale = true;
}

void mewo_set_head_frame(mewo *m, mewo_head_frame frame) {
    m->head_frame = frame;
    m->stale = true;
}

void _load_bitmap(mewo *m, int start_x, int start_y, mewo_frame_info *frame_info) {
    // Iterate through the frame pixels by row/col
    for (int row = 0; row < frame_info->num_rows; row++) {
        for (int col = 0; col < frame_info->num_cols; col++) {
            uint8_t pix8 = m->body_frame_info->fdata[row][col];
            for (int bit_index = 0; bit_index < 8; bit_index++) {
                if (pix8 & (1 << bit_index)) {
                    // Convert the pixel coordinates from frame row/col to vbuffer x/y
                    int x = start_x + col;
                    int y = start_y + m->body_frame_info->num_rows - (row+1);

                    // Convert the pixel coordinatesfrom vbuffer x/y to vbuffer row/col
                    int vbuff_row = DISPLAY_ROWS - y - 1;
                    int vbuff_col = x;

                    // Set the vbuffer pixel if in bounds
                    if (vbuff_row >= 0 && vbuff_row < DISPLAY_ROWS && vbuff_col >= 0 && vbuff_col < DISPLAY_COLS) {
                        m->vbuffer[vbuff_row][vbuff_col] = true;
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
        case MEWO_BODY_FRAME_WALK_A:
            // TODO
            m->body_frame_info = &MEWO_BODY_SIT;
            break;
        case MEWO_BODY_FRAME_WALK_B:
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
    _load_bitmap(m, body_x, body_y, m->body_frame_info);

    switch (m->head_frame) {
        case MEWO_HEAD_FRAME_FORWARD:
            m->head_frame_info = &MEWO_HEAD_FORWARD;
            break;
        case MEWO_HEAD_FRAME_FORWARD_BLINK:
            // TODO
            m->head_frame_info = &MEWO_HEAD_FORWARD;
            break;
        case MEWO_HEAD_FRAME_SIDE_LEFT:
            m->head_frame_info = &MEWO_HEAD_SIDE;
            break;
        case MEWO_HEAD_FRAME_SIDE_RIGHT:
            // TODO: Mirror
            m->head_frame_info = &MEWO_HEAD_SIDE;
            break;
    }
            
    int head_x = m->x_pos + m->head_frame_info->x_offset + m->body_frame_info->x_offset;
    int head_y = m->head_frame_info->y_offset + m->body_frame_info->y_offset;
    _load_bitmap(m, head_x, head_y, m->head_frame_info);

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
        } else if (m->x_pos >= DISPLAY_COLS-1) {
            m->x_speed = -1;
        } else {
            m->x_speed = 1;
        }
        // TODO: Make this more interesting
    }

    // Set next body frame
    switch (m->body_frame) {
        case MEWO_BODY_FRAME_WALK_B:
            m->body_frame = MEWO_BODY_FRAME_WALK_A;
            break;
        case MEWO_BODY_FRAME_WALK_A:
        default:
            m->body_frame = MEWO_BODY_FRAME_WALK_B;
            break;
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
