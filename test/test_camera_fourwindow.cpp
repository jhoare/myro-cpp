#include <Myro.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
//using namespace Magick;
using namespace std;

int main(int argc, char ** argv) {

    connect();

    cout << "Connected to Robot" << endl;
    cout << "Proceeding to test camera" << endl;

    cout << "Testing Color, if image looks correct close display" << endl;
    cout << "If not, try restarting robot, and rerunning test" << endl;

    Picture* color = robot.takePicture("color");
    color->show("Color");
    //delete color;

    cout << "Testing Grayscale" << endl;
    Picture* gray = robot.takePicture("gray");
    gray->show("Gray");
    //delete gray;

    cout << "Testing Jpeg Color" << endl;
    Picture* jpeg = robot.takePicture("jpeg");
    jpeg->show("Color JPEG");
    //delete jpeg;

    cout << "Testing Jpeg Gray" << endl;
    Picture* grayjpeg = robot.takePicture("grayjpeg");
    grayjpeg->show("Gray JPEG");
    //delete grayjpeg;

    cout << "All Camera Test Completed\n";
    cout << "Waiting 10 seconds" << endl;
    wait(10);

    disconnect();

    return 0;
}

