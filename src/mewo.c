#include <stdint.h>
#include <string.h>
#include "mewo.h"

#define SEC_PER_DAY (86400)
#define SEC_PER_HOUR (3600)

#define SLEEP_X_POS (10)

void _refresh_vbuffer(mewo *m);

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
    _refresh_vbuffer(m);
}

void _refresh_vbuffer(mewo *m) {
    memset(m->vbuffer, 0, sizeof(m->vbuffer));

    // TODO
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
                m->head_frame = MEWO_HEAD_FRAME_LEFT;
                break;
            case 2:
                m->head_frame = MEWO_HEAD_FRAME_RIGHT;
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
