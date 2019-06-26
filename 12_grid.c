#define X_FULL
#include "sh.h"

void show_mat(int nl, int nc, char mat[nl][nc]){
    x_get_palette('w');
    x_clear();
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++)
        for(c = 0; c < nc; c++){
            x_get_palette(mat[l][c]);
            x_grid_square(l, c);
            x_get_palette(colors[(c + l) % strlen(colors)]);
            x_grid_circle(l, c);
            x_get_palette('k');
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

int main(){
    int w = 902, h = 602, side = 100;
    x_open(w, h);
    x_grid_init(side, 1);
    
    int MUSIC_ROCK = x_load_music("rock.ogg");
    x_play_music_toggle(MUSIC_ROCK);

    int nl = h / side, nc = w / side;
    char mat[nl][nc];
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++){
        for(c = 0; c < nc; c++){
            mat[l][c] = colors[rand() % strlen(colors)];
        }
    }
    int timer = 0;
    while(x_get_event() != X_EVENT_QUIT){
        if(x_timer(&timer, 1000)){
            x_clear();
            show_mat(nl, nc, mat);
            x_display();
        }
    }
    x_close();
    return 0;
}