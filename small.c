#define X_FULL
#define X_AUTO
#include "sh.h"


typedef struct {
    int x, y;
} XY;

//left, up, right, down, stop
XY vdesl[] = {{-1, 0}, {0, -1}, {1, 0}, {0, +1}, {0, 0}};
int FONT_SCRIPT;
int x = 100, y = 100, dir = 2, cont = 0;

void setup(){
    x_open(800, 600, "small");
    FONT_SCRIPT = x_load_font("script12.ttf");
    x = 100, y = 100, dir = 2;
}

void handle(int ev){
    if(ev == SDLK_LEFT)
        dir = 0;
    else if(ev == SDLK_UP)
        dir = 1;
    else if(ev == SDLK_RIGHT)
        dir = 2;
    else if(ev == SDLK_DOWN)
        dir = 3;
    else if(ev == SDLK_SPACE)
        dir = 4;
}

void update(){
        x += 3 * vdesl[dir].x;
        y += 3 * vdesl[dir].y;

        x_set_color("k"); x_clear();
        x_set_font_size(30);
        x_font_set(FONT_SCRIPT);
        x_set_color("w"); x_write(0, 30, "control the ARC using directional keys");
        
        x_set_color("y"); x_fill_arc(x, y, 50, 40, 0, 360);
        x_set_color("r"); x_fill_arc(x, y, 50, 30, 270 + x, 140);

        cont += 5;
        x_plot(100, 100);
}
    
