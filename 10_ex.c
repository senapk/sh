#define SH_FULL
#include "sh.h"
#include <stdbool.h>


int main(){
    sh_init(800, 600);
    int TEX_SHIP = sh_sprite_save("ships.bmp", 2, 5, 50, 50);
    int timer = 0;
    int ind = 0;
    int dir = 1;
    bool is_open = true;
    while(is_open){
        int ev;
        while((ev = sh_input_get())){
            if(ev == sh_EVQUIT)
                is_open = false;
            if(ev == sh_EVLEFTCLICK){
                int x, y;
                sh_input_get_mouse_pos(&x, &y);
                sh_fill_square(x, y, 50);
            }
            if(ev == sh_EVRIGHTCLICK){
                int x, y;
                sh_input_get_mouse_pos(&x, &y);
                sh_fill_square(x, y, 100);
            }
        }

        sh_color_set(0, 0, 0, 255);
        //sh_clear();
        sh_color_set(155, 155, 155, 255);
        sh_write(0, 0, 0, "press q to leave");
        int x, y;
        sh_input_get_mouse_pos(&x, &y);
        sh_plot(x, y);
        if(sh_timer(&timer, 200)){
            ind += dir;
            if(ind == 0 || ind == 4)
                dir *= -1;
        }
        sh_sprite_draw(TEX_SHIP, ind, 200, 200);
        sh_display();
    }
    sh_quit();
}