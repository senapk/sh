#define X_FULL
#define X_EASY
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
    printf("%d %d %c\n", bloco.pos.x, bloco.pos.y, bloco.cor);
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
    char color[] = {bloco.cor, '\0'};
    x_set_color(color);
    XY pos = bloco.pos;
    pos.x *= LADO;
    pos.y *= LADO;
    for(int i = 0; i < LADO; i++)
        x_fill_square(pos.x + 1, pos.y + 1, LADO - 2);
}

void dar_a_volta_bloco(XY * pos){
    if(pos->x == NC)
        pos->x = 0;
    if(pos->y == NL)
        pos->y = 0;
    if(pos->x == -1)
        pos->x = NC - 1;
    if(pos->y == -1)
        pos->y = NL - 1;
}


int speed;
int pontos;
Cobra cobra;
Bloco food;
int timer;

void dar_a_volta(){
    for(int i = 0; i < cobra.size; i++)
        dar_a_volta_bloco(&cobra.corpo[i].pos);
}

void andar_cobra(){
    if(x_time_elapsed(&timer, speed)){
        for(int i = cobra.size - 1; i >= 1; i--)
            cobra.corpo[i].pos = cobra.corpo[i - 1].pos;
        cobra.corpo[0].pos.x += vet_dir[cobra.dir].x;
        cobra.corpo[0].pos.y += vet_dir[cobra.dir].y;
    }
}

void comeu_comida(){
    if(cobra.corpo[0].pos.x == food.pos.x && cobra.corpo[0].pos.y == food.pos.y){
        cobra.corpo[cobra.size] = food;
        cobra.size += 1;
        food = gerar_bloco_aleat();
        pontos += 1;
        speed *= 0.9;
    }
}

void setup(){
    x_open(NC * LADO, NL * LADO, "croba");
    speed = 300;
    pontos = 0;
    cobra = gerar_cobra();
    food = gerar_bloco_aleat();
    x_set_font_size(18);
    timer = 0;
}

void handle(int event){
    if(event == SDLK_RIGHT){
        cobra.dir = 2;
    }else if(event == SDLK_LEFT){
        cobra.dir = 0;
    }else if(event == SDLK_UP){
        cobra.dir = 1;
    }else if(event == SDLK_DOWN){
        cobra.dir = 3;
    }
}

void update(){
    andar_cobra();
    dar_a_volta();
    comeu_comida();

    x_set_color("15, 15, 15");
    x_clear();
    draw_square(food);
    for(int i = 0; i < cobra.size; i++)
        draw_square(cobra.corpo[i]);
    x_set_color("w");
    x_write(0, 0, "pontos %d", pontos);
}
