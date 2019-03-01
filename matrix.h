//
//  matrix.h
//  libmath
//
//  Created by 中山一輝 on 2018/10/31.
//  Copyright © 2018年 中山一輝. All rights reserved.
//

#pragma once

// INCLUDE
#include <iostream>
#include <initializer_list>

// struct Matrix
template<typename TYPE, int COLS, int ROWS>
struct Matrix {
    TYPE values[ROWS][COLS];
    
    Matrix();
    Matrix(const Matrix<TYPE, COLS, ROWS>& m);
    Matrix(std::initializer_list<TYPE> init);

    inline int __attribute__((always_inline)) cols() const;
    inline int __attribute__((always_inline)) rows() const;
    inline void __attribute__((always_inline)) zeros();
    void identity();

    void mulMM(const Matrix<TYPE, COLS, ROWS>& m);
    template<int COLS_B>
    void mulMM(const Matrix<TYPE, COLS_B, COLS>& m, Matrix<TYPE, COLS_B, ROWS>& ret) const;

    void transpose();
    void transpose(Matrix<TYPE, ROWS, COLS>& ret);

    bool inverse();
    bool inverse(Matrix<TYPE, COLS, ROWS>& ret);

    void disp() const;
    void cofNNMatrix(int x, int y, Matrix<TYPE, COLS-1, ROWS-1>& ret) const;
    TYPE cofactor() const;
    const Matrix<TYPE, COLS, ROWS>& operator *= (float k);
};

/**
 * デフォルトコンストラクタ
 */
template<typename TYPE, int COLS, int ROWS>
Matrix<TYPE, COLS, ROWS>::Matrix() {
}

/**
 * コピーコンストラクタ
 */
template<typename TYPE, int COLS, int ROWS>
Matrix<TYPE, COLS, ROWS>::Matrix(const Matrix<TYPE, COLS, ROWS>& m) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            values[i][j] = m.values[i][j];
        }
    }
}

/**
 * 初期化子を使用したコンストラクタ
 */
template<typename TYPE, int COLS, int ROWS>
Matrix<TYPE, COLS, ROWS>::Matrix(std::initializer_list<TYPE> init) {
    const TYPE* init_array = init.begin();
    const TYPE* init_array_e = init.end();
    
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (init_array != init_array_e) {
                values[i][j] = *(init_array++);
            } else {
                values[i][j] = 0;
            }
        }
    }
}

/**
 * 行の大きさを返却する
 */
template<typename TYPE, int COLS, int ROWS>
inline int __attribute__((always_inline)) Matrix<TYPE, COLS, ROWS>::cols() const {
    return COLS;
}

/**
 * 列の大きさを返却する
 */
template<typename TYPE, int COLS, int ROWS>
inline int __attribute__((always_inline)) Matrix<TYPE, COLS, ROWS>::rows() const {
    return ROWS;
}

/**
 * 行列の全要素を0にする
 */
template<typename TYPE, int COLS, int ROWS>
inline void __attribute__((always_inline)) Matrix<TYPE, COLS, ROWS>::zeros() {
    memset(values, 0, sizeof(values));
}

/**
 * 単位行列を作成する
 */
template<typename TYPE, int COLS, int ROWS>
void Matrix<TYPE, COLS, ROWS>::identity() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            values[i][j] = (i == j);
        }
    }
}

/**
 * 行列同士の乗算を行う
 * 返却される行列(ret)の大きさは乗算し合う行列の行と列を組み合わせたものとなる。
 * this<TYPE, S, R1> * m<TYPE, C2, S> = ret<TYPE, C2, R1>
 */
template<typename TYPE, int COLS, int ROWS>
void Matrix<TYPE, COLS, ROWS>::mulMM(const Matrix<TYPE, COLS, ROWS>& m) {
    const int COLS_ROWS = COLS;

    Matrix<TYPE, COLS, ROWS> src(*this);
    zeros();

    for (int i = 0; i < ROWS; i++) {
        for (int k = 0; k < COLS_ROWS; k++) {
            for (int j = 0; j < COLS; j++) {
                values[i][j] += src.values[i][k] * m.values[k][j];
            }
        }
    }
}

/**
 * 行列同士の乗算を行う
 * 返却される行列(ret)の大きさは乗算し合う行列の行と列を組み合わせたものとなる。
 * this<TYPE, S, R1> * m<TYPE, C2, S> = ret<TYPE, C2, R1>
 */
template<typename TYPE, int COLS, int ROWS>
template<int COLS_B>
void Matrix<TYPE, COLS, ROWS>::mulMM(const Matrix<TYPE, COLS_B, COLS>& m, Matrix<TYPE, COLS_B, ROWS>& ret) const {
    const int COLS_ROWS_B = COLS;
    
    ret.zeros();
    
    for (int i = 0; i < ROWS; i++) {
        for (int k = 0; k < COLS_ROWS_B; k++) {
            for (int j = 0; j < COLS_B; j++) {
                ret.values[i][j] += values[i][k] * m.values[k][j];
            }
        }
    }
}

/**
 * 転置行列に置き換える
 */
template<typename TYPE, int COLS, int ROWS>
void Matrix<TYPE, COLS, ROWS>::transpose() {
    Matrix<TYPE, COLS, ROWS> src(*this);
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            values[j][i] = src.values[i][j];
        }
    }
}

/**
 * 転置行列の返却
 */
template<typename TYPE, int COLS, int ROWS>
void Matrix<TYPE, COLS, ROWS>::transpose(Matrix<TYPE, ROWS, COLS>& ret) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            ret.values[j][i] = values[i][j];
        }
    }
}

/**
 * 逆行列を求め置き換える
 * @return 逆行列が存在しない場合はfalse, 存在する場合はtrue
 */
template<typename TYPE, int COLS, int ROWS>
bool Matrix<TYPE, COLS, ROWS>::inverse() {
    Matrix<TYPE, COLS, ROWS> src(*this);
    return src.inverse(*this);
}

/**
 * 逆行列を返却する
 * @return 逆行列が存在しない場合はfalse, 存在する場合はtrue
 */
template<typename TYPE, int COLS, int ROWS>
bool Matrix<TYPE, COLS, ROWS>::inverse(Matrix<TYPE, COLS, ROWS>& inv_mat) {
    const float cof = cofactor();
    if (cof == 0 || COLS != ROWS) {
        // 逆行列が存在しない場合
        return false;
    }
    
    Matrix<TYPE, COLS-1, ROWS-1> cofnnm;
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            // 余因子行列の取得
            cofNNMatrix(j, i, cofnnm);

            // 符号の割り当て
            if (((i + j) % 2) == 0) {
                // 偶数の場合
                inv_mat.values[j][i] = cofnnm.cofactor();
            } else {
                // 奇数の場合
                inv_mat.values[j][i] = -cofnnm.cofactor();
            }
        }
    }
    
    // 余因子の逆数を求める
    const float rep_cof = 1.f / cof;
    
    // スカラーの乗算
    inv_mat *= rep_cof;
    
    return true;
}

/**
 * 標準出力に行列を表示する
 */
template<typename TYPE, int COLS, int ROWS>
void Matrix<TYPE, COLS, ROWS>::disp() const {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            std::cout << values[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * 余因子行列を返却する
 */
template<typename TYPE, int COLS, int ROWS>
void Matrix<TYPE, COLS, ROWS>::cofNNMatrix(int x, int y, Matrix<TYPE, COLS-1, ROWS-1>& ret) const {
    for (int i = 0, ii = 0; i < ret.rows(); i++, ii++) {
        if (ii == y) {
            ii++;
        }
        
        for (int j = 0, jj = 0; j < ret.cols(); j++, jj++) {
            if (jj == x) {
                jj++;
            }
            ret.values[i][j] = values[ii][jj];
        }
    }
}

/**
 * 余因子を返却する
 */
template<typename TYPE, int COLS, int ROWS>
TYPE Matrix<TYPE, COLS, ROWS>::cofactor() const {
    constexpr int cols = COLS == 2 ? 1 : COLS;
    
    TYPE sum = 0;
    for (int k = 0; k < cols; k++) {
        
        TYPE sum_p = 1;
        TYPE sum_m = 1;
        for (int i = 0; i < COLS; i++) {
            int i0 = i;
            int j0 = (i + k) % ROWS;
            sum_p *= values[i0][j0];
            
            int i1 = i;
            int j1 = ((COLS - 1)+ k - i) % COLS;
            sum_m *= values[i1][j1];
        }
        sum += sum_p;
        sum -= sum_m;
    }
    
    return sum;
}

/**
 * スカラーの乗算
 */
template<typename TYPE, int COLS, int ROWS>
const Matrix<TYPE, COLS, ROWS>& Matrix<TYPE, COLS, ROWS>::operator *= (float k) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            values[i][j] *= k;
        }
    }
    return *this;
}