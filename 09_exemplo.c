#define SH_FULL
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
    sh_color_set(alien.r, alien.g, alien.b, 255);
    sh_fill_square(alien.x, alien.y, lado);
    sh_color_set(255, 255, 255, 255);
    sh_draw_square(alien.x, alien.y, lado);
    sh_color_set(155, 0, 0, 255);
    sh_write(alien.x, alien.y, "%d", alien.cont);
}


void quicar_dentro(Ponto * alien, int lado){
    if(alien->y + lado > sh_window_height){
        alien->y = sh_window_height - lado - 1;
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
    if(alien->x + lado > sh_window_width){
        alien->x = sh_window_width - lado;
        alien->vx *= -1;        
    }
}

int main(void) {
    srand(time(NULL));
    bool is_open = true;
    int lado = 50;

    sh_init(800, 600);

    //int FONT_TELA = sh_font_save("script12.ttf", 40);
    
    int SOUND_RING = sh_sound_save( "sonic.wav");
    int SOUND_SHOT = sh_sound_save("shot.wav");

    int MUSIC_ROCK = sh_music_save("rock.ogg");
    sh_music_toggle_play(MUSIC_ROCK);

    int qtd = 10;

    double angle = 0.0;
    const float grav = 0.1;
    int timer = 0;
    int timer_hit = 0;

    //int TEX_NAVE = sh_sprite_save("ship.bmp", 1, 1, lado, lado);
    int TEX_FUNDO = sh_sprite_save("background.bmp", 1, 1, sh_window_width, sh_window_height);
    int TEX_EXPLOSION = sh_sprite_save("explosion.bmp", 5, 5, 2 * lado, 2 * lado);
    int TEX_DANCE = sh_sprite_save("dancing.bmp", 10, 8, 2 * lado, 2 * lado);
    int TEX_SHIPS = sh_sprite_save("ships.bmp", 2, 5, lado, lado);
    Ponto aliens[qtd];

    for(int i = 0; i < qtd; i++){
        aliens[i].x = rand() % (sh_window_width - lado);
        aliens[i].y = rand() % (sh_window_height - lado);
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
        if(!sh_timer(&timer, 10))
            continue;

        sh_color_set(50, 50, 50, 255);
        sh_clear();
        sh_color_set(255, 0, 0, 255);
        
        while(SDL_PollEvent(&evento)){
            if(evento.type == SDL_QUIT)
                is_open = false;
            else if(evento.type == SDL_KEYDOWN){
                if(evento.key.keysym.sym == 'e')
                    sh_sound_play(SOUND_SHOT, 0);
            }
            else if(evento.type == SDL_MOUSEMOTION){
                x = evento.motion.x - lado / 2;
                y = evento.motion.y - lado / 2;
            }
            else if(evento.type == SDL_MOUSEBUTTONDOWN){
                if(evento.button.button == SDL_BUTTON_LEFT){
                    static int time_shot = 0;
                    if(sh_timer(&time_shot, 200)){
                        sh_sound_play(SOUND_SHOT, 0);
                    }
                }
            }
        }


        float forca = 0;
        if(sh_input_is_key_pressed('w'))
            forca = -2 * grav;
        if(sh_input_is_key_pressed('a'))
            angle -= 3;
        if(sh_input_is_key_pressed('d'))
            angle += 3;

        for(int i = 0 ; i < qtd; i++){
            aliens[i].vy += grav + forca;
            aliens[i].x += aliens[i].vx;
            aliens[i].y += aliens[i].vy;
        }
        
        for(int i = 0 ; i < qtd; i++)
            quicar_dentro(&aliens[i], lado);

        for(int i = 0 ; i < qtd; i++){
            float dist = sqrt((aliens[i].x - x) * (aliens[i].x - x) + (aliens[i].y - y) * (aliens[i].y - y));
            if(dist < lado){
                if(sh_timer(&timer_hit, 500)){
                    aliens[i].cont += 1;
                    sh_sound_play(SOUND_RING, 0);
                }
            }
        }
        
        static int exp_ind = 0;
        static int timer_exp = 0;
        if(sh_timer(&timer_exp, 100))
            exp_ind += 1;

        static int dance_ind = 48;
        static int timer_dance = 0;
        if(sh_timer(&timer_dance, 98)){
            dance_ind += 1;
             if(dance_ind == 64)
                dance_ind = 48; 
        }

        static int ship_ind = 0;
        static int timer_ship = 0;
        if(sh_timer(&timer_ship, 200))
            ship_ind += 1;

        sh_sprite_draw(TEX_FUNDO, 0, 0, 0);
        sh_sprite_draw(TEX_EXPLOSION, exp_ind, 0, 0);
        sh_sprite_draw(TEX_DANCE, dance_ind, 300, 300);
        for(int i = 0 ; i < qtd; i++)
            show_square(aliens[i], lado);       
        sh_sprite_draw_rot(TEX_SHIPS, ship_ind, x, y, angle, SDL_FLIP_NONE);
        //sh_font_load(FONT_TELA);
        sh_write(10, 10, "ola mundo");
        //sh_font_load(0);
        sh_display();
    }
    sh_quit();
    return 0;
}
