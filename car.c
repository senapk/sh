#define X_FULL
#define X_AUTO
#include "sh.h"
#include <math.h>
#define deg2rad(ang) ((ang) * (3.14159265358979323846/180.0)) 

typedef struct{
    float x, y, vel, acc, angle;//pos, acc, vel
} Car;

int img_car;
int img_fundo;
int sound_shot;
Car player;

void setup(){
    x_open(1200, 700, "player");
    img_car = x_load_sprite("car.bmp", 1, 1, 830/5, 370/5);
    img_fundo = x_load_sprite("autodromo.bmp", 1, 1, x_window_width, x_window_height);
    sound_shot = x_load_sound("shot.wav");
    player = (Car) {200, 200, 0, 0, 90};
}

void handle(int event){
    if(event == X_KEY_SPACE)
        x_play_sound(sound_shot, 0);
}

void update(){
    player.acc = 0;
    if(x_is_key_pressed(SDLK_UP)) player.acc += 0.3;
    if(x_is_key_pressed(SDLK_LEFT))  {if(player.vel > 0.3) player.angle += 3;}
    if(x_is_key_pressed(SDLK_RIGHT)) {if(player.vel > 0.3) player.angle -= 3;}
    if(x_is_key_pressed(SDLK_DOWN)) player.acc -= 0.4;
    player.acc -= 0.1; //friction
    player.vel += player.acc;
    if(player.vel < 0) player.vel = 0;
    player.x += player.vel * cos(x_math_deg2rad(player.angle));
    player.y -= player.vel * sin(x_math_deg2rad(player.angle));
    x_clear();
    x_draw_sprite(img_fundo, 0, 0, 0);
    x_write(10, 10, "Use os direcionais para mover o carro, acelerar ,freiar");
    x_write(10, 30, "Use a tecla espaco para espocar");
    x_draw_sprite_rot(img_car, 0, player.x, player.y, player.angle, SDL_FLIP_NONE);
}
