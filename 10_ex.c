#define X_FULL
#include "sh.h"
#include <stdbool.h>


int main(){
    x_open(800, 600, "sei la");
    int TEX_SHIP = x_load_sprite("ships.bmp", 2, 5, 50, 50);
    int timer = 0;
    int ind = 0;
    int dir = 1;
    bool is_open = true;
    while(is_open){
        int ev;
        while(x_pool_event(&ev)){
            if(ev == X_EVENT_QUIT)
                is_open = false;
            if(ev == X_EVENT_LEFTCLICK){
                int x, y;
                x_get_mouse_pos(&x, &y);
                x_fill_square(x, y, 50);
            }
            if(ev == X_EVENT_RIGHTCLICK){
                int x, y;
                x_get_mouse_pos(&x, &y);
                x_fill_square(x, y, 100);
            }
        }

        X_CC('k');
        //x_clear();
        x_set_color(x_make_color(155, 155, 155, 255));
        x_write(0, 0, 0, "press q to leave");
        int x, y;
        x_get_mouse_pos(&x, &y);
        x_plot(x, y);
        if(x_timer(&timer, 200)){
            ind += dir;
            if(ind == 0 || ind == 4)
                dir *= -1;
        }
        x_draw_sprite(TEX_SHIP, ind, 200, 200);
        x_display();
    }
    x_close();
}