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

b8 slow_mode = false;

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

void operatorControl()
{
    i8 l_spd;
    i8 r_spd;

    motorSet(ARM_SERVO_1, -127);
    motorSet(ARM_SERVO_2, 127);

    register_button(FIRE_BTN, fire_btn);
    register_button(SLOW_MODE_BTN, slow_mode_btn);
    register_button(ARM_UP_BTN, arm_up_btn);
    register_button(ARM_UP_BTN, arm_down_btn);

    while (true)
    {
        l_spd = (r_spd = get_axis(FWD_AXIS));

        l_spd = safe_add_i8(l_spd, get_axis(TURN_AXIS));
        r_spd = safe_add_i8(r_spd, -1 * get_axis(TURN_AXIS));

        if (slow_mode)
        {
            l_spd /= 4;
            r_spd /= 4;
        }

        printf("L: %.3d; R: %.3d\r", l_spd, r_spd);

        motorSet(LEFT_MOT, l_spd);
        motorSet(RIGHT_MOT, r_spd);
    }
}
