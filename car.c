#define X_FULL
#include "sh.h"
#include <math.h>
#define deg2rad(ang) ((ang) * (3.14159265358979323846/180.0)) 

typedef struct{
    float x, y, vel, acc, angle;//pos, acc, vel
} Car;
int main(){
    x_open(1200, 700, "player");
    int img_car = x_load_sprite("car.bmp", 1, 1, 830/5, 370/5);
    int img_fundo = x_load_sprite("autodromo.bmp", 1, 1, x_window_width, x_window_height);
    Car player = {200, 200, 0, 0, 90};
    int ev = 0;
    while(x_get_event(&ev)){
        x_delay(20); //framerate control
        player.acc = 0;
        if(x_is_key_pressed(SDLK_UP)) player.acc += 0.3;
        if(x_is_key_pressed(SDLK_LEFT))  {if(player.vel > 0.3) player.angle += 3;}
        if(x_is_key_pressed(SDLK_RIGHT)) {if(player.vel > 0.3) player.angle -= 3;}
        if(x_is_key_pressed(SDLK_DOWN)) player.acc -= 0.4;
        player.acc -= 0.1; //friction
        player.vel += player.acc;
        if(player.vel < 0) player.vel = 0;
        player.x += player.vel * cos(deg2rad(player.angle));
        player.y -= player.vel * sin(deg2rad(player.angle));
        x_clear();
        x_draw_sprite(img_fundo, 0, 0, 0);
        x_write(10, 10, "Use os direcionais para mover o carro, acelerar e freiar");
        x_draw_sprite_rot(img_car, 0, player.x, player.y, player.angle, SDL_FLIP_NONE);
        x_display();
    }

    x_close();
}