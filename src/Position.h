/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 23.04.2017
 */

#ifndef __POSITION_H__
#define __POSITION_H__

class Position {

    private:
        float                   _x;
        float                   _y;
        float                   _z;

    public:
                                Position();
                                Position(float x, float y, float z);
                                Position(const Position& q);
        virtual                 ~Position();

        float                   getX();
        float                   getY();
        float                   getZ();

};

#endif

