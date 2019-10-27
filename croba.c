#define X_FULL
#include "sh.h"

const int LADO = 50;
int NL = 12;
int NC = 16;

typedef struct{
    int x, y;
} XY;

typedef struct{
    XY pos;
    char cor;
} Bloco;

Bloco gerar_bloco_aleat(){
    const char * cores = "rgbymcov";
    Bloco bloco = {{rand() % NC, rand() % NL}, cores[rand() % strlen(cores)]};
    return bloco;
}

typedef struct{
    Bloco corpo[100];
    int size;
    int dir;
} Cobra;

Cobra gerar_cobra(){
    Cobra cobra;
    cobra.corpo[0] = gerar_bloco_aleat();
    cobra.dir = rand() % 4;
    cobra.size = 1;
    return cobra;
}

//                0   , 1 , 2    , 3
//                LEFT, UP, RIGHT, DOWN
X_V2d vet_dir[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

void draw_square(Bloco bloco){
    x_get_palette(bloco.cor);
    XY pos = bloco.pos;
    pos.x *= LADO;
    pos.y *= LADO;
    for(int i = 0; i < LADO; i++)
        x_draw_line(pos.x, pos.y + i, pos.x + LADO - 1, pos.y + i);
}

void dar_a_volta(XY * pos){
    if(pos->x == NC)
        pos->x = 0;
    if(pos->y == NL)
        pos->y = 0;
    if(pos->x == -1)
        pos->x = NC - 1;
    if(pos->y == -1)
        pos->y = NL - 1;
}



int main(){
    int speed = 300;
    x_open(NC * LADO, NL * LADO, "croba");
    int pontos = 0;
    puts("oi");
    Cobra cobra = gerar_cobra();
    Bloco food = gerar_bloco_aleat();
    x_set_font_size(18);
    int timer = 0;
    bool is_open = true;
    int c;
    while(is_open){
        puts("tim");
        while(x_poll_event(&c)){
            if(c == X_EVENT_QUIT){
                is_open = false;
            }else if(c == SDLK_RIGHT){
                cobra.dir = 2;
            }else if(c == SDLK_LEFT){
                cobra.dir = 0;
            }else if(c == SDLK_UP){
                cobra.dir = 1;
            }else if(c == SDLK_DOWN){
                cobra.dir = 3;
            }
        }
        /*
        if(x_timer(&timer, speed)){
            for(int i = cobra.size - 1; i >= 1; i--)
                cobra.corpo[i].pos = cobra.corpo[i - 1].pos;
            cobra.corpo[0].pos.x += vet_dir[cobra.dir].x;
            cobra.corpo[0].pos.y += vet_dir[cobra.dir].y;
        }

        for(int i = 0; i < cobra.size; i++)
            dar_a_volta(&cobra.corpo[i].pos);

        if(cobra.corpo[0].pos.x == food.pos.x && cobra.corpo[0].pos.y == food.pos.y){
            cobra.corpo[cobra.size] = food;
            cobra.size += 1;
            food = gerar_bloco_aleat();
            pontos += 1;
            speed *= 0.9;
        }
        */

        x_set_color(x_get_palette('b'));
        x_clear();
        x_set_color(x_get_palette('w'));
        //for(int i = 0; i < cobra.size; i++)
        //    draw_square(cobra.corpo[i]);
        //draw_square(food);
        x_write(0, 0, "pontos");
        x_display();
    }
    x_close();
}