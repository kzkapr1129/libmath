//
//  main.cpp
//  TestApp
//
//  Created by 中山一輝 on 2018/10/20.
//  Copyright © 2018年 中山一輝. All rights reserved.
//

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <iostream>

template<int COLS>
void dispM(const int M[4][COLS]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

template<int COLS>
void dispM(const float M[4][COLS]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%f ", M[i][j]);
        }
        printf("\n");
    }
}

void dispV(const int V[4]) {
    for (int i = 0; i < 4; i++) {
        printf("%d ", V[i]);
    }
    printf("\n");
}

void dispV(const float V[4]) {
    for (int i = 0; i < 4; i++) {
        printf("%f ", V[i]);
    }
    printf("\n");
}


template<typename TYPE, int AW, int BW>
void mulMM(const TYPE a[4][AW], const TYPE b[4][BW], TYPE c[4][BW]) {
#ifdef DEBUG
    if (AW < BW || AW > 4) {
        std::cout << "WARN: AW: " << AW << ", BW:" << BW << std::endl;
        return;
    }
#endif
    constexpr size_t SIZE = sizeof(TYPE) * 4 * BW;
    memset(c, 0, SIZE);
    
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < AW; k++) {
            for (int j = 0; j < BW; j++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

template<typename TYPE, int AW>
void mulMV(const TYPE a[4][AW], const TYPE b[4], TYPE c[4]) {
#ifdef DEBUG
    if (AW > 4) {
        std::cout << "WARN: AW: " << AW << std::endl;
        return;
    }
#endif
    constexpr size_t SIZE = sizeof(TYPE) * 4;
    memset(c, 0, SIZE);
    
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < AW; k++) {
            c[i] += a[i][k] * b[k];
        }
    }
}

int main(int argc, const char * argv[]) {
    float a[4][4] = {{2, 3, 8, 6}, {1, 4, 8, 5}, {2, 1, 4, 3}, {8, 8, 6, 3}};
    float b[4][4] = {{3, 6, 0, 0}, {6, 4, 0, 0}, {7, 2, 0, 0}, {6, 3, 0, 0}};
    float c[4][4];
    mulMM(a, b, c);
    dispM(c);
    
    float d[4][4] = {{2, 3, 8, 6}, {1, 4, 8, 5}, {2, 1, 4, 3}, {8, 8, 6, 3}};
    float e[4]= {3, 6, 7, 6};
    float f[4];
    mulMV(d, e, f);
    dispV(f);
    
    return 0;
}
