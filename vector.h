//
//  vector.h
//  libmath
//
//  Created by 中山一輝 on 2019/01/02.
//  Copyright © 2019年 中山一輝. All rights reserved.
//

#pragma once

// INCLUDE
#include "matrix.h"
#include <math.h>
#include <string.h>
#include <iostream>
#include <initializer_list>

template<typename TYPE, int LEN>
class Vector {
public:
    TYPE values[LEN];

    Vector();
    Vector(TYPE initValue);
    Vector(const Vector<TYPE, LEN>& v);
    Vector(std::initializer_list<TYPE> init);
    template<class... Args>
    Vector(Args... args);


    inline int __attribute__((always_inline)) len() const;
    inline void __attribute__((always_inline)) zero();

    Vector<TYPE, LEN> operator - () const;
    Vector<TYPE, LEN> operator * (TYPE k) const;
    Vector<TYPE, LEN> operator / (TYPE k) const;
    Vector<TYPE, LEN> operator + (const Vector<TYPE, LEN>& v) const;
    Vector<TYPE, LEN> operator - (const Vector<TYPE, LEN>& v) const;
    Vector<TYPE, LEN> operator * (const Vector<TYPE, LEN>& v) const;
    const Vector<TYPE, LEN> operator += (const Vector<TYPE, LEN>& v);
    const Vector<TYPE, LEN> operator -= (const Vector<TYPE, LEN>& v);
    const Vector<TYPE, LEN> operator *= (const Vector<TYPE, LEN>& v);

    const Vector<TYPE, LEN>& add(const Vector<TYPE, LEN>& v);
    const Vector<TYPE, LEN>& sub(const Vector<TYPE, LEN>& v);

    const Vector<TYPE, LEN>& mulVS(float scalar);
    const Vector<TYPE, LEN>& mulMV(const Matrix<TYPE, LEN, LEN>& m);
    const Vector<TYPE, LEN>& mulHM(const Matrix<TYPE, LEN, LEN>& m);

    const Vector<TYPE, LEN>& normalize();

    const Vector<TYPE, LEN>& reflect(const Vector<TYPE, LEN>& n);
    const Vector<TYPE, LEN>& refract(const Vector<TYPE, LEN>& n, float n1, float n2);

    float dot(const Vector<TYPE, LEN>& v) const;
    void cross(const Vector<TYPE, LEN>& v, Vector<TYPE, LEN>& ret) const;

    void disp() const;
};

typedef Vector<float, 3> Vector3f;
typedef Vector<float, 4> Vector4f;
typedef Vector<uint8_t, 3> Vector3b;

/**
 * デフォルトコンストラクタ
 */
template<typename TYPE, int LEN>
Vector<TYPE, LEN>::Vector() {
}

/**
 * 
 */
template<typename TYPE, int LEN>
Vector<TYPE, LEN>::Vector(TYPE initValue) {
    for (int i = 0; i < LEN; i++) {
        values[i] = initValue;
    }
}

/**
 * コピーコンストラクタ
 */
template<typename TYPE, int LEN>
Vector<TYPE, LEN>::Vector(const Vector<TYPE, LEN>& v) {
    memcpy(values, v.values, sizeof(values));
}

/**
 * 初期化子を使用したコンストラクタ
 */
template<typename TYPE, int LEN>
Vector<TYPE, LEN>::Vector(std::initializer_list<TYPE> init) {
    const TYPE* init_array = init.begin();
    const TYPE* init_array_e = init.end();
    
    for (int i = 0; i < LEN; i++) {
        if (init_array != init_array_e) {
            values[i] = *(init_array++);
        } else {
            values[i] = 0;
        }
    }
}

template<typename TYPE, int LEN>
template<class... Args>
Vector<TYPE, LEN>::Vector(Args... args) {
    int i = 0;
    for (auto const& e : { args... }) {
        values[i++] = e;
        if (i == LEN) break;
    }
}

template<typename TYPE, int LEN>
int Vector<TYPE, LEN>::len() const {
    return LEN;
}

template<typename TYPE, int LEN>
void Vector<TYPE, LEN>::zero() {
    memset(values, 0, sizeof(values));
}

template<typename TYPE, int LEN>
Vector<TYPE, LEN> Vector<TYPE, LEN>::operator - () const {
    Vector<TYPE, LEN> self(*this);
    for (int i = 0; i < LEN; i++) {
        self.values[i] = -self.values[i];
    }
    return self;
}

template<typename TYPE, int LEN>
Vector<TYPE, LEN> Vector<TYPE, LEN>::operator * (TYPE k) const {
    Vector<TYPE, LEN> ret;
    for (int i = 0; i < LEN; i++) {
        ret.values[i] = values[i] * k;
    }
    return ret;
}

template<typename TYPE, int LEN>
Vector<TYPE, LEN> Vector<TYPE, LEN>::operator / (TYPE k) const {
    Vector<TYPE, LEN> ret;
    for (int i = 0; i < LEN; i++) {
        ret.values[i] = values[i] / k;
    }
    return ret;
}

template<typename TYPE, int LEN>
Vector<TYPE, LEN> Vector<TYPE, LEN>::operator + (const Vector<TYPE, LEN>& v) const {
    Vector<TYPE, LEN> ret;
    for (int i = 0; i < LEN; i++) {
        ret.values[i] = values[i] + v.values[i];
    }
    return ret;
}

template<typename TYPE, int LEN>
Vector<TYPE, LEN> Vector<TYPE, LEN>::operator - (const Vector<TYPE, LEN>& v) const {
    Vector<TYPE, LEN> ret;
    for (int i = 0; i < LEN; i++) {
        ret.values[i] = values[i] - v.values[i];
    }
    return ret;
}

template<typename TYPE, int LEN>
Vector<TYPE, LEN> Vector<TYPE, LEN>::operator * (const Vector<TYPE, LEN>& v) const {
    Vector<TYPE, LEN> ret;
    for (int i = 0; i < LEN; i++) {
        ret.values[i] = values[i] * v.values[i];
    }
    return ret;
}

template<typename TYPE, int LEN>
const Vector<TYPE, LEN> Vector<TYPE, LEN>::operator += (const Vector<TYPE, LEN>& v) {
    for (int i = 0; i < LEN; i++) {
        values[i] = values[i] + v.values[i];
    }
    return *this;
}

template<typename TYPE, int LEN>
const Vector<TYPE, LEN> Vector<TYPE, LEN>::operator -= (const Vector<TYPE, LEN>& v) {
    for (int i = 0; i < LEN; i++) {
        values[i] = values[i] - v.values[i];
    }
    return *this;
}

template<typename TYPE, int LEN>
const Vector<TYPE, LEN> Vector<TYPE, LEN>::operator *= (const Vector<TYPE, LEN>& v) {
    for (int i = 0; i < LEN; i++) {
        values[i] = values[i] * v.values[i];
    }
    return *this;
}

template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::add(const Vector<TYPE, LEN>& v) {
    for (int i = 0; i < LEN; i++) {
        values[i] += v.values[i];
    }
    return *this;
}

template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::sub(const Vector<TYPE, LEN>& v) {
    for (int i = 0; i < LEN; i++) {
        values[i] -= v.values[i];
    }
    return *this;
}

template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::mulVS(float scalar) {
    for (int i = 0; i < LEN; i++) {
        values[i] *= scalar;
    }
    return *this;
}

/**
 * 列ベクトル(本オブジェクト)と行列の積を求め結果を置き換える
 * @param m 行列
 * @return 行列の乗算結果を格納した本オブジェクトへの参照を返却する
 */
template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::mulMV(const Matrix<TYPE, LEN, LEN>& m) {
    Vector<TYPE, LEN> src(*this);
    zero();

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            values[i] += src.values[j] * m.values[i][j];
        }
    }

    return *this;
}

/**
 * 行ベクトル(本オブジェクト)と行列の積を求め結果を置き換える
 * @param m 行列
 * @return 行列の乗算結果を格納した本オブジェクトへの参照を返却する
 */
template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::mulHM(const Matrix<TYPE, LEN, LEN>& m) {
    Vector<TYPE, LEN> src(*this);
    zero();

    for (int i = 0; i < LEN; i++) {
        for (int j = 0; j < LEN; j++) {
            values[i] += src.values[j] * m.values[j][i];
        }
    }

    return *this;
}

template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::normalize() {
    TYPE mag = 0;
    for (int i = 0; i < LEN; i++) {
        mag += values[i] * values[i];
    }

    mag = 1 / sqrt(mag);

    for (int i = 0; i < LEN; i++) {
        values[i] *= mag;
    }

    return *this;
}

template<typename TYPE, int LEN>
void Vector<TYPE, LEN>::disp() const {
    for (int i = 0; i < LEN; i++) {
        std::cout << values[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * 反射ベクトルを求め置き換える
 * @param n 法線ベクトル
 * @return 反射ベクトル(面から離れる方向)を格納した本オブジェクトの参照を返却する
 * @warning 入力するベクトルは以下のルールに従うこと
 *   a. 入射ベクトル(本オブジェクト)は面に対して近く方向であること
 *   b. 法線ベクトルと入射ベクトルとの内積は0未満であること
 */
template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::reflect(const Vector<TYPE, LEN>& n) {
    // o = i + 2(dot(-i, n))n
    float d2 = 2 * n.dot(-(*this));
    add(n * d2);
    return *this;
}

/**
 * 物質1から物質2に入射したときの屈折ベクトルを求め置き換える
 * @param n 法線ベクトル
 * @param n1 物質1の絶対屈折率
 * @parma n2 物質2の絶対屈折率
 * @return 屈折ベクトル(面から離れる方向)を格納した本オブジェクトの参照を返却する
 * @warning 入力するベクトルは以下のルールに従うこと
 *   a. 入射ベクトル(本オブジェクト)は面に対して近く方向であること
 *   b. 法線ベクトルと入射ベクトルとの内積は0未満であること
 */
template<typename TYPE, int LEN>
const Vector<TYPE, LEN>& Vector<TYPE, LEN>::refract(
        const Vector<TYPE, LEN>& n, float n1, float n2) {
    float n1n2 = n1 / n2;
    float n2n1 = n2 / n1;
    float n2n1_2 = n2n1 * n2n1;
    float cos_theta = dot(-n);
    float cos_theta2 = cos_theta * cos_theta;
    float k = sqrt(n2n1_2 - (1.f - cos_theta2)) - cos_theta;
    sub(n * k);
    mulVS(n1n2);
    return *this;
}

template<typename TYPE, int LEN>
float Vector<TYPE, LEN>::dot(const Vector<TYPE, LEN>& v) const {
    float d = 0;
    for (int i = 0; i < LEN; i++) {
        d += values[i] * v.values[i];
    }
    return d;
}

template<typename TYPE, int LEN>
void Vector<TYPE, LEN>::cross(const Vector<TYPE, LEN>& v, Vector<TYPE, LEN>& ret) const {
    if (LEN != 3) return;

    // v0 = a1b2 - a2b1
    TYPE v0 = values[1] * v.values[2] - values[2] * v.values[1];

    // v1 = a0b2 - a2b0
    TYPE v1 = -values[0] * v.values[2] + values[2] * v.values[0];

    // v2 = a0b1 - a1b0
    TYPE v2 = values[0] * v.values[1] - values[1] * v.values[0];

    ret.values[0] = v0;
    ret.values[1] = v1;
    ret.values[2] = v2;
}
