#define X_FULL
#define X_AUTO
#include "sh.h"

int sprite_pickachu;
int sprite_explosao;
int x = 100;
int y = 300;
int lado = 100;
int timer = 0;
int ind_explosao = 0;
float xe = 100;
float ye = 300;
float vxe = 0;
float vye = 0;

void setup(){
    x_open(800, 600, "pickachu");
    sprite_pickachu = x_load_sprite("pickachu.bmp", 1, 1, lado, lado);
    sprite_explosao = x_load_sprite("explosion.bmp", 5, 5, lado, lado);
}
void handle(int key){
    if(key == X_KEY_RIGHT)
        x += lado;
    if(key == X_KEY_LEFT)
        x -= lado;
    if(key == X_KEY_UP)
        y -= lado;
    if(key == X_KEY_DOWN)
        y += lado;
    if(key == X_EVENT_LEFTCLICK){
        xe = x;
        ye = y;
        int xm = x_get_mouse_x();
        int ym = x_get_mouse_y();
        vxe = - x + xm;
        vye = - y + ym;
        X_V2d xy = x_v2d_normalize(x_make_v2d(vxe, vye));
        vxe = xy.x;
        vye = xy.y;
    }
    
}
void update(){
    xe += vxe;
    ye += vye;

    x_clear();

    x_write(0, 0, "use as teclas ou clique em algum lugar");
    x_draw_sprite(sprite_pickachu, 0, x, y);
    if(x_time_elapsed(&timer, 25))
        ind_explosao += 1;
    x_draw_sprite(sprite_explosao, ind_explosao, xe, ye);
    
}