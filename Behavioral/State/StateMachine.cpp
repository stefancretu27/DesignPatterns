#include "StateMachine.hpp"

using namespace std;

//map canbe initialized globally only upon definition
map<IDEStateMachine::State, vector<pair<IDEStateMachine::Transition, IDEStateMachine::State>>> IDEStateMachine::rules
{
    {IDEStateMachine::State::Closed, {{IDEStateMachine::Transition::Opening, IDEStateMachine::State::Open}}
    },

    {IDEStateMachine::State::Open,  { {IDEStateMachine::Transition::Exiting, IDEStateMachine::State::Closed},
                                      {IDEStateMachine::Transition::Editing, IDEStateMachine::State::EditCode}
                                    }
    },

    {IDEStateMachine::State::EditCode, {{IDEStateMachine::Transition::Exiting, IDEStateMachine::State::Closed},
                                        {IDEStateMachine::Transition::Editing, IDEStateMachine::State::EditCode},
                                        {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CodeCompiled},
                                        {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CompilationFailed}
                                        }
    },

    {IDEStateMachine::State::CodeCompiled, { {IDEStateMachine::Transition::Exiting, IDEStateMachine::State::Closed},
                                            {IDEStateMachine::Transition::Editing, IDEStateMachine::State::EditCode},
                                            {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CodeCompiled},
                                            {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CompilationFailed},
                                            {IDEStateMachine::Transition::Linking, IDEStateMachine::State::BinariesLinked},
                                            {IDEStateMachine::Transition::Linking, IDEStateMachine::State::LinkingFailed}
                                           }
    },

    {IDEStateMachine::State::CompilationFailed, {   {IDEStateMachine::Transition::Exiting, IDEStateMachine::State::Closed},
                                                    {IDEStateMachine::Transition::Editing, IDEStateMachine::State::EditCode},
                                                    {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CompilationFailed}
                                                }
    },

    {IDEStateMachine::State::BinariesLinked, {  {IDEStateMachine::Transition::Exiting, IDEStateMachine::State::Closed},
                                                {IDEStateMachine::Transition::Editing, IDEStateMachine::State::EditCode},
                                                {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CodeCompiled},
                                                {IDEStateMachine::Transition::Linking, IDEStateMachine::State::BinariesLinked},
                                                {IDEStateMachine::Transition::Running, IDEStateMachine::State::RunBinaries}
                                             }
    },

    {IDEStateMachine::State::LinkingFailed, {   {IDEStateMachine::Transition::Exiting, IDEStateMachine::State::Closed},
                                                {IDEStateMachine::Transition::Editing, IDEStateMachine::State::EditCode},
                                                {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CodeCompiled},
                                                {IDEStateMachine::Transition::Linking, IDEStateMachine::State::LinkingFailed}
                                            }
    },

    {IDEStateMachine::State::RunBinaries, { {IDEStateMachine::Transition::Exiting, IDEStateMachine::State::Closed},
                                            {IDEStateMachine::Transition::Editing, IDEStateMachine::State::EditCode},
                                            {IDEStateMachine::Transition::Compiling, IDEStateMachine::State::CodeCompiled},
                                            {IDEStateMachine::Transition::Linking, IDEStateMachine::State::BinariesLinked},
                                            {IDEStateMachine::Transition::Running, IDEStateMachine::State::RunBinaries}
                                          }
    }
};