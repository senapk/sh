#define X_FULL
#include "sh.h"


/* void      x_color_set(r, g, b)
void      x_color_change(char)
SDL_Color x_color_get()

void      x_palette_set(char, r, g, b, a)   save
SDL_Color x_color_get(char)                 load, combina com os loads que retornam indices
 */

typedef struct {
    int x, y;
} XY;

//left, up, right, down, stop
XY vdesl[] = {{-1, 0}, {0, -1}, {1, 0}, {0, +1}, {0, 0}};

int main(){
    x_open(800, 600, "small");
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
        x_color_change('w'); x_write(0, 0, "control the square using directional keys");
        x_color_change('y'); x_fill_arc(x, y, 50, 40, 0, 360);
        x_color_change('r'); x_fill_arc(x, y, 50, 30, 270, 140);

        cont += 5;
        x_plot(100, 100);
        x_display();
    }
    
    x_close();
}