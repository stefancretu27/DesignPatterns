#include "Memento.hpp"

/*
* Memento is a design pattern which allows for keeping snapshots of a system with the scope
* of performing roll back and front operations between the recorded states. The states are 
* the result of a flow of operations that occur on the data members of a class/component.
* With each change, the resulted state is recorded so the changes can be tracked.
*
* Implementation wise it involves the creation of a separate class, called Memento, which
* encapsulates similar data members as the class for which it will hold snapshots. Then,
* in the snapshoted class, methods that modify its field values, also update the field values of the
* memento. In other terms, the memento acts as backup data storage.
* Then, these methods return a memento object, representing the current state. This object
* can be used afterwards to revert to its values (passed as an argument to a revert method).
*
*             ________________________________                       _________________________________________________________
*            |        struct Memento         |                       |             User class                                |
*            |                               |                       |                                                       |  
*            | string state;                 |    Uses               | vector<Memento> mementoSnapshots;                     |
*            |                               |<----------------------| string mData;                                         |
*            |                               |                       | size_t snapshotIndex{};                               |      
*            |_______________________________|                       |                                                       |
*                                                                    | Memento(const string& data):mData{data}               |  
*                                                                    | {    mementoSnapshots.push_back({data});              |
*                                                                    |       ++snapshotIndex;                                | 
*                                                                    | }                                                     |
*                                                                    |                                                       |
*                                                                    | void Revert(size_t snapIdx)                           |
*                                                                    | {mData = mementoSnapshots[snapIdx].state;             |
*                                                                    |    snapshotIndex = snapIdx;                           |
*                                                                    |                                                       |
*                                                                    | Memento UpdateData(const string& data)                |
*                                                                    | { mData = data;                                       |
*                                                                    |   ++snapshotIndex;                                    |
*                                                                    |   Memento result{{data}};                             |   
*                                                                    |   mementoSnapshots.push_back(result);                 |
*                                                                    |   return result;}                                     |
*                                                                    |                                                       |
*                                                                    | void Revert(Memento& snapshot)                        |
*                                                                    | {for(auto idx{}; idx<mementoSnapshots.size(); ++idx)  |
*                                                                    |        if(snap==snapshot)                             |
*                                                                    |        {  mData = snap.state;                         |
*                                                                    |            snapshotIndex = idx;}}                     |
*                                                                    |_______________________________________________________| 
*       
*
* The Memento class does not implement methods that can change the stored snapshots. A memento
* object is immutable and not to be used for performing changes on data it stores.
*
* These methods can be instructed to return a snapshot but, additionally, the snapshoted class
* can encapsulate a container of Memento, where all changes are recorded. In this regard, 
* an index can be kept, so it can identify a particular snapshot. This logic can be either
* included in memento class, with the container holding pointers to Memento. Then, the container
* is used to implement undo and redo operations.
*
* Even more, a particular implementation of the pattern, uses do operations in c-tor and the undo
* in its d-tor, such that when memento object is created within a scope block, it performs these
* operations automatically, on the object passed as argument to c-tor.
*
* The pattern can be regarded as an alternative to Command, but without defining, thus restricting,
* to a particular set of operations.
*/

int main()
{
    TokenMachine tkMachine{};

    Memento m1 = tkMachine.add_token(5);
    Memento m2 = tkMachine.add_token(23);
    Memento m3 = tkMachine.add_token(-7);

    cout<<"current state: ";
    for(auto&& spToken : tkMachine.tokens)
    {
        cout<<spToken->value<<" ";
    }

    cout<<endl<<" after revert to m1 memento: ";
    tkMachine.revert(m1);
    for(auto&& spToken : tkMachine.tokens)
    {
        cout<<spToken->value<<" ";
    }

    cout<<endl<<" after revert to m3 memento: ";
    tkMachine.revert(m3);
    for(auto&& spToken : tkMachine.tokens)
    {
        cout<<spToken->value<<" ";
    }

    cout<<endl<<" after undo: ";
    Memento mUndo = tkMachine.undo();
    for(auto&& spToken : tkMachine.tokens)
    {
        cout<<spToken->value<<" ";
    }
    cout<<" Index of current snapshot: "<<tkMachine.idxCurrentSnapshot<<endl;

    cout<<endl<<" after redo: ";
    Memento mRedo = tkMachine.redo();
    for(auto&& spToken : tkMachine.tokens)
    {
        cout<<spToken->value<<" ";
    }
    cout<<" Index of current snapshot: "<<tkMachine.idxCurrentSnapshot<<endl;

    return 0;
}
