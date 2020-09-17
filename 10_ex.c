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
    int framerate = 0;
    while(is_open){
        if(!x_time_elapsed(&framerate, 25))
            continue;
        int ev;
        while(x_poll_event(&ev)){
            if(ev == X_EVENT_QUIT)
                is_open = false;
            if(ev == X_EVENT_LEFTCLICK){
                int x = x_get_mouse_x();
                int y = x_get_mouse_y();
                x_fill_square(x, y, 50);
            }
            if(ev == X_EVENT_RIGHTCLICK){
                int x = x_get_mouse_x();
                int y = x_get_mouse_y();
                x_fill_square(x, y, 100);
            }
        }

        x_set_color("k");
        //x_clear();
        x_set_color_rgba(155, 155, 155, 255);
        x_write(0, 0, 0, "press q to leave");
        int x = x_get_mouse_x();
        int y = x_get_mouse_y();
        x_plot(x, y);
        if(x_time_elapsed(&timer, 200)){
            ind += dir;
            if(ind == 0 || ind == 4)
                dir *= -1;
        }
        x_draw_sprite(TEX_SHIP, ind, 200, 200);
        x_display();
    }
    x_close();
}