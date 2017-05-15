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
        TEACH,              // Switch to Teach mode
        TEACH_WAIT,         // Wait
        TEACH_BEGIN,
        TEACH_RUN,
        TEACH_END,
        EXERCISE,           // Switch to Exercise mode
        EXERCISE_WAIT,      // Wait
        EXERCISE_BEGIN,
        EXERCISE_RUN,
        EXERCISE_END,
        EVALUATE,           // Switch to Evaluate mode
        EVALUATE_WAIT,
        EVALUATE_SERIAL,
        ERROR,              // Start-Stop-Button pressed while changing mode => release button first!
        START
    } State;

    private:
        State           _currentState;
        //State           _nextState;
        Mode            _mode;

    public:
                        StateMachine();
        virtual         ~StateMachine();

        void            run(Mode &mode, bool start);

        String          toString();

    private:
        bool            checkState(Mode &mode);
        bool            checkStateOnRun(Mode &mode, State state);
        State           nextState(Mode &mode);

};

#endif

