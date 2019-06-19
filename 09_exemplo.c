#define X_FULL
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
    x_color_set(x_color_make(alien.r, alien.g, alien.b, 255));
    x_fill_square(alien.x, alien.y, lado);
    x_color_set(X_COLOR_WHITE);
    x_draw_square(alien.x, alien.y, lado);
    x_color_set(X_COLOR_BLACK);
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

int main(void) {
    srand(time(NULL));
    bool is_open = true;
    int lado = 50;

    x_open(800, 600, "bolinhas");

    //int FONT_TELA = x_font_save("script12.ttf", 40);
    
    int SOUND_RING = x_sound_load( "sonic.wav");
    int SOUND_SHOT = x_sound_load("shot.wav");

    int MUSIC_ROCK = x_music_load("rock.ogg");
    x_music_toggle_play(MUSIC_ROCK);

    int qtd = 10;

    double angle = 0.0;
    const float grav = 0.1;
    int timer = 0;
    int timer_hit = 0;

    //int TEX_NAVE = x_sprite_load("ship.bmp", 1, 1, lado, lado);
    int TEX_FUNDO = x_sprite_load("background.bmp", 1, 1, x_window_width, x_window_height);
    int TEX_EXPLOSION = x_sprite_load("explosion.bmp", 5, 5, 2 * lado, 2 * lado);
    int TEX_DANCE = x_sprite_load("dancing.bmp", 10, 8, 2 * lado, 2 * lado);
    int TEX_SHIPS = x_sprite_load("ships.bmp", 2, 5, lado, lado);
    Ponto aliens[qtd];

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

    SDL_Event evento;
    int x = 0;
    int y = 0;
    while (is_open) {
        if(!x_timer(&timer, 10))
            continue;

        x_color_set(x_color_make(50, 50, 50, 255));
        x_clear();
        x_color_set(x_color_make(255, 0, 0, 255));
        
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT)
                is_open = false;
            else if(evento.type == SDL_KEYDOWN){
                if(evento.key.keysym.sym == 'e')
                    x_sound_play(SOUND_SHOT, 0);
            }
            else if(evento.type == SDL_MOUSEMOTION){
                x = evento.motion.x - lado / 2;
                y = evento.motion.y - lado / 2;
            }
            else if(evento.type == SDL_MOUSEBUTTONDOWN){
                if(evento.button.button == SDL_BUTTON_LEFT){
                    static int time_shot = 0;
                    if(x_timer(&time_shot, 200)){
                        x_sound_play(SOUND_SHOT, 0);
                    }
                }
            }
        }


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
            float dist = y_xy_distance(x, y, alien[i].x, alien[i].y);
            if(dist < lado){
                if(x_timer(&timer_hit, 500)){
                    aliens[i].cont += 1;
                    x_sound_play(SOUND_RING, 0);
                }
            }
        }
        
        static int exp_ind = 0;
        static int timer_exp = 0;
        if(x_timer(&timer_exp, 100))
            exp_ind += 1;

        static int dance_ind = 48;
        static int timer_dance = 0;
        if(x_timer(&timer_dance, 98)){
            dance_ind += 1;
             if(dance_ind == 64)
                dance_ind = 48; 
        }

        static int ship_ind = 0;
        static int timer_ship = 0;
        if(x_timer(&timer_ship, 200))
            ship_ind += 1;

        x_sprite_draw(TEX_FUNDO, 0, 0, 0);
        x_sprite_draw(TEX_EXPLOSION, exp_ind, 0, 0);
        x_sprite_draw(TEX_DANCE, dance_ind, 300, 300);
        for(int i = 0 ; i < qtd; i++)
            show_square(aliens[i], lado);       
        x_sprite_draw_rot(TEX_SHIPS, ship_ind, x, y, angle, SDL_FLIP_NONE);
        x_write(10, 10, "ola mundo");
        x_display();
    }
    x_close();
    return 0;
}
