#pragma once

#include <iostream>
#include <vector>

using namespace std;

/*
* Given the class Particiant which implement IParticipant interface and uses Mediator class, both not implemented,
* it is required to implement say method such that when a participant vroadcasts a value, all other participants
* increment their value by that amount.
*/

struct IParticipant
{
    virtual void incrementValue(const int amount) = 0;
    virtual int getValue() const = 0;
};

struct Mediator
{
    vector<IParticipant*> participants;
    
    void broadcast(const int val, IParticipant* source)
    {
        for(IParticipant* p : participants)
        {
            if(p != source)
            {
                p->incrementValue(val);
            }
        }
    }

    void printMessageLog()
    {
        static size_t participantID{0};

        for(IParticipant* ip : participants)
        {
            cout<<"ParticipantId: "<<++participantID<<" value: "<<ip->getValue()<<endl;
        }
    }
};

struct Participant : IParticipant
{
    int value{0};
    Mediator& mediator;

    Participant(Mediator &mediator) : mediator(mediator)
    {
      mediator.participants.push_back(this);
    }

    void say(int value)
    {
        mediator.broadcast(value, this);
    }
    
    void incrementValue(const int amount) override
    {
        value += amount;
    }

    int getValue() const override
    {
        return value;
    }
};

