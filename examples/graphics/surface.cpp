/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <arrayfire.h>
#include <cstdio>
#include <math.h>

using namespace af;

static const int POINTS = 30;
static const int N = 2 * POINTS;

int main(int argc, char *argv[])
{
    try {
        // Initialize the kernel array just once
        af::info();
        af::Window myWindow(800, 800, "3D Surface example: ArrayFire");

        // Creates grid of between [-1 1] with precision of 1 / POINTS
        const array x = iota(dim4(N, 1), dim4(1, N)) / POINTS - 1;
        const array y = iota(dim4(1, N), dim4(N, 1)) / POINTS - 1;

        std::cout << x.dims()  << y.dims() << std::endl;

        static float t=0;
        while(!myWindow.close()) {
            t+=0.07;
            array z = 10*x*-abs(y) * cos(x*x*(y+t))+sin(y*(x+t))-1.5;
            myWindow.surface(x, y, z);
        }

    } catch (af::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }

    #ifdef WIN32 // pause in Windows
    if (!(argc == 2 && argv[1][0] == '-')) {
        printf("hit [enter]...");
        fflush(stdout);
        getchar();
    }
    #endif
    return 0;
}
