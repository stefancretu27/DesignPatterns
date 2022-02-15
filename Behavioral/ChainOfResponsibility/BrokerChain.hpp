#pragma once

#include <vector>
using namespace std;

/*
* Given a mediator class Game that contains a vector of pointers to abstarct class Creature and the Struct that defines
* the layout for a query, the Creature takes a Goblin specialization. Goblin is extended further by GoblinKing;
* It is asked to implement virtual emthods get_attack and get_defense such that:
*    - each goblin takes +1 defense for each other goblin in game (including GoblinKing)
*    - each goblin takes +1 attack for each GoblinKing in game
* Goblin starts with (1, 1) by default, and GoblinKing with (3,3). 
*/

struct Creature;

//mediator: defines a chain of objects acting as a broker for computing attributes values that depend on the exitsence of other objects
struct Game
{
    vector<Creature*> creatures;
};

struct StatQuery
{
    enum Statistic { attack, defense } statistic;
    int result;
};

struct Creature
{
    protected:
        Game& game;
        int base_attack, base_defense;
    
    public:
        Creature(Game &game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
                                                                  base_defense(base_defense) {}
        virtual int get_attack() = 0;
        virtual int get_defense() = 0;

        //add a new virtual method that should eb overriden by Goblin and GoblinKing accordingly
        virtual void query(void* source, StatQuery& sq) = 0;
};

class Goblin : public Creature
{
    public:
        Goblin(Game &game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}
        
        Goblin(Game &game) : Creature(game, 1, 1) {}
        
        int get_attack() override 
        {
            //the result is stored internally in StatQuery, that has a given type
            StatQuery q{StatQuery::attack, 0};
            
            //iterate through the chain of objects and query each one, including self, using same query object
            //thus, each iterated object is queried for this object using each time the query defined above
            for(auto&& creature : game.creatures)
            {
                creature->query(this, q);
            }
                
            //return the result stored in the query object
            return q.result;
        }
        
        int get_defense() override 
        {
            //the result is stored internally in StatQuery, that has a given type
            StatQuery q{StatQuery::defense, 0};
            
            //iterate through the chain of objects and query each one, including self, using same query object
            //thus, each iterated object is queried for this object using each time the query defined above
            for(auto&& creature : game.creatures)
            {
                creature->query(this, q);
            }
                
            //return the result stored in the query object
            return q.result;
        }
        
        void query(void *source, StatQuery &sq) override 
        {
            //whem querying self, add to the result the values of self members
            if (source == this)
            {
              switch (sq.statistic)
              {
                case StatQuery::attack:
                  sq.result += base_attack;
                  break;
                case StatQuery::defense:
                  sq.result += base_defense;
                  break;
              }
            } 
            else
            {
                //when querying other obejcts, add +1 to defense,
                //as goblins get +1 defense for each goblin in play
                if (sq.statistic == StatQuery::defense)
                {
                    sq.result++;
                }
            }
        }
};

class GoblinKing : public Goblin
{
    public:
        GoblinKing(Game &game) : Goblin(game, 3, 3) {}
    
        //get_defense and get_attack are inherited the same from Goblin
        //it only differs how a query is built
        void query(void *source, StatQuery &sq) override 
        {
            // when querying other objects, add +1 to attack,
            // as goblins (including kings)  get +1 attack for each goblinKing in play
            if (source != this && sq.statistic == StatQuery::attack)
            {
                sq.result++;
            } 
            else
            {
                //appart from that, act as a regular goblin
                Goblin::query(source, sq);
            }
        }
};