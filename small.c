#define X_FULL
#include "sh.h"



typedef struct {
    int x, y;
} XY;

//left, up, right, down, stop
XY vdesl[] = {{-1, 0}, {0, -1}, {1, 0}, {0, +1}, {0, 0}};

int main(){
    x_open(800, 600, "small");
    int FONT_SCRIPT = x_font_load("script12.ttf");
    int FONT_PIXEL = x_font_load("pixel.ttf");
    int x = 100, y = 100, dir = 2;
    int ev;
    int cont = 0;
    while(x_has_events(&ev)){
        x_delay(20);
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

        x += 3 * vdesl[dir].x;
        y += 3 * vdesl[dir].y;

        x_color_change('k'); x_clear();
        x_font_set_size(20);
        x_font_set(0);
        x_font_set(FONT_SCRIPT);
        x_color_change('w'); x_write(0, 30, "control the SQUARE using directional keys");
        
        x_color_change('y'); x_fill_arc(x, y, 50, 40, 0, 360);
        x_color_change('r'); x_fill_arc(x, y, 50, 30, 270, 140);
        x_font_set_size(50);
        x_font_set(FONT_SCRIPT);
        x_color_change('w'); x_write(0, 140, "control the square using directional keys");

        cont += 5;
        x_plot(100, 100);
        x_display();
    }
    
    x_close();
}