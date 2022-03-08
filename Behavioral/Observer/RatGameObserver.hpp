#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
* Given the classes Game (unimplemented at all) and Rat (inherits from nonimplemented interface), it is asked
* to implement them such that a Rat joins the game via c-tor end quits via d-tor. Each Rat has attack value = 1,
* but this value should be updated to the total numbe rof rats in game, when more rats join or quit.
*/

struct IRat
{
    virtual void setAttack(int value) = 0;
};

//Game acts as observer class
struct Game
{
    vector<IRat*> ratsInGame;
    
    //join and quit Game act as notifiers called from Rat class
    void ratJoined(IRat* sourceObject)
    {
        ratsInGame.push_back(sourceObject);
        
        for(IRat* rat : ratsInGame)
        {
            rat->setAttack(ratsInGame.size());
        }
    }
    
    void ratQuit(IRat* sourceObject)
    {
        //erase remove idiom
        ratsInGame.erase( remove_if( ratsInGame.begin(), 
                                     ratsInGame.end(), 
                                     [sourceObject](IRat* rat){return rat==sourceObject;}),
                         ratsInGame.end());
                         
        for(IRat* rat : ratsInGame)
        {
            rat->setAttack(ratsInGame.size());
        }
    }
};

//Rat class is observable
struct Rat : public IRat
{
    //game acts as observer
    Game& game;
    int attack{1};

    Rat(Game &game) : game(game)
    {
        game.ratJoined(this);
    }

    ~Rat() 
    { 
        game.ratQuit(this);
    }
    
    void setAttack(int value) override
    {
        attack = value;
    };
    
};