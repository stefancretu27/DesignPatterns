#pragma once

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
using namespace std;

struct Creature
{
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health) {}
};

struct CardGame
{
    vector<Creature> creatures;

    CardGame(const vector<Creature> &creatures) : creatures(creatures) {}

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2)
    {
        //simulate battle, as each creatures hits one another
        hit(creatures[creature1], creatures[creature2]);
        hit(creatures[creature2], creatures[creature1]);
        
        
        int result;
        
        if(creatures[creature1].health > 0 && creatures[creature2].health <=0)
        {
            result = creature1;
        }
        else if(creatures[creature2].health > 0 && creatures[creature1].health <=0)
        {
            result = creature2;
        }
        else
        {
            result = -1;
        }
        
        return result;
    }

    virtual void hit(Creature& attacker, Creature& other) = 0;
};

struct TemporaryCardDamageGame : CardGame
{
    TemporaryCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override 
    {
      int initialHealth = other.health;
      
      other.health -= attacker.attack;
      
      if(other.health > 0)
      {
          other.health = initialHealth;
      }
    }
};

struct PermanentCardDamageGame : CardGame
{
    PermanentCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override
    {
        if(other.health > 0)
        {
            other.health -= attacker.attack;
        }
    }
};