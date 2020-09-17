#define X_FULL
#define X_AUTO
#include "sh.h"

void show_mat(int nl, int nc, char mat[nl][nc]){
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++)
        for(c = 0; c < nc; c++){
            char color[2] = {mat[l][c], '\0'};
            x_set_color(color);
            x_grid_square(l, c);
            color[0] = colors[(c + l) % strlen(colors)];
            x_set_color(color);
            x_grid_circle(l, c);
            x_set_color("k");
            if(rand() % 2 == 0){
                char number[10];
                sprintf(number, "%d", rand() % 500 - 250);
                x_grid_text(l, c, number);
            }else{
                char str[] = "abcdef";
                str[rand() % 5 + 1] = '\0';
                x_grid_text(l, c, str);
            }
        }
}

#define nl 7
#define nc 9
#define side  99
char mat[nl][nc];
int MUSIC_ROCK;

void setup(){
    x_open(nc * side + 1, nl * side + 1, "grid");
    x_grid_init(side, 1);
    MUSIC_ROCK = x_load_music("rock.ogg");
    x_play_music_toggle(MUSIC_ROCK);
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++)
        for(c = 0; c < nc; c++)
            mat[l][c] = colors[rand() % strlen(colors)];
}
void handle(int event){
    (void) event;
}

void update(){
    x_delay(200);
    x_clear();
    show_mat(nl, nc, mat);
}
