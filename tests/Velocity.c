/*
===========================================================
                     TEST INFORMATION

TEST NAME: Velocity.c
CREATION DATE: 25/12/3 | International Date Format
LAST MODIFIED: 25/12/3 | International Date Format

===========================================================
                      TEST PURPOSE

This test is to mark & benchmark the prototype stage of Jubi.
It's to test top-level functions of 2D physics.

If working correctly, the program should say the increasing
velocity on the Y axis for the box.

===========================================================
                   LICENSE INFORMATION

The following software is protected under the MIT license.
More detailed information is present at the root LICENSE
file AND OR the end of the file.

===========================================================
*/

#define JUBI_IMPLEMENTATION
#include "../Jubi.h"

#include <stdio.h>

int main() {
    Body2D Box = JBody2D_CreateBox(NULL, (Vector2){0, 0}, (Vector2){4, 4}, BODY_DYNAMIC, 0.4f);

    printf("START VELOCITY\nY Velocity: %f\n\n", Box.Velocity.y);

    for (int i=0; i < 10; i++) {
        // We actually have a built in function for testing for once.
        JVector2_ApplyGravity(&Box, TIME_STEP);

        printf("Y Velocity: %f\n", Box.Velocity.y);
    }
}

/*

All source code & software are available under the MIT license:
    MIT License

    Copyright (c) 2025 Averi

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
