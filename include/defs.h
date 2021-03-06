/*
Copyright (c) 2017 Devin Kyser

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* This file provides shared defintions for all the other files. */

#ifndef DEFS_H
#define DEFS_H

#include <API.h>

/* Configuration. */
#define FIRE_REL_BTN    8, JOY_DOWN
#define FIRE_LOCK_BTN   8, JOY_RIGHT
#define FAST_MODE_BTN   5, JOY_DOWN
#define ARM_MOVE_BTN    5, JOY_UP
#define ARM_UP_BTN      6, JOY_UP
#define ARM_DOWN_BTN    6, JOY_DOWN
#define LIM_SWTCH       12
#define TURN_AXIS       1
#define FWD_AXIS        3
#define LEFT_MOT        2
#define RIGHT_MOT       3
#define FIRE_SERVO      4
#define ARM_MOT         5
#define DEADZONE        20
#define BTN_DELAY       250

/* Typedefs for convenience. */
typedef bool            b8;
typedef unsigned char   u8;
typedef signed char     i8;
typedef unsigned short  u16;
typedef signed short    i16;
typedef unsigned long   u32;
typedef signed long     i32;
typedef float           f32;

/* Declarations for PROS's main functions
(we only actually define one of these). */
void autonomous();
void initializeIO();
void initialize();
void operatorControl();

/* Declarations for our misc. functions */
i8 get_axis(u8 axis);
i8 safe_add_i8(i8 a, i8 b);

/* Declaration for the function that our button system provides. */
void register_button(u8 buttonGroup, u8 button, void (*function)());

#endif
