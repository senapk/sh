#define SH_FULL
#include "sh.h"

int main(){
    sh_init(1000, 600);

    while(sh_input_get() != sh_EVQUIT){

        sh_color_load('k');
        sh_clear();
        /* cada exemplo vai ser apresentado num espaço de 200x200 pixels */
        sh_color_load('g');
        sh_write(30, 30, "Exemplo das funcoes de desenho de formas geometricas");

        sh_color_load('w');
        int x = 10;
        int y = 100;
        sh_write(x, y, "xd_line");
        sh_draw_line(x + 30, y + 30, x + 180, y + 180);

        x += 200;
        sh_write(x, y, "xd_thick_line");
        sh_fill_line(x + 30, y + 30, x + 180, y + 180, 3);

        x += 200;
        sh_write(x, y, "xd_circle");
        sh_draw_circle(x + 100, y + 100, 80);

        x += 200;
        sh_write(x, y, "xd_ellipse");
        sh_draw_ellipse(x + 20, y + 50, x + 180, y + 180);  

        x += 200;
        sh_write(x, y, "xd_bezier");
        sh_draw_bezier(x + 30, y + 30, x + 200, y, x + 100, y + 200);  

        x = 10;
        y += 250;
        sh_write(x, y, "xd_filled_arc");
        sh_fill_arc(x + 100, y + 100, 80, 30, 30, 290);

        x += 200;
        sh_write(x, y, "xd_filled_triangle");
        sh_fill_triangle(x, y + 70, x + 160, y + 30, x + 180, y + 180);  

        x += 200;
        sh_write(x, y, "sh_fill_circle");
        sh_fill_circle(x + 100, y + 100, 80);

        x += 200;
        sh_write(x, y, "xd_filled_ellipse");
        sh_fill_ellipse(x + 20, y + 50, x + 180, y + 180);  

        x += 200;
        sh_write(x, y, "sh_fill_rect");
        sh_fill_rect(x + 30, y + 50, x + 180, y + 180);  

        sh_display();
    }
    sh_quit();
    return 0;
}