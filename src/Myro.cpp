#include "Myro.h"
#include <sys/time.h>
#include <time.h>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include <cstdlib>

static time_t start_time;
static bool running = false;

Scribbler robot;

void wait(double time) {
	int utime = (int)(time * pow(10,6));
	if(time != 0)
		usleep(utime);
}

bool timeRemaining(double desired_time) {	
	if(!running) {
		running = true;
        start_time = time(NULL);
		return true;
	}

    if ( difftime(time(NULL), start_time) >= desired_time ){
      running = false;
      return false;
    }
    return true;
}

void connect(){
	int status = robot.connect(); 
	if(status < 0) { 
		exit(-1);
	}
    std::cout << "Connected to Robot" << std::endl;
}

void disconnect(){
    robot.stop();
	robot.disconnect();
}
