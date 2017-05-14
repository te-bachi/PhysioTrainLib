/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 14.05.2017
 */

#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include "WString.h"
#include "Mode.h"

class StateMachine {

    typedef enum _State {
        NONE,
        TEACH,
        TEACH_BEGIN,
        TEACH_RUN,
        TEACH_END,
        EXERCISE,
        EXERCISE_BEGIN,
        EXERCISE_RUN,
        EXERCISE_END,
        EVALUATE,
        START
    } State;

    private:
        State           _currentState;
        State           _nextState;
        Mode            _mode;

    public:
                        StateMachine();
        virtual         ~StateMachine();

        void            run(Mode &mode, bool start);

        String          toString();

    private:
        void            checkState(Mode &mode);
        State           nextState(Mode &mode);

};

#endif

