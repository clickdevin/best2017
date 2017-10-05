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

/* Toggle variables */
b8 fast_mode    = false;
b8 arm_move     = true;

/* These static functions ending in _btn are used
as callbacks for our button-handling system. */

static void fire_btn()
{
    if (motorGet(FIRE_MOT) == 127)
        motorSet(FIRE_MOT, 0);
    else motorSet(FIRE_MOT, 127);
}

static void fast_mode_btn()
{
    fast_mode = !fast_mode;
}

static void arm_move_btn()
{
    arm_move = !arm_move;
}

/* Beginning of the main part of the program */
void operatorControl()
{
    /* We need to assign and manipulate these variables at little later. */
    i8 l_spd;
    i8 r_spd;
    i8 a_spd;
    i8 speed_mod;

    /* Register the static functions above to our button system. */
    register_button(FIRE_BTN, fire_btn);
    register_button(FAST_MODE_BTN, fast_mode_btn);
    register_button(ARM_MOVE_BTN, arm_move_btn);

    /* Enter an infinite loop. */
    while (true)
    {
        /* Set l_spd and r_spd to the forward joystick speed. */
        l_spd = (r_spd = get_axis(FWD_AXIS));

        /* Account for turning. */
        speed_mod = get_axis(TURN_AXIS);
        l_spd = safe_add_i8(l_spd, 0.6 * speed_mod);
        r_spd = safe_add_i8(r_spd, -0.6 * speed_mod);

        /* Arm motor control */
        if (joystickGetDigital(1, ARM_DOWN_BTN))
        {
            a_spd = 127;
            l_spd = arm_move ? safe_add_i8(l_spd, -44): 0;
            r_spd = arm_move ? safe_add_i8(r_spd, -44): 0;
        } else if (joystickGetDigital(1, ARM_UP_BTN)) {
            a_spd = -127;
            l_spd = arm_move ? safe_add_i8(l_spd, 44): 0;
            r_spd = arm_move ? safe_add_i8(r_spd, 44): 0;
        }
        else a_spd = 0;

        /* If we aren't in fast mode, reduce speeds. */
        if (!fast_mode)
        {
            if (get_axis(FWD_AXIS) < 0)
            {
                l_spd /= 3;
                r_spd /= 3;
            } else {
                l_spd /= 2;
                r_spd /= 2;
            }
            a_spd /= 2;
        }

        /* Set the motors to l_spd and r_spd. */
        motorSet(LEFT_MOT, l_spd);
        motorSet(RIGHT_MOT, r_spd);
        motorSet(ARM_MOT, a_spd);
    }
}
