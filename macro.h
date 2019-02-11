//
//  macro.h
//  libmath
//
//  Created by 中山一輝 on 2019/02/11.
//  Copyright © 2019年 中山一輝. All rights reserved.
//

#pragma once

#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

#define RADIAN(angle) ((angle) * M_PI / 180)
#define DEGREE(radian) (((radian)/2/M_PI)*360)