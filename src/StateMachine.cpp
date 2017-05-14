/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 14.05.2017
 */

#include "config.h"
#include "StateMachine.h"
#include "SdCard.h"

StateMachine::StateMachine()
: _currentState(START), _nextState(START), _mode(Mode::NONE)
{

}

StateMachine::~StateMachine()
{

}

void
StateMachine::run(Mode &mode, bool start)
{
    /*
    if (_currentState != _nextState) {
        _currentState = _nextState;
    }
    */

    switch (_currentState) {
        case State::NONE:
            checkState(mode);
            break;

        case State::TEACH:
            checkState(mode);
            if (start) {
                _currentState = TEACH_BEGIN;
            }
            break;

        case State::TEACH_BEGIN:
            break;

        case State::TEACH_RUN:
            if (mode != _mode) {
                //_mode
            }
            break;

        case State::TEACH_END:
            break;

        case State::EXERCISE:
            checkState(mode);
            break;

        case State::EXERCISE_BEGIN:
            break;

        case State::EXERCISE_RUN:
            break;

        case State::EXERCISE_END:
            break;

        case State::EVALUATE:
            checkState(mode);
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
        case State::NONE:           str = "NONE";           break;
        case State::TEACH:          str = "TEACH";          break;
        case State::TEACH_BEGIN:    str = "TEACH_BEGIN";    break;
        case State::TEACH_RUN:      str = "TEACH_RUN";      break;
        case State::TEACH_END:      str = "TEACH_END";      break;
        case State::EXERCISE:       str = "EXERCISE";       break;
        case State::EXERCISE_BEGIN: str = "EXERCISE_BEGIN"; break;
        case State::EXERCISE_RUN:   str = "EXERCISE_RUN";   break;
        case State::EXERCISE_END:   str = "EXERCISE_END";   break;
        case State::EVALUATE:       str = "EVALUATE";       break;
        case State::START:
        default:                    str = "START";          break;
    }
    return str;
}

void
StateMachine::checkState(Mode &mode)
{
    if (mode != _mode) {
        _currentState = nextState(mode);
    }
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
