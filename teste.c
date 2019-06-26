#define X_FULL
#include "sh.h"

int main(){
    x_open(800, 600, "janela");
    int x = 0, y = 0;
    int x2 = 100, y2 = 100;
    int IMG_PIK = x_load_sprite("pickachu.bmp", 1, 1, 200, 200);
    int IMG_SHIP = x_load_sprite("ships.bmp", 2, 5, 200, 200);
    int TEX_DANCE = x_load_sprite("dancing.bmp", 10, 8, 300, 300);
    int MUSIC_ROCK = x_load_music("rock.ogg");
    x_play_music_toggle(MUSIC_ROCK);
    int ind_ship = 48;
    int timer_ship = 0;
    int delta = 1;
    while(x_get_event(NULL)){
        if(x_timer(&timer_ship, 100)){
            ind_ship += delta;
            if((ind_ship == 56) || (ind_ship == 47))
                delta *= -1;
        }
        x_set_pcolor('k');
        x_clear();
        x_set_pcolor('w');
        x_get_mouse_pos(&x, &y);
        x_draw_sprite(TEX_DANCE, ind_ship, x2, y2);
        x_write(60, 70, "Ola pessoal %d", 50);
        x_draw_bezier(0, 0, 200, 300, x, y);
        x_display();
    }
    x_close();
}