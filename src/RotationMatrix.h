/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 */

#ifndef __ROTATION_MATRIX_H__
#define __ROTATION_MATRIX_H__

class RotationMatrix {
    public:
        static const int        SIZE = 3;
        float                   a[SIZE][SIZE];

    private:

    public:
                                RotationMatrix();
                                RotationMatrix(const RotationMatrix& rot);
        virtual                 ~RotationMatrix();

        float                   getElement(int m, int n);

};

#endif
