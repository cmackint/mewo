#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "mewo.h"

void run_frame_validation();
void draw_mewo(mewo *m);

int main() {	
    run_frame_validation();
    return EXIT_SUCCESS;
}

void run_frame_validation() {
    mewo_config m_conf = {
        .name = "Mewo",
        .wakeup_time_ms = 0,
        .sleep_time_ms = 0
    };
    mewo m = {};

    mewo_init(&m, &m_conf, 0);

    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_SIT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_FORWARD);
    // mewo_refresh(&m);
    // draw_mewo(&m);

    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_SIT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_SIDE_LEFT);
    // mewo_refresh(&m);
    // draw_mewo(&m);

    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_SIT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_SIDE_RIGHT);
    // mewo_refresh(&m);
    // draw_mewo(&m);



    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_WALK_A_LEFT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_SIDE_LEFT);
    // mewo_refresh(&m);
    // draw_mewo(&m);

    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_WALK_A_LEFT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_SIDE_RIGHT);
    // mewo_refresh(&m);
    // draw_mewo(&m);

    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_WALK_A_LEFT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_FORWARD);
    // mewo_refresh(&m);
    // draw_mewo(&m);



    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_WALK_A_RIGHT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_SIDE_RIGHT);
    // mewo_refresh(&m);
    // draw_mewo(&m);

    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_WALK_A_RIGHT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_SIDE_LEFT);
    // mewo_refresh(&m);
    // draw_mewo(&m);

    // mewo_set_body_frame(&m, MEWO_BODY_FRAME_WALK_A_RIGHT);
    // mewo_set_head_frame(&m, MEWO_HEAD_FRAME_FORWARD);
    // mewo_refresh(&m);
    // draw_mewo(&m);
}

void draw_mewo(mewo *m) {
    for (int y = MEWO_DISPLAY_ROWS - 1; y >= 0; y--) {
        for (int x = 0; x < MEWO_DISPLAY_COLS; x++) {
            bool pixel = mewo_get_pixel(m, x, y);

            if (pixel) {
                printf("o");
            } else {
                printf("_");
            }
        }
        printf("\n");
    }
    for (int x = 0; x < MEWO_DISPLAY_COLS; x++) {
        printf("#");
    }
    printf("\n");
}
