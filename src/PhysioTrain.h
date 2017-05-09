/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 02.05.2017
 */

#ifndef __PHYSIO_TRAIN_H__
#define __PHYSIO_TRAIN_H__


class PhysioTrain {

    private:

    public:
        enum Mode {
            TEACH,
            EXERCISE,
            EVALUATE
        };
        static Mode  MODE;



    public:
        PhysioTrain();
        virtual     ~PhysioTrain();


    private:
};

#endif

