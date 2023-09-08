#include <stdint.h>

#define DISPLAY_COLS (128)
#define DISPLAY_ROWS (64)

typedef enum {
    MEWO_STATE_SIT,
    MEWO_STATE_WALK,
    MEWO_STATE_SLEEP,
} mewo_state;

typedef enum {
    MEWO_BODY_FRAME_WALK_A,
    MEWO_BODY_FRAME_WALK_B,
    MEWO_BODY_FRAME_SIT,
    MEWO_BODY_FRAME_SIT_TAIL,
    MEWO_BODY_FRAME_SLEEP,
} mewo_body_frame;

typedef enum {
    MEWO_HEAD_FRAME_FORWARD,
    MEWO_HEAD_FRAME_FORWARD_BLINK,
    MEWO_HEAD_FRAME_LEFT,
    MEWO_HEAD_FRAME_RIGHT
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
    mewo_head_frame head_frame;
    int vbuffer[DISPLAY_ROWS][DISPLAY_COLS];
} mewo;

void mewo_init(mewo *m, mewo_config *config, uint64_t time_ms, );

/**
 * time_sec: Number of seconds into current day. [0, 86400)
*/
void mewo_tick(mewo *m, uint64_t time_ms);
