#pragma once

#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct Node
{
    T value;
    Node *left{nullptr}, *right{nullptr}, *parent{nullptr};

    Node(T value) : value(value) {};

    Node(const T& val, Node<T>* par) : value{val}, parent{par}
    {
        if(!parent->left)
        {
            parent->left = this;
        }
        else if(parent->left && !parent->right)
        {
            parent->right = this;
        }
    }

    Node(const T& value, Node<T>* left, Node<T>* right) : value(value), left(left), right(right) 
    {
        left->parent = right->parent = this;
    }

    void setAsRightNode(Node<T>* rightNode)
    {
        if(!right)
        {
            right = rightNode;
            rightNode->parent = this;
        }
    }

    void setAsLeftNode(Node<T>* leftNode)
    {
        if(!left)
        {
            left = leftNode;
            leftNode->parent = this;
        }
    }

    // The methods beneath represent the modalities of implementing DFS tree algorithms, which aim at traversing
    // the nodes of a tree by firstly exploring the lowest level nodes.
    // There are 3 methods traverse the node and its children and put all the results into `result`
    // Also, each one has a classic traversial friend counterpart, used to compare the results.
    //        A
    //       / \
    //      B   C
    //     / \  /
    //    D   E F
    //   / \
    //  J   G
    //     / \
    //    H   K
    //     \
    //      I

    /*
    *  Preorder traversal: take an input root node and go through its leftmost branches. It has root->left->right strategy
    *  that is, when a node is examined, it is visited firstly, then its left child is checked recursively, lastly its right child.
    * eg: A->B->D->J->G->H->I->K->E->C->F
    */
   friend void classicPreOrderTraversal(Node<T>* startNode)
    {
        if(!startNode)
        {
            return;
        }

        cout<<startNode->value<<" ";
        classicPreOrderTraversal(startNode->left);
        classicPreOrderTraversal(startNode->right);
    }

    void preorderTraversal(vector<Node<T>*>& result);


    /*
    * Postorder traversal: take an input root node and go through its leftmost, bottom up branches. It has Left->Right->Root strategy
    * that is, when a node is examined, its left child is examined recursively, then its right child and lastly the node is visited
    * eg: J->I->H->K->G->D->E->B->F->C->A
    */
    friend void classicPostOrderTraversal(Node<T>* startNode)
    {
        if(!startNode)
        {
            return;
        }

        classicPostOrderTraversal(startNode->left);
        classicPostOrderTraversal(startNode->right);

        cout<<startNode->value<<" ";
    }

    void postorderTraversal(vector<Node<T>*>& result);
    

    /*
    *  Inorder traversal: take an input root node and go through its leftmost branches. It has left->root->right strategy
    *  that is, when a node is examined, its left child is firstly checked recursively, then the node is visited and
    *  lastly its right child is recursively checked.
    * eg: A->B->D->J->G->H->I->K->E->C->F
    */
    friend void classicInOrderTraversal(Node<T>* startNode)
    {
        if(!startNode)
        {
            return;
        }

        classicInOrderTraversal(startNode->left);
        cout<<startNode->value<<" ";
        classicInOrderTraversal(startNode->right);
    }

    void inorderTraversal(vector<Node<T>*>& result);

    /*
    * Breadth-fiurst search goes from top to bottom, but, at each level it explores all
    * the nodes from left to right.
    */
    friend size_t treeHeight(Node<T>* startNode)
    {
        if(!startNode)
        {
            return 0;
        }

        // for the end nodes these will be both 0
        size_t lheight = treeHeight(startNode->left);
        size_t rheight = treeHeight(startNode->right);

        /*
        * Increase by one when returning from each level, so the current level is counted as well.
        * At each level, it is checked whether its left or right branch is longer than the other one
        * and the longest is icnremented and returned.
        * As both values are 0 for end nodes, it will be returned 1 on else branch.
        * */
        if(lheight > rheight)
            return lheight + 1;
        else 
            return rheight + 1; 
    }

    /* 
    * This function is called for in order to get to the desired level in the tree. In order to do so, irt is
    * invoked in a for loop that provides the level input, which tells how many recursive calls will be performed. 
    * At each recursive call, the function  goes further down in the tree till level decreases to 1. 
    * As the starting point is  the root node, this is a traversal approach in this situation.
    */
    friend void currentLevelBFS(Node<T>* startNode, size_t levelsToGoDown)
    {
        if(!startNode)
        {
            return;
        }

        if(levelsToGoDown == 1)
        {
            cout<< startNode->value <<" ";
        }
        else if(levelsToGoDown > 1)
        {
            currentLevelBFS(startNode->left, levelsToGoDown-1);
            currentLevelBFS(startNode->right, levelsToGoDown-1);
        }
    }

    friend void BFS(Node<T>* startNode)
    {
        auto height = treeHeight(startNode);

        //loop which tell the function how many levels it should go down in the tree
        for(size_t idx{1}; idx < height; ++idx)
        {
            currentLevelBFS(startNode, idx);
        }
    }
};