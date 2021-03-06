#define X_FULL
#include "sh.h"

int main(){
    x_open(1000, 600, "desenho");
    x_set_font_size(18);
    while(x_get_event()){
        x_set_color("k");
        x_clear();
        /* cada exemplo vai ser apresentado num espaço de 200x200 pixels */
        x_set_color("g");
        x_write(30, 30, "Exemplo das funcoes de desenho de formas geometricas");

        x_set_color("w");
        int x = 10;
        int y = 100;
        x_write(x, y, "xd_line");
        x_draw_line(x + 30, y + 30, x + 180, y + 180);

        x += 200;
        x_write(x, y, "xd_thick_line");
        x_fill_line(x + 30, y + 30, x + 180, y + 180, 3);

        x += 200;
        x_write(x, y, "xd_circle");
        x_draw_circle(x + 100, y + 100, 80);

        x += 200;
        x_write(x, y, "xd_ellipse");
        x_draw_ellipse(x + 20, y + 50, x + 180, y + 180);  

        x += 200;
        x_write(x, y, "xd_bezier");
        x_draw_bezier(x + 30, y + 30, x + 200, y, x + 100, y + 200);  

        x = 10;
        y += 250;
        x_write(x, y, "xd_filled_arc");
        x_fill_arc(x + 100, y + 100, 80, 30, 30, 290);

        x += 200;
        x_write(x, y, "xd_filled_triangle");
        x_fill_triangle(x, y + 70, x + 160, y + 30, x + 180, y + 180);  

        x += 200;
        x_write(x, y, "x_fill_circle");
        x_fill_circle(x + 100, y + 100, 80);

        x += 200;
        x_write(x, y, "xd_filled_ellipse");
        x_fill_ellipse(x + 20, y + 50, x + 180, y + 180);  

        x += 200;
        x_write(x, y, "x_fill_rect");
        x_fill_rect(x + 30, y + 50, x + 180, y + 180);  

        x_display();
    }
    x_close();
    return 0;
}