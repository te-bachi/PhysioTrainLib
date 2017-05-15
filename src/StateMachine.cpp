/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 14.05.2017
 */

#include "config.h"
#include "StateMachine.h"
#include "SdCard.h"
#include "PhysioTrain.h"

StateMachine::StateMachine()
: _currentState(START), /*_nextState(START), */ _mode(Mode::NONE)
{

}

StateMachine::~StateMachine()
{

}

void
StateMachine::run(Mode &mode, bool start)
{
    DateTime now;

    switch (_currentState) {
        case State::NONE:
            checkState(mode);
            break;

        case State::TEACH:
            if (start) {
                _currentState = State::ERROR;
            } else {
                _mode         = mode;
                _currentState = State::TEACH_WAIT;
            }
            break;

        case State::TEACH_WAIT:
            if (!checkState(mode)) {
                /* Start */
                if (start) {
                    _currentState = State::TEACH_BEGIN;
                }
            }
            break;

        case State::TEACH_BEGIN:
            now             = rtc.now();
            teachFile       = sdCard.replaceTeachFile(now);
            if (!teachFile) {
                SerialUSB.println("teachFile <NULL>");
            }
            _currentState = State::TEACH_RUN;
            break;

        case State::TEACH_RUN:
            if (!checkStateOnRun(mode, State::TEACH_END)) {

                /* Stop */
                if (!start) {
                    _currentState = State::TEACH_END;

                /* Run */
                } else {

                }
            }
            break;

        case State::TEACH_END:
            teachFile.close();
            /* Good */
            if (!start) {
                _currentState = State::TEACH;

            /* Bad */
            } else {
                _currentState = State::ERROR;
            }
            break;

        case State::EXERCISE:
            if (start) {
                _currentState = State::ERROR;
            } else {
                _mode         = mode;
                _currentState = State::EXERCISE_WAIT;
            }
            break;

        case State::EXERCISE_WAIT:
            if (!checkState(mode)) {
                /* Start */
                if (start) {
                    _currentState = State::EXERCISE_BEGIN;
                }
            }
            break;

        case State::EXERCISE_BEGIN:
            now             = rtc.now();
            teachFile       = sdCard.openNextTeachFile();
            exerciseFile    = sdCard.openExerciseFile(now);
            resultFile      = sdCard.openResultFile(now);

            if (!teachFile) {
                SerialUSB.println("teachFile <NULL>");
            }

            if (!exerciseFile) {
                SerialUSB.println("exerciseFile <NULL>");
            }

            _currentState = State::EXERCISE_RUN;
            break;

        case State::EXERCISE_RUN:
            if (!checkStateOnRun(mode, State::EXERCISE_END)) {

                /* Stop */
                if (!start) {
                    _currentState = State::EXERCISE_END;

                /* Run */
                } else {

                }
            }
            break;

        case State::EXERCISE_END:
            teachFile.close();
            exerciseFile.close();
            resultFile.close();

            /* Good */
            if (!start) {
                _currentState = State::EXERCISE;

            /* Bad */
            } else {
                _currentState = State::ERROR;
            }
            break;

        case State::EVALUATE:
            if (start) {
                _currentState = State::ERROR;
            } else {

                /**/
                sdCard.openRoot();
                sdCard.rewindRoot();
                File file = sdCard.openNextExerciseFile();
                while (file) {
                    SerialUSB.print("==> ");
                    SerialUSB.println(file.name());
                    file.close();
                    file = sdCard.openNextExerciseFile();
                }
                sdCard.closeRoot();

                _mode         = mode;
                _currentState = State::EVALUATE_WAIT;
            }
            break;

        case State::EVALUATE_WAIT:
            if (!checkState(mode)) {

                /* Start Serial*/
                if (start) {
                    _currentState = State::EVALUATE_SERIAL;
                }
            }
            break;

        case State::EVALUATE_SERIAL:
            if (!checkState(mode)) {

                /* Start => Error */
                if (!start) {
                    _currentState = State::EVALUATE;
                }
            }
            break;

        case State::ERROR:
            if (!start) {
                _currentState = nextState(mode);
            }
            break;

        case State::START:
        default:
            _currentState = nextState(mode);
            break;
    }
}

String
StateMachine::toString()
{
    String str;
    switch (_currentState) {
        case State::NONE:               str = "NONE";               break;
        case State::TEACH:              str = "TEACH";              break;
        case State::TEACH_WAIT:         str = "TEACH_WAIT";         break;
        case State::TEACH_BEGIN:        str = "TEACH_BEGIN";        break;
        case State::TEACH_RUN:          str = "TEACH_RUN";          break;
        case State::TEACH_END:          str = "TEACH_END";          break;
        case State::EXERCISE:           str = "EXERCISE";           break;
        case State::EXERCISE_WAIT:      str = "EXERCISE_WAIT";      break;
        case State::EXERCISE_BEGIN:     str = "EXERCISE_BEGIN";     break;
        case State::EXERCISE_RUN:       str = "EXERCISE_RUN";       break;
        case State::EXERCISE_END:       str = "EXERCISE_END";       break;
        case State::EVALUATE:           str = "EVALUATE";           break;
        case State::EVALUATE_WAIT:      str = "EVALUATE_WAIT";      break;
        case State::EVALUATE_SERIAL:    str = "EVALUATE_SERIAL";    break;
        case State::ERROR:              str = "ERROR";              break;
        case State::START:              str = "START";              break;
        default:                        str = "<EMPTY>";            break;
    }
    return str;
}


/**
 * Change mode/state NOW!
 **/
bool
StateMachine::checkState(Mode &mode)
{
    if (mode != _mode) {
        _mode         = mode;
        _currentState = nextState(mode);
        //_nextState    = nextState(mode);

        return true;
    }

    return false;
}

/**
 * Changed Mode during RUN
 **/
bool
StateMachine::checkStateOnRun(Mode &mode, StateMachine::State state)
{
    if (mode != _mode) {
        _mode           = mode;
        _currentState   = state;
        //_nextState      = nextState(mode);

        return true;
    }

    return false;
}

StateMachine::State
StateMachine::nextState(Mode &mode)
{
    if (mode == Mode::TEACH) {
        return State::TEACH;

    } else if (mode == Mode::EXERCISE) {
        return State::EXERCISE;

    } else if (mode == Mode::EVALUATE) {
        return State::EVALUATE;
    }

    return State::NONE;
}

