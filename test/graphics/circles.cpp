#include <Myro.h>

static const int num_of_circles = 1000;
static const int width=500;
static const int height=500;
static const int max_circle_radius=50;

int main(){
    GraphWin win("Circles", width,height);
    Circle* c[num_of_circles];
    for (int i = 0; i < num_of_circles; i++){
        int x=rand()%width;
        int y=rand()%height;
        int r=rand()%max_circle_radius;
        int R=rand()%255;
        int G=rand()%255;
        int B=rand()%255;
        c[i] = new Circle(Point(x,y),r);
        c[i]->setFill(color_rgb(R,G,B));
        c[i]->draw(win);
        wait(0.01);
    }
    wait(5);
    win.close();
    win.waitWinClosed();
}
