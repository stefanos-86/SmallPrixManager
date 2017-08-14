#include "TangentCircle.h"

#include <cmath>



#include <iostream>


namespace spm {

    struct Matrix3x3 {
        float at[3][3];  // at so that you do matrix.at[x][y].
    };

    // Stolen from https://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c
    static const Matrix3x3 invert3x3(const Matrix3x3& m) {
        // computes the inverse of a matrix m
        float det = m.at[0][0] * (m.at[1][1] * m.at[2][2] - m.at[2][1] * m.at[1][2]) -
            m.at[0][1] * (m.at[1][0] * m.at[2][2] - m.at[1][2] * m.at[2][0]) +
            m.at[0][2] * (m.at[1][0] * m.at[2][1] - m.at[1][1] * m.at[2][0]);

        float invdet = 1 / det;

        Matrix3x3 minv; // inverse of matrix m
        minv.at[0][0] = (m.at[1][1] * m.at[2][2] - m.at[2][1] * m.at[1][2]) * invdet;
        minv.at[0][1] = (m.at[0][2] * m.at[2][1] - m.at[0][1] * m.at[2][2]) * invdet;
        minv.at[0][2] = (m.at[0][1] * m.at[1][2] - m.at[0][2] * m.at[1][1]) * invdet;
        minv.at[1][0] = (m.at[1][2] * m.at[2][0] - m.at[1][0] * m.at[2][2]) * invdet;
        minv.at[1][1] = (m.at[0][0] * m.at[2][2] - m.at[0][2] * m.at[2][0]) * invdet;
        minv.at[1][2] = (m.at[1][0] * m.at[0][2] - m.at[0][0] * m.at[1][2]) * invdet;
        minv.at[2][0] = (m.at[1][0] * m.at[2][1] - m.at[2][0] * m.at[1][1]) * invdet;
        minv.at[2][1] = (m.at[2][0] * m.at[0][1] - m.at[0][0] * m.at[2][1]) * invdet;
        minv.at[2][2] = (m.at[0][0] * m.at[1][1] - m.at[1][0] * m.at[0][1]) * invdet;

        return minv;
    }


    TangentCircle::TangentCircle(const sf::Vector2f& p0, const sf::Vector2f& p1, const sf::Vector2f& p2) {
        Matrix3x3 initial;
        initial.at[0][0] = p0.x; initial.at[0][1] = p0.y; initial.at[0][2] = 1;
        initial.at[1][0] = p1.x; initial.at[1][1] = p1.y; initial.at[1][2] = 1;
        initial.at[2][0] = p2.x; initial.at[2][1] = p2.y; initial.at[2][2] = 1;

        Matrix3x3 inverse = invert3x3(initial);

        const float coefficients[] = { -(p0.x * p0.x + p0.y * p0.y),
            -(p1.x * p1.x + p1.y * p1.y),
            -(p2.x * p2.x + p2.y * p2.y) };


        a = inverse.at[0][0] * coefficients[0];
        a += inverse.at[0][1] * coefficients[1];
        a += inverse.at[0][2] * coefficients[2];

        b = inverse.at[1][0] * coefficients[0];
        b += inverse.at[1][1] * coefficients[1];
        b += inverse.at[1][2] * coefficients[2];

        c = inverse.at[2][0] * coefficients[0];
        c += inverse.at[2][1] * coefficients[1];
        c += inverse.at[2][2] * coefficients[2];
    }

    float TangentCircle::radius() const {
        const float halfA = - a / 2;
        const float halfB = - b / 2;
        return sqrt( (halfA * halfA) + (halfB * halfB) - c);
    }

}