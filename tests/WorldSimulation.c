/*
===========================================================
                     TEST INFORMATION

TEST NAME: WorldSimulation.c
CREATION DATE: 25/12/4 | International Date Format
LAST MODIFIED: 25/12/4 | International Date Format

===========================================================
                      TEST PURPOSE

This test is to mark & benchmark the prototype stage of Jubi.
It's to test top-level functions of world creation & usage.

If working correctly, the program should say the increasing
velocity & changing position of the box(s).

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
    JubiWorld2D WORLD = Jubi_CreateWorld2D();

    Body2D *Box = JBody2D_CreateBox(&WORLD, (Vector2){0, 0}, (Vector2){1, 1}, BODY_DYNAMIC, 1.0f);
    
    // ~1 second at 60 FPS
    for (int i=0; i < 60; i++) {
        Jubi_StepWorld2D(&WORLD, 0.033f);

        printf("Frame: %02d | Position: (%.3f, %.3f) | Velocity: (%.3f, %.3f) | Index: %d\n", i, Box -> Position.x, Box -> Position.y, Box -> Velocity.x, Box -> Velocity.y, Box -> Index);
    }
    
    return 0;
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
