#ifndef __MYRO_H__
#define __MYRO_H__

//This header defines general robot opitions, as well as the construction,
//of a global robot variable. The global robot is created upon calling
//connect and destroyed upon calling disconnect.

#include <Scribbler.h>


extern Scribbler robot;

/// Connect the global robot
void connect();
/// Disconnect the global robot
void disconnect();

/** 
 * Like sleep, but takes an argument of seconds, 
 * and can take a fraction of seconds.
 *
 * @param time The number of seconds to wait
 */
void wait(double time);

/**
 * Returns true until start_time ammount of time has passed.
 * 
 * For use in loops that you would like to run for longer then a certain number
 * of minutes.
 */
bool timeRemaining(double start_time);


#endif // __MYRO_H__
