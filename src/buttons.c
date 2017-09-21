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

/* This file contains the logic for our multi-threaded button system. */

#include <defs.h>

/* Because we can only pass a single void pointer to our thread
function, we use a struct to actually store all the arguments. */
typedef struct
{
    u8 buttonGroup;
    u8 button;
    void (*function)();
} bl_params_t;

/* This is the function that actaully runs in its own
thread for every button. It checks if the button has been
pressed, and if it has, runs the corresponding function.
Then, the task gets delayed to prevent accidental extra presses. */
void button_listener(void *params_void)
{
    bl_params_t *params = (bl_params_t *)params_void;
    while (1)
    {
        if (joystickGetDigital(1, params->buttonGroup, params->button))
        {
            params->function();
            taskDelay(BTN_DELAY);
        }
    }
}

/* This function takes a button and a function and sets up
a thread to run the function when the button is pressed. */
void register_button(u8 buttonGroup, u8 button, void (*function)())
{
    /* To start, we need to reserve a bit of
    data on the heap. This way, the data isn't lost when
    the stack returns to the function that called this one. */
    void *params_void = malloc(sizeof(bl_params_t));
    /* Next, we need to cast the void pointer to a bl_params_t
    pointer, so we can treat the data as the bl_params_t struct. */
    bl_params_t *params = (bl_params_t *)params_void;
    /* After that, we store this function's arguments in the struct. */
    params->buttonGroup = buttonGroup;
    params->button = button;
    params->function = function;
    /* Lastly, we create a new thread and pass a pointer
    to the struct we made at the beginning to it. */
    taskCreate(
        button_listener,
        TASK_DEFAULT_STACK_SIZE,
        params,
        TASK_PRIORITY_DEFAULT
    );
}
