#include <Graphics.h>
#include <MyroInternals.h>
#include <iostream>
#include <assert.h>
#include <cmath>

static unsigned char red[] = {255,0,0};

static inline void debug_rectangle(myro_img& img, int x, int y){
    img.draw_rectangle(x-2,y-2,x+2,y+2, red);
}

template <typename T>
static void swap(T& one, T& two){
    T temp;
    temp = one;
    one = two;
    two = temp;
}

int FindColor(const char *name, Color *colorPtr);

Color color_rgb(unsigned char r, unsigned char g, unsigned char b){
    Color c;
    c.R = r;
    c.G = g;
    c.B = b;
    return c;
}

Color string_to_color(std::string color){
    Color f;
    FindColor(color.c_str(), &f);
    return f;
}

// ====================
// GraphWin
// ====================
GraphWin::GraphWin(std::string title, int width, int height)
: title(title),
  background(width,height,1,3),
  result(width,height,1,3),
  width(width),
  height(height)
{
    background.fill(255);
    result.fill(255);
    init();
    redraw();
}

GraphWin::GraphWin(std::string title, myro_img* img)
: title(title),
  background(*img),
  result(*img),
  width(width),
  height(height)
{
    init();
    redraw();
} 

GraphWin::GraphWin(std::string title, myro_img& img)
: title(title),
  background(img),
  result(img),
  width(width),
  height(height)
{
    init();
    redraw();
} 

GraphWin::~GraphWin(){
    if (thread){
        thread->stop();
        delete thread;
    }
}

void GraphWin::init(){
    thread = new CImg_display(result, title.c_str());
    thread->start();
}

void GraphWin::plot(int x, int y, Color color){
}

void GraphWin::plotPixel(int x, int y, Color color){
}

void GraphWin::setBackground(Color color){
    if ( background.spectrum() == 1 )
        background.assign(width,height,1,3);
    cimg_forXY(background,x,y){
        background(x,y,0,0) = color.R;
        background(x,y,0,1) = color.G;
        background(x,y,0,2) = color.B;
    }
}
void GraphWin::setBackground(std::string color){
    Color c = string_to_color(color);
    this->setBackground(c);
}

void GraphWin::setBackground(Picture* img){
}

void GraphWin::close(){
    if ( thread ) {
        thread->stop();
        delete thread;
        thread = NULL;
    }
}

void GraphWin::waitWinClosed(){
    if ( this->thread ){
        thread->join();
        delete thread;
        thread = NULL;
    }
}

/*
Point GraphWin::getMouse(){
}

Point GraphWin::checkMouse(){
}
*/

void GraphWin::setCoords(int xll, int yll, int xur, int yur){
}

GOL_reg GraphWin::draw(GraphicsObject* obj){
    drawlist.push_back(obj);
    GOL_reg registration = --drawlist.end();
    this->redraw();
    return registration;
}

void GraphWin::undraw(GOL_reg reg){
    drawlist.erase(reg);
}

void GraphWin::redraw(){
    // Copy Background to result
    if ( background.spectrum() == 1 ){
        cimg_forXY(background,x,y){
            result(x,y,0,0) = background(x,y,0,0);
            result(x,y,0,1) = background(x,y,0,0);
            result(x,y,0,2) = background(x,y,0,0);
        }
    }else {
        result = background;
    }
    for(GOL_reg it = drawlist.begin(); it != drawlist.end(); it++)
        (*it)->draw_command(result);

    thread->change_image(result);
}

// ====================
// GraphicsObject
// ====================
GraphicsObject::GraphicsObject()
: canvas(NULL),
  fill(color_rgb(255,255,255)),
  outline(color_rgb(0,0,0)),
  width(1)
{}

GraphicsObject::GraphicsObject(Color fill, Color outline, int width)
: canvas(NULL),
  fill(fill),
  outline(outline),
  width(width)
{}

void GraphicsObject::setFill(Color color){
    fill=color;
    if ( this->canvas )
        this->canvas->redraw();
}

void GraphicsObject::setFill(std::string color){
    Color c = string_to_color(color);
    this->setFill(c);
}

void GraphicsObject::setOutline(Color color){
    outline=color;
    if ( this->canvas )
        this->canvas->redraw();
}

void GraphicsObject::setOutline(std::string color){
    Color c = string_to_color(color);
    this->setOutline(c);
}

void GraphicsObject::setWidth(int width){
    this->width = width;
}

void GraphicsObject::draw(GraphWin* canvas){
    if ( !this->canvas ){
        this->canvas = canvas;
        this->registration = this->canvas->draw(this);
        assert( *registration == this );
    }
    else {
        // Throw an exception or something
    }
}

void GraphicsObject::draw(GraphWin& canvas){
    this->draw(&canvas);
}

void GraphicsObject::undraw(){
    if ( this->canvas ){
        this->canvas->undraw(this->registration);
        canvas = NULL;
    }
    else{
        // Throw an exception
    }
}

// ====================
// Point
// ====================
Point::Point(): x(0),y(0){}
Point::Point(int x, int y)
: x(x), y(y)
{}
/*
Point::Point(const Point& p){
    this->x = p.x;
    this->y = p.y;
}
*/
Point* Point::clone(){ return new Point(x,y); }
int Point::getX(){ return x; }
int Point::getY(){ return y; }
void Point::move(int dx, int dy){
    x += dx;
    y += dy;
    if ( this->canvas )
        this->canvas->redraw();
}
Point& Point::operator+=(const Point& rhs){
    x += rhs.x;
    y += rhs.y;
    return *this;
}
Point Point::operator+(const Point& other){
    Point result = *this;
    result += other;
    return result;
}
void Point::draw_command(myro_img& canvas){
    canvas(x,y,0,0) = outline.R;
    canvas(x,y,0,1) = outline.G;
    canvas(x,y,0,2) = outline.B;
}

// ====================
// _BBox
// ====================
_BBox::_BBox(Point p1, Point p2)
: p1(p1), p2(p2)
{}

void _BBox::move(int dx, int dy){
    Point d(dx,dy);
    this->p1 += d;
    this->p2 += d;
    if ( this->canvas ) 
        this->canvas->redraw();
}

Point _BBox::getP1(){ return p1; };
Point _BBox::getP2(){ return p2; };
Point _BBox::getCenter(){ 
    return Point((p1.getX()+p2.getX())/2, 
                 (p1.getY()+p2.getY())/2);
}

// ====================
// Oval
// ====================
Oval::Oval(Point p1, Point p2)
: _BBox(p1,p2)
{
}

Oval* Oval::clone(){
    return new Oval(this->p1, this->p2);
}

void Oval::draw_command(myro_img& canvas){
    Point center = this->getCenter();
    unsigned char color[] = {fill.R, fill.G, fill.B};
    unsigned char outlinecolor[] = {outline.R, outline.G, outline.B};
    int r0 = abs(center.getX() - this->getP2().getX());
    int r1 = abs(center.getY() - this->getP2().getY());
    if ( this->width ){
        canvas.draw_ellipse(center.getX(),center.getY(), r0, r1, 0, outlinecolor);
        canvas.draw_ellipse(center.getX(), center.getY(), r0-width, r1-width, 0, color);
    }
    else
        canvas.draw_ellipse(center.getX(),center.getY(), r0, r1, 0, color);
}

// ====================
// Circle
// ====================
Circle::Circle(Point center, int radius)
: Oval(Point(center.getX()-radius,center.getY()-radius),Point(center.getX()+radius,center.getY()+radius)), 
  centerPoint(center),
  radius(radius)
{}

int Circle::getRadius(){
    return radius;
}
/*
void Circle::draw_command(myro_img& canvas){

}
*/

// ====================
// Rectangle
// ====================
Rectangle::Rectangle(Point p1, Point p2)
: _BBox(p1,p2)
{}

void Rectangle::draw_command(myro_img& canvas){
    unsigned char color[] = {fill.R, fill.G, fill.B};
    if ( this->width ){
        unsigned char outlinecolor[] = {outline.R, outline.G, outline.B};
        int leftx = std::min(p1.getX(),p2.getX())+width;;
        int rightx = std::max(p1.getX(), p2.getX())-width;
        int topy = std::min(p1.getY(), p2.getY())+width;
        int bottomy = std::max(p1.getY(), p2.getY())-width;
        canvas.draw_rectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), outlinecolor);
        canvas.draw_rectangle(leftx,topy,rightx,bottomy, color);
    }
    else{
        canvas.draw_rectangle(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
    }
}

// ====================
// Line
// ====================
Line::Line(Point p1, Point p2)
: _BBox(p1,p2),
  arrow_type("none")
{}

void Line::setArrow(std::string type){
    if ( type == "first" ||
         type == "last"  ||
         type == "both"  ||
         type == "none" )
        this->arrow_type = type;
    else{
        std::cerr << "Line::setArrow(): Bad Type: " << type << std::endl;
        // TODO: Throw Exception
    }
}

void Line::draw_command(myro_img& canvas){
    unsigned char color[] = {outline.R, outline.G, outline.B};
    //std::cerr<< "color.R: " << (int)color[0] << "color.G: " << (int)color[1] << "color.B: " << (int)color[2] << std::endl;
    if ( arrow_type == "first" ){
        canvas.draw_arrow(p2.getX(), p2.getY(), p1.getX(), p1.getY(), color);
    }
    else if ( arrow_type == "last" ){
        canvas.draw_arrow(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
    }
    else if ( arrow_type == "both" ){
        canvas.draw_arrow(p2.getX(), p2.getY(), p1.getX(), p1.getY(), color);
        canvas.draw_arrow(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
    }
    if ( this->width > 1 ){
        int x0=p1.getX(),x1=p2.getX(),y0=p1.getY(),y1=p2.getY();
        bool steep = abs(y0-y1) > abs(x0-x1);
        if ( steep ){
            swap(x0,y0);
            swap(x1,y1);
        }
        if ( x0 > x1 ){
            swap(x0,x1);
            swap(y0,y1);
        }
        int deltax = x1-x0;
        int deltay = abs(y1-y0);
        float error = 0;
        float deltaerr = (float)(deltay) / (deltax);
        int ystep = y0 < y1 ? 1 : -1;
        int y = y0;
        // This is a sort of weird bresenhams thing where I sweep the end
        // points so i can draw a "thick" line
        for (int x = x0; x <= x1; x++){
            if ( steep )
                canvas.draw_circle(y,x,ceil(this->width/2.0),color);
            else
                canvas.draw_circle(x,y,ceil(this->width/2.0),color);
            error += deltaerr;
            if ( error >= 0.5 ){
                y += ystep;
                error -= 1.0;
            }
        }
    }
    else if (this->width == 1){
        canvas.draw_line(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
    }
}

// ====================
// Polygon
// ====================
Polygon::Polygon(std::vector<Point> points)
:  pts(points.size(),2), points(points)
{
}

std::vector<Point> Polygon::getPoints(){
    return points;
}

std::vector<Point> Polygon::update_points(){
    Point l,r,p;
    double theta,a,b,c;
    double alpha, beta, el;
    int i_x, i_y;
    std::vector<Point> ret;
    outline_lines.clear();
    outline_lines.push_back(Line(points[points.size()-1],points[0]));

    for (int i = 0; i < (int)points.size(); i++){
        if (i+1 < (int)points.size())
            outline_lines.push_back(Line(points[i],points[i+1]));
        ret.push_back(points[i]);
        //l = this->points[(i+1)%points.size()];
        p = this->points[i];
        //r = this->points[(i-1)%points.size()];
    /*
        // Law of cosines from wikipedia.
        // Distance of sides of the triangle
        // c - opposite of l
        c = hypot(r.getX()-p.getX(),r.getY()-p.getY());
        std::cout << "c: " << c << std::endl;
        // b - opposite of r
        b = hypot(l.getX()-p.getX(),l.getY()-p.getY());
        std::cout << "b: " << b << std::endl;
        // a - opposite of p
        a = hypot(l.getX()-r.getX(),l.getY()-r.getY());
        std::cout << "a: " << a << std::endl;
        // Angle from line segments from l->r and l->p
        theta = acos((a*a+b*b-(c*c))/(2*a*b));
        std::cout << "theta: " << theta << std::endl;

        // Angle from x-axis to line segment from l->r
        alpha = atan2(l.getY()-r.getY(),l.getX()-r.getX());
        //alpha = atan2(r.getY()-l.getY(),r.getX()-l.getX());

        // TODO: This is probably more calculations that needs to be done!

        // Magnitude of distance fom triangle made of l & p
        el = b * cos(theta);
        std::cerr << "el: " << el << std::endl;
        // i_x, i_y is the point for the third point of the right triangle
        // with l & p
        i_x = l.getX() + el*cos(alpha);
        i_y = l.getY() + el*sin(alpha);
        ret.push_back(Point(i_x,i_y));
        std::cerr << i_x << " " << i_y << std::endl;

        // The direction to the "inside" of the polygon, from p.
        beta = atan2(i_y-p.getY(),i_x-p.getX());

        // x
        pts(i,0,0,0) = (this->width*cos(beta))+p.getX();
        // y
        pts(i,0,0,1) = (this->width*sin(beta))+p.getY();
        */
        /*
        pts_bdr(i,0) = p.getX();
        pts_bdr(i,1) = p.getY();
        */
        pts(i,0) = p.getX();
        pts(i,1) = p.getY();
    }
    for (int i = 0; i < (int)outline_lines.size(); i++)
        outline_lines[i].setWidth(this->width);
    return ret;
}

void Polygon::draw_command(myro_img& canvas){
    unsigned char color[] = {fill.R, fill.G, fill.B};
    unsigned char border[] = {outline.R, outline.G, outline.B};
    
    // TODO: I feel like this is somewhat of an expensive operation O(N) for
    // the number of points, this should probably only be done when the points
    // actually need to be updated when they've changed.
    std::vector<Point> debug = update_points();

    //canvas.draw_polygon(pts_bdr, border, 1, ~0U);
    //canvas.draw_polygon(pts_bdr, border, 1, ~0U);
    //canvas.draw_polygon(pts, color);
    canvas.draw_polygon(pts, color);
    if ( this->width == 1 ){
        canvas.draw_polygon(pts, border, 1, ~0U);
    } else if ( this->width > 1 ){
        for (int i = 0; i < (int)outline_lines.size(); i++)
            outline_lines[i].draw_command(canvas);
    }
    /*
    std::cerr << debug.size() << " debug points" << std::endl;
    for (int i = 0; i < (int)debug.size(); i++){
        canvas.draw_rectangle(debug[i].getX()-2,debug[i].getY()-2,debug[i].getX()+2,debug[i].getY()+2, red);
    }
    */
}

void Polygon::move(int dx, int dy){
    Point d(dx,dy);
    for (int i = 0; i < (int)points.size(); i++){
        points[i] += d;
    }
    if ( this->canvas ) 
        this->canvas->redraw();
}

// ====================
// Text
// ====================
Text::Text(Point anchor, std::string text)
: GraphicsObject(color_rgb(0,0,0), color_rgb(0,0,0), 0),
  text(text),
  font("helvetica"),
  size(13),
  background(false),
  style("normal"),
  anchor(anchor)
{}

std::string Text::getText(){ return text; }
void Text::setText(std::string text){ this->text = text; }
Point Text::getAnchor(){ return anchor; }
void Text::setAnchor(Point anchor){ this->anchor=anchor; }
void Text::setFace(std::string font){
    // TODO
    //Joke's On you because I don't support any font other than the default!
}
void Text::setSize(int size){
    this->size = size;
}

void Text::setStyle(std::string style){
    // TODO: Yeah I don't support this either
}

void Text::setTextColor(Color color){ this->setOutline(color); }
void Text::setTextColor(std::string color){ this->setOutline(color); }

void Text::drawBackground(bool background){
    this->background = background;
}

void Text::draw_command(myro_img& canvas){
    unsigned char background[] = {fill.R, fill.G, fill.B};
    unsigned char text_color[] = {outline.R, outline.G, outline.B};
    if ( this->background ){
        canvas.draw_text(anchor.getX(), anchor.getY(), text.c_str(), 
                         text_color, background, 1, size);
    }
    else{
        canvas.draw_text(anchor.getX(), anchor.getY(), text.c_str(), 
                         text_color, 0, 1, size);
    }
}

void Text::move(int dx, int dy){
    anchor += Point(dx,dy);
    if ( this->canvas ) 
        this->canvas->redraw();
}
