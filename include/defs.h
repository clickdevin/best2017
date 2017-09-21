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

#ifndef DEFS_H
#define DEFS_H

#include <API.h>

#define FIRE_BTN        5, JOY_DOWN
#define SLOW_MODE_BTN   6, JOY_DOWN
#define ARM_UP_BTN      6, JOY_UP
#define ARM_DOWN_BTN    5, JOY_UP
#define TURN_AXIS       1
#define FWD_AXIS        3
#define LEFT_MOT        2
#define RIGHT_MOT       3
#define FIRE_MOT_1      4
#define FIRE_MOT_2      5
#define ARM_SERVO_1     7
#define ARM_SERVO_2     8
#define DEADZONE        20
#define BTN_DELAY       250

typedef bool            b8;
typedef unsigned char   u8;
typedef signed char     i8;
typedef unsigned short  u16;
typedef signed short    i16;
typedef unsigned long   u32;
typedef signed long     i32;
typedef float           f32;

void autonomous();
void initializeIO();
void initialize();
void operatorControl();

i8 get_axis(u8 axis);
i8 safe_add_i8(i8 a, i8 b);

void register_button(u8 buttonGroup, u8 button, void (*function)());

#endif
