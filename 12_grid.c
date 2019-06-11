#define SH_FULL
#include "sh.h"

void show_mat(int nl, int nc, char mat[nl][nc]){
    sh_color_load('w');
    sh_clear();
    char * colors = "rgbymcov";
    int l, c;
    for(l = 0; l < nl; l++)
        for(c = 0; c < nc; c++){
            sh_color_load(mat[l][c]);
            sh_grid_splot(l, c);
            sh_color_load(colors[(c + l) % strlen(colors)]);
            sh_grid_cplot(l, c);
            sh_color_load('k');
            if(rand() % 2 == 0){
                char number[10];
                sprintf(number, "%d", rand() % 500 - 250);
                sh_grid_tplot(l, c, number);
            }else{
                char str[] = "abcdef";
                str[rand() % 5 + 1] = '\0';
                sh_grid_tplot(l, c, str);
            }
        }
}

int main(){
    int w = 902, h = 602, side = 100;
    sh_init(w, h);
    sh_grid_init(side, 1);
    
    int MUSIC_ROCK = sh_music_save("rock.ogg");
    sh_music_toggle_play(MUSIC_ROCK);

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
    while(sh_input_get() != sh_EVQUIT){
        if(sh_timer(&timer, 1000)){
            sh_clear();
            show_mat(nl, nc, mat);
            sh_display();
        }
    }
    sh_quit();
    return 0;
}