/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 */

#ifndef __TRANSFORMATION_H__
#define __TRANSFORMATION_H__

#include "Position.h"
#include "RotationMatrix.h"

class Transformation {
    public:
        static const int        SIZE = 4;
        float                   a[SIZE][SIZE];

    private:

    public:
                                Transformation();
                                Transformation(Position &pos, RotationMatrix &rot);
                                Transformation(const Transformation& q);
        virtual                 ~Transformation();

};

#endif

