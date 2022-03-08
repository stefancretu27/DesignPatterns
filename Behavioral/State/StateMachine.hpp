#pragma once

#include <map>
#include <utility>
#include <vector>
#include <iostream>


struct IDEStateMachine
{
    enum class State
    {
        Closed,
        Open,
        EditCode,
        CodeCompiled,
        CompilationFailed,
        BinariesLinked,
        LinkingFailed,
        RunBinaries
    };

    enum class Transition
    {
        None,
        Opening,
        Exiting,
        Editing,
        Compiling,
        Linking, 
        Running
    };

    friend std::ostream& operator<<(std::ostream& os, const State& t)
    {
        switch(t)
        {
            case State::Closed:
            {
                os << "Closed";
            }
            break;
            case State::Open:
            {
                os << "Open";
            }
            break;
            case State::EditCode:
            {
                os << "Edit code";
            }
            break;
            case State::CodeCompiled:
            {
                os << "Code compiled";
            }
            break;
            case State::CompilationFailed:
            {
                os << "Compilation Failed";
            }
            break;
            case State::BinariesLinked:
            {
                os << "Binaries Linked";
            }
            break;
            case State::LinkingFailed:
            {
                os << "Linking Failed";
            }
            break;
            case State::RunBinaries:
            {
                os << "Run Binaries";
            }
            break;
        }

        return os;
    };

    friend std::ostream& operator<<(std::ostream& os, const Transition& t)
    {
        switch(t)
        {
            case Transition::None:
            {
                os << "no transition";
            }
            break;
            case Transition::Opening:
            {
                os << "Opening";
            }
            break;
            case Transition::Exiting:
            {
                os << "Exiting";
            }
            break;
            case Transition::Editing:
            {
                os << "Editing";
            }
            break;
            case Transition::Compiling:
            {
                os << "Compiling";
            }
            break;
            case Transition::Linking:
            {
                os << "Linking";
            }
            break;
            case Transition::Running:
            {
                os << "Running";
            }
            break;
        }

        return os;
    };

    /*
    * Each listed state can be a start state. Hence, define which transitions are possible from that starting state
    * and to which state the transitions ends. Thus, there are considered pairs of Tranistions and end states and 
    * because there can be multiple possibilities, they are organized as vectors. Consequently each starting state
    * is mapped to a vector of pairs.
    */
    static std::map<State, std::vector<std::pair<Transition, State>>> rules;
    State currentState;
    Transition lastExecutedTransition;

    IDEStateMachine(): currentState{State::Closed}, lastExecutedTransition{Transition::None}{};

};