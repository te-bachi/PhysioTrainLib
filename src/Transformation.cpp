/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 */

#include "config.h"
#include "Transformation.h"
#include "avr/dtostrf.h"
#include <stdio.h>

Transformation::Transformation()
: Transformation(Transformation::TYPE_EYE)
{

}

Transformation::Transformation(Type type)
{
    int m;
    int n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            if (m == n && type == Transformation::TYPE_EYE) {
                a[m][n] = 1;
            } else {
                a[m][n] = 0;
            }
        }
    }
}

Transformation::Transformation(Position &pos, RotationMatrix &rot)
{
    int m;
    int n;

    for (m = 0; m < RotationMatrix::SIZE; m++) {
        for (n = 0; n < RotationMatrix::SIZE; n++) {
            a[m][n] = rot.getElement(m, n);
        }
    }

    a[0][3] = pos.getX();
    a[1][3] = pos.getY();
    a[2][3] = pos.getZ();

    a[3][0] = 0.0f;
    a[3][1] = 0.0f;
    a[3][2] = 0.0f;
    a[3][3] = 1.0f;
}

Transformation::Transformation(const Transformation& trans)
{
    int m;
    int n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            a[m][n] = trans.a[m][n];
        }
    }

}

Transformation::~Transformation()
{
    //
}

float
Transformation::getElement(int m, int n)
{
    if (m >= 0 && m < SIZE && n >= 0 && n < SIZE) {
        return a[m][n];
    }
    return 0.0f;
}

String
Transformation::toString()
{
    String res = "";
    char str[16][16];
    int  m;
    int  n;
    for (m = 0; m < SIZE; m++) {
        res += "  ";
        for (n = 0; n < SIZE; n++) {
            dtostrf(a[m][n], 8, 4, str[(m << (SIZE - 2)) + n]);
            res += str[(m << (SIZE - 2)) + n];
        }
        res += "\n";
    }

    return res;
}



Transformation
Transformation::operator* (const Transformation &other)
{
    Transformation  res(Transformation::TYPE_NULL);
    int             i;
    int             j;
    int             k;

    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            for (k = 0; k < SIZE; ++k) {
                res.a[i][j] += this->a[i][k] * other.a[k][j];
            }
        }
    }

    return res;
}
