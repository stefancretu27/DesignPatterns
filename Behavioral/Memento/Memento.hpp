#pragma once

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/*
* Provided Token and Mememnto structs, together with TokenMachine struct,
* it is required to implement add_token and revert methods such that they encapsulate
* the logic of memento. The add_token method receives as argument an shared_ptr so it
* is advised to take care to the cases when the shared_ptr is used externally to change the
* value, or redirected, whilst the method still created the snapshot.
*/

struct Token
{
    int value;

    Token(int value) : value(value) {};
};

struct Memento
{
    vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{
    vector<shared_ptr<Token>> tokens;

    vector<Memento> snapshots;
    size_t idxCurrentSnapshot{0};

    Memento add_token(int value)
    {
        return add_token(make_shared<Token>(value));
    }

    // adds the token to the set of tokens and returns the snapshot of the entire system
    Memento add_token(const shared_ptr<Token>& token)
    {
        Memento mementoInst{};
        
        if(token)
        {
            //push back with the value, not with the shared ptr whose value can be subsequently changed or can be redirected
            tokens.push_back(make_shared<Token>(token->value));
            
            //take a snapshot of the whole vector, whose state represents the whole system's state
            mementoInst.tokens = tokens;

            snapshots.push_back(mementoInst);
            ++idxCurrentSnapshot;
        }
        
        return mementoInst;
    };

    // reverts the system to a state represented by the token
    void revert(const Memento& m)
    {
        // leverage that the memento is immutable so the shared_ptr kept in its vector member 
        // are not used to change values. Moreover, they have been pushed by value, when added.
        tokens = m.tokens;

        //update index
        for(size_t idx{0}, len = snapshots.size(); idx < len; ++idx)
        {
            if(snapshots[idx].tokens == m.tokens)
            {
                idxCurrentSnapshot = idx;
            }
        } 
    };

    //goes back one snapshot
    Memento undo()
    {
        if(idxCurrentSnapshot > 0)
        {
            --idxCurrentSnapshot;

            //retrieve snapshot
            Memento snap = snapshots[idxCurrentSnapshot];

            tokens = snap.tokens;

            return snap;
        }
        return {};
    }

    //goes forward one snapshot
    Memento redo()
    {
        if(idxCurrentSnapshot + 1 < snapshots.size())
        {
            ++idxCurrentSnapshot;

            //retrieve snapshot
            Memento snap = snapshots[idxCurrentSnapshot];

            tokens = snap.tokens;

            return snap;
        }
        return {};
    }
};