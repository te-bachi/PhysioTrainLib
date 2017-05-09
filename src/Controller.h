/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 02.05.2017
 */

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


class Controller {

    private:

    public:
        enum Mode {
            TEACH,
            EXERCISE,
            EVALUATE
        };



    public:
        Controller();
        virtual     ~Controller();


    private:
};

#endif

