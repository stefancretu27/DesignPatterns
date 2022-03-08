#include "State.hpp"

#include "StateMachine.hpp"

/*
* Almost all objects can hold state, if they have attributes. A change in state is equivalent tot eh change of the value
* of at least one of the object's attributes. The change of state can be explicit (a result of assignment) or a result of
* a notification (as in Observer) or a command.
*
* A handmade implementation of a state machine involves defining all possible states as an enum, and all possible transitions,
* as another enum. Then, from each state can eb transitioned to at least another state (be it the same one). A particular transition
* goes to another, singular state. Hence, for each state there is at least one pair {Transition, State} that is possible for
* execution. Therefore, each State is associated with a vector of such pair, so it can record all possible transitions and end
* states for a particular state. Thus, all possible actions are recorded as a map<State, vector<pair<Transition, State>>>
*/

int main()
{
    CombinationLock c1({1,2,3});
    cout<<c1.status<<endl;
    
    c1.enter_digit(1);
    cout<<c1.status<<endl;
    
    c1.enter_digit(2);
    cout<<c1.status<<endl;
    
    c1.enter_digit(3);
    cout<<c1.status<<endl;

    IDEStateMachine ide{};

    int transitionOption;
    while(true)
    {
        cout<< "Current state: "<< ide.currentState<<endl;

        size_t idx{0};

        for(auto&& pairTransitionState : ide.rules[ide.currentState])
        {
            cout<<"     Possible transition: "<<pairTransitionState.first<<" has index: "<<++idx<<endl;
        }

        cout<<" Enter transition option: "<<endl;
        cin>>transitionOption;

        if(transitionOption < 1 || transitionOption > ide.rules[ide.currentState].size())
        {
            break;
        }

        ide.lastExecutedTransition = ide.rules[ide.currentState][transitionOption-1].first;
        ide.currentState = ide.rules[ide.currentState][transitionOption-11].second;
    }
    
    return 0;
}