
#include "config.h"
#include "RotationMatrix.h"

RotationMatrix::RotationMatrix()
{
    int m;
    int n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            a[m][n] = 0;
        }
    }
}

RotationMatrix::RotationMatrix(const RotationMatrix& rot)
{
    int m;
    int n;

    for (m = 0; m < SIZE; m++) {
        for (n = 0; n < SIZE; n++) {
            a[m][n] = rot.a[m][n];
        }
    }
}

RotationMatrix::~RotationMatrix()
{
    //
}

float
RotationMatrix::getElement(int m, int n)
{
    if (m >= 0 && m < SIZE && n >= 0 && n < SIZE) {
        return a[m][n];
    }
    return 0.0f;
}
