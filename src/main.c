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

#include <defs.h>

/* A variable for a toggle switch used later. */
b8 slow_mode = false;

/* These static functions ending in _btn are used
as callbacks for our button-handling system. */

static void fire_btn()
{
    if (motorGet(FIRE_MOT_1) == 127)
    {
        motorSet(FIRE_MOT_1, 0);
        motorSet(FIRE_MOT_2, 0);
    } else {
        motorSet(FIRE_MOT_1, 127);
        motorSet(FIRE_MOT_2, 127);
    }
}

static void slow_mode_btn()
{
    slow_mode = !slow_mode;
}

static void arm_up_btn()
{
    i8 newval = safe_add_i8(motorGet(ARM_SERVO_1), 16);
    motorSet(ARM_SERVO_1, newval);
    motorSet(ARM_SERVO_2, -1 * newval);
}

static void arm_down_btn()
{
    i8 newval = safe_add_i8(motorGet(ARM_SERVO_1), -16);
    motorSet(ARM_SERVO_1, newval);
    motorSet(ARM_SERVO_2, -1 * newval);
}

/* Beginning of the main part of the program */
void operatorControl()
{
    /* We need to assign and manipulate these variables at little later. */
    i8 l_spd;
    i8 r_spd;
    i8 speed_mod;

    /* Make sure the servos are in their initial positions. */
    motorSet(ARM_SERVO_1, -127);
    motorSet(ARM_SERVO_2, 127);

    /* Register the static functions above to our button system. */
    register_button(FIRE_BTN, fire_btn);
    register_button(SLOW_MODE_BTN, slow_mode_btn);
    register_button(ARM_UP_BTN, arm_up_btn);
    register_button(ARM_UP_BTN, arm_down_btn);

    /* Enter an infinite loop. */
    while (true)
    {
        /* Set l_spd and r_spd to the forward joystick speed. */
        l_spd = (r_spd = get_axis(FWD_AXIS));

        /* Account for turning. */
        speed_mod = get_axis(TURN_AXIS);
        if (get_axis(FWD_AXIS) != 0) speed_mod *= 0.8;
        l_spd = safe_add_i8(l_spd, speed_mod);
        r_spd = safe_add_i8(r_spd, -1 * speed_mod);

        /* If slow mode is activated, make everything 3 times slower. */
        if (slow_mode)
        {
            l_spd /= 3;
            r_spd /= 3;
        }

        /* Set the motors to l_spd and r_spd. */
        motorSet(LEFT_MOT, l_spd);
        motorSet(RIGHT_MOT, r_spd);
    }
}
