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

typedef struct
{
    u8 button;
    void (*function)();
} bl_params_t;

void button_listener(void *params_void)
{
    bl_params_t *params = (bl_params_t *)params_void;
    if (digitalRead(params->button))
    {
        params->function();
        taskDelay(BTN_DELAY);
    }
}

void register_button(u8 button, void (*function)())
{
    void *params_void = malloc(sizeof(bl_params_t));
    bl_params_t *params = (bl_params_t *)params_void;
    params->button = button;
    params->function = function;
    taskCreate(
        button_listener,
        TASK_DEFAULT_STACK_SIZE,
        params,
        TASK_PRIORITY_DEFAULT
    );
}
