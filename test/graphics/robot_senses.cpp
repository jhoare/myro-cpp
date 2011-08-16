#include<Myro.h>
#include<iostream>

using namespace std;

static const int y_spacing = 20;
static const int title_left_x = 20;

static const int win_width = 300;

static const int padding_width = 10;

static const int title_right_x = 80;
static const int two_field_spacing = ( (win_width-padding_width) - title_right_x ) / 2;
static const int three_field_spacing = ( (win_width-padding_width) - title_right_x ) / 3;

static const void draw_label(int level, const char* text, GraphWin& win){
    Text t(Point(title_left_x, y_spacing*level), text);
    t.draw(win);
}

int main(){

    //connect();

    GraphWin win("Senses", win_width, y_spacing*9);
    // Constantly poll the mouse position and draw a circle
    draw_label(1,"Line: ", win);
    Point line_1_l(y_spacing*1, title_right_x);
    Point line_2_l(y_spacing*1, title_right_x+two_field_spacing);
    draw_label(2,"Stall: ", win);
    Point stall_l(y_spacing*2, title_right_x);
    draw_label(3,"Bright: ", win);
    Point bright_1_l(y_spacing*3, title_right_x);
    Point bright_2_l(y_spacing*3, title_right_x+three_field_spacing);
    Point bright_3_l(y_spacing*3, title_right_x+three_field_spacing*2);
    draw_label(4,"Obstacle: ", win);
    Point obstacle_1_l(y_spacing*4, title_right_x);
    Point obstacle_2_l(y_spacing*4, title_right_x+three_field_spacing);
    Point obstacle_3_l(y_spacing*4, title_right_x+three_field_spacing*2);
    draw_label(5,"IR: ", win);
    Point ir_1_l(y_spacing*5, title_right_x);
    Point ir_2_l(y_spacing*5, title_right_x+two_field_spacing);
    draw_label(6,"Light: ", win);
    Point light_1_l(y_spacing*6, title_right_x);
    Point light_2_l(y_spacing*6, title_right_x+three_field_spacing);
    Point light_3_l(y_spacing*6, title_right_x+three_field_spacing*2);
    draw_label(7,"Battery: ", win);
    Point battery_l(y_spacing*7, title_right_x+three_field_spacing*2);

    win.waitWinClosed();
    //disconnect();
    return 0;
}
