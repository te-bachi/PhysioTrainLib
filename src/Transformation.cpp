/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 */

#include "config.h"
#include "Transformation.h"

Transformation::Transformation()
{
    int m;
    int n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            if (m == n) {
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
    a[1][3] = pos.getX();
    a[2][3] = pos.getX();

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
