#define X_FULL
#define X_AUTO //you need write setup, handle e draw only
#include "sh.h"

typedef struct{
    float x;
    float y;
    float vx;
    float vy;
    int cont;
    int r; //red
    int g; //green
    int b; //blue
} Ponto;


void show_square(Ponto alien, int lado){
    x_set_color_rgba(alien.r, alien.g, alien.b, 255);
    x_fill_square(alien.x, alien.y, lado);
    x_set_color("white");
    x_draw_square(alien.x, alien.y, lado);
    x_set_color("k");
    x_write(alien.x + lado/2, alien.y + lado/2, "%d", alien.cont);
}


void quicar_dentro(Ponto * alien, int lado){
    if(alien->y + lado > x_window_height){
        alien->y = x_window_height - lado - 1;
        alien->vy *= -0.9;
    }
    if(alien->x < 0){
        alien->x = 0;
        alien->vx *= -1;
    }
    if(alien->y < 0){
        alien->y = 0;
        alien->vy *= -1;
    }
    if(alien->x + lado > x_window_width){
        alien->x = x_window_width - lado;
        alien->vx *= -1;        
    }
}


int lado = 50;
int SOUND_RING;
int SOUND_SHOT;
int MUSIC_ROCK;
#define qtd  10

double angle = 0.0;
const float grav = 0.1;
int timer = 0;
int timer_hit = 0;


int TEX_FUNDO;
int TEX_EXPLOSION;
int TEX_DANCE;
int TEX_SHIPS;
Ponto aliens[qtd];

int x = 0;
int y = 0;


void setup(){
    srand(time(NULL));
    x_open(800, 600, "bolinhas");
    SOUND_RING = x_load_sound( "sonic.wav");
    SOUND_SHOT = x_load_sound("shot.wav");
    MUSIC_ROCK = x_load_music("rock.ogg");
    x_play_music_toggle(MUSIC_ROCK);

    angle = 0.0;
    timer = 0;
    timer_hit = 0;
    TEX_FUNDO = x_load_sprite("background.bmp", 1, 1, x_window_width, x_window_height);
    TEX_EXPLOSION = x_load_sprite("explosion.bmp", 5, 5, 2 * lado, 2 * lado);
    TEX_DANCE = x_load_sprite("dancing.bmp", 10, 8, 2 * lado, 2 * lado);
    TEX_SHIPS = x_load_sprite("ships.bmp", 2, 5, lado, lado);

    for(int i = 0; i < qtd; i++){
        aliens[i].x = rand() % (x_window_width - lado);
        aliens[i].y = rand() % (x_window_height - lado);
        aliens[i].vx = (rand() % 11) - 5;
        aliens[i].vy = (rand() % 11) - 5;
        aliens[i].r = rand() % 256;
        aliens[i].g = rand() % 256;
        aliens[i].b = rand() % 256;
        aliens[i].cont = 0;
    }
}

void handle(int event){
    if(event == X_KEY_RIGHT){
        x_play_sound(SOUND_SHOT, 0);
    }
    else if(event == X_EVENT_LEFTCLICK){
        static int time_shot = 0;
        if(x_time_elapsed(&time_shot, 200)){
            x_play_sound(SOUND_SHOT, 0);
        }
    }
}

void update(){
    x = x_get_mouse_x() - lado/2;
    y = x_get_mouse_y() - lado/2;
    float forca = 0;
    if(x_is_key_pressed('w'))
        forca = -2 * grav;
    if(x_is_key_pressed('a'))
        angle -= 3;
    if(x_is_key_pressed('d'))
        angle += 3;

    for(int i = 0 ; i < qtd; i++){ 
        aliens[i].vy += grav + forca;
        aliens[i].x += aliens[i].vx;
        aliens[i].y += aliens[i].vy;
    }
    
    for(int i = 0 ; i < qtd; i++)
        quicar_dentro(&aliens[i], lado);

    for(int i = 0 ; i < qtd; i++){
        float dist = x_v2d_distance(x, y, aliens[i].x, aliens[i].y);
        if(dist < lado){
            if(x_time_elapsed(&timer_hit, 500)){
                aliens[i].cont += 1;
                x_play_sound(SOUND_RING, 0);
            }
        }
    }
    
    static int exp_ind = 0;
    static int timer_exp = 0;
    if(x_time_elapsed(&timer_exp, 100))
        exp_ind += 1;

    static int dance_ind = 48;
    static int timer_dance = 0;
    if(x_time_elapsed(&timer_dance, 98)){
        dance_ind += 1;
            if(dance_ind == 64)
            dance_ind = 48; 
    }

    static int ship_ind = 0;
    static int timer_ship = 0;
    if(x_time_elapsed(&timer_ship, 200))
        ship_ind += 1;

    x_draw_sprite(TEX_FUNDO, 0, 0, 0);
    x_draw_sprite(TEX_EXPLOSION, exp_ind, 0, 0);
    x_draw_sprite(TEX_DANCE, dance_ind, 300, 300);
    for(int i = 0 ; i < qtd; i++)
        show_square(aliens[i], lado);       
    x_draw_sprite_rot(TEX_SHIPS, ship_ind, x, y, angle, SDL_FLIP_NONE);
    x_write(10, 10, "use as teclas as para alterar a gravidade e nao deixe");
    x_write(10, 30, "as pecas tocarem a nave");
}
