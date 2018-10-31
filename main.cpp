//
//  main.cpp
//  TestApp
//
//  Created by 中山一輝 on 2018/10/20.
//  Copyright © 2018年 中山一輝. All rights reserved.
//

#include "matrix.h"

int main(int argc, const char * argv[]) {
    Matrix<float, 3, 3> m = {
             1,2,1,
             2,5,6,
             1,3,4
        };

    Matrix<float, 3, 3> inv;
    if (m.inverse(inv)) {
        Matrix<float, 3, 3> mi;
        m.mulMM(mi, inv);

        std::cout << "m:" << std::endl;
        m.disp();

        std::cout << "inv:" << std::endl;
        inv.disp();

        std::cout << "m*inv:" << std::endl;
        mi.disp();

        std::cout << "identity: " << std::endl;
        m.identity();
        m.disp();
    } else {
        std::cout << "inverse matrix didn't exist" << std::endl;
    }
    return 0;
}
