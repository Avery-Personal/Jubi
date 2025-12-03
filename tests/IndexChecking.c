/*
===========================================================
                     TEST INFORMATION

TEST NAME: BoxCollision.c
CREATION DATE: 25/12/2 | International Date Format
LAST MODIFIED: 25/12/2 | International Date Format

===========================================================
                      TEST PURPOSE

This test is to mark & benchmark the baby stage of Jubi.
It's to test top-level functions of index/JubiBody2D creation.

If working correctly, the program should say the two indexes
of the bodies (-1 if not in a world).

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

    Body2D Box1 = JBody2D_CreateBox(NULL, (Vector2){0, 0}, (Vector2){4, 4}, BODY_DYNAMIC, 1.0f);
    Body2D Box2 = JBody2D_CreateBox(&WORLD, (Vector2){2, 2}, (Vector2){2, 2}, BODY_STATIC, 0.0f);
    
    printf("Box1 Index: %d\n", Box1.Index);
    printf("Box2 Index: %d\n", Box2.Index);
    
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
