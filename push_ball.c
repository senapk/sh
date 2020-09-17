#define X_FULL
#include "sh.h"

typedef struct{
    float x, y, radius, ax, ay, vx, vy;//pos, acc, vel
} Ball;

void interact(Ball *a, Ball *b){
    float deformation = (a->radius + b->radius) - x_v2d_distance(a->x, a->y, b->x, b->y);
    if(deformation > 0) {
        X_V2d dif = x_v2d_dot(x_v2d_normalize(x_make_v2d(a->x - b->x, a->y - b->y)), deformation);
        static float K = 0.01;
        float fx = (dif.x) * (dif.x) * K; //elastic force simplified
        float fy = (dif.y) * (dif.y) * K;
        a->ax -= dif.x < 0 ? fx : -fx; //applying force in wright direction
        a->ay -= dif.y < 0 ? fy : -fy;
        b->ax += dif.x < 0 ? fx : -fx; //applying force in wright direction
        b->ay += dif.y < 0 ? fy : -fy;
    }
}
int main(){
    x_open(800, 600, "ball");
    Ball ball = {200, 200, 50, 0, 0, 0, 0};
    Ball player = {0, 0, 30, 0, 0, 0, 0};
    int ev = 0;
    while(x_get_event(&ev)){
        x_delay(10); //framerate control
        int x = x_get_mouse_x();
        int y = x_get_mouse_y();
        player.x = x; player.y = y;
        ball.ax = 0; ball.ay = 0;
        interact(&player, &ball); //accelerate collinding balls
        ball.vx *= 0.9;     ball.vy *= 0.9;     //friction
        ball.vx += ball.ax; ball.vy += ball.ay; //accelerating
        ball.x += ball.vx;  ball.y += ball.vy;  //changing position
        if(ball.x > 800) ball.x -= 800; //looping screen
        if(ball.x < 0)   ball.x += 800;
        if(ball.y > 600) ball.y -= 600; 
        if(ball.y < 0)   ball.y += 600;
        x_set_color("k"); x_clear();
        x_set_color("y"); x_fill_circle(ball.x, ball.y, ball.radius);
        x_set_color("g"); x_fill_circle(player.x, player.y, player.radius);
        x_display();
    }

    x_close();
}