#include "NodeTraversals.hpp"

#include <map>
#include <utility>

template<class T>
void Node<T>::preorderTraversal(vector<Node<T>*>& result)
{
    /*
    * If the input vector is empty, it means the root node has not been added.
    * In preorder travrsel, the root node is always the first, thus push it to the vector and
    * continue processing recursively.
    */
    if(result.empty())
    {
        result.push_back(this);
        preorderTraversal(result);
    }
    /*
    *  If the result input vector is not empty, take the last node, which was previously added,
    * and check if it has any chldren nodes, in the order left first and right the last. When
    * such a child node is found, push it to the result vector and continue processing recursively.
    */
    else
    {
        Node<T>* pred = result.back();
        if(pred->left) 
        {
            result.push_back(pred->left);
            preorderTraversal(result);
        }
        if(pred->right)
        {
            result.push_back(pred->right);
            preorderTraversal(result);
        }
    }
}

template<class T>
void Node<T>::postorderTraversal(vector<Node<T>*>& result)
{
    enum class NodeType:uint16_t
    {
        Parent,
        Left, 
        Right
    };

    //the first node to be added to result is the leftmost. 
    static NodeType lastPushedNodeType{NodeType::Parent};

    if(result.empty())
    {
        //find the leftmost node
        Node* currentNode = this;
        while(currentNode->left)
        {
            currentNode = currentNode->left;
        }

        /*
        * Set its node type and push it to the result. At this point, it is known it has no further left branch,
        * but it was not determined if it has right child node. This is done in the next iteration
        * */
        lastPushedNodeType = NodeType::Left;
        result.push_back(currentNode);
        postorderTraversal(result);
    }
    else
    {
        Node<T>* pred = result.back();
        
        if(lastPushedNodeType == NodeType::Left)
        {
            /*
            * If the last pushed node has left type, check if it has right child node. 
            * If so, remove the last node in the result vector and push back its right child node.
            */
            if(pred->right)
            {
                result.pop_back();
                result.push_back(pred->right);
                lastPushedNodeType = NodeType::Right;
            }
            /*
            * Otherwise, check if there is a right node having the same parent. If so, push this right node.
            * If not, push the parent node whose node type is set to parent, meaning it should not be further
            * examined for downmost branches
            */
            else if(pred->parent)
            {
                if(pred->parent->right) 
                {
                    result.push_back(pred->parent->right);
                    lastPushedNodeType = NodeType::Right;

                }
                else
                {
                    result.push_back(pred->parent);
                    lastPushedNodeType = NodeType::Parent;
                }
            }

            postorderTraversal(result);
        }
        else if(lastPushedNodeType == NodeType::Right)
        {
            /*
            * If the last psuhed node is a right node, firstly check if it has any left branch
            */
            Node* currentNode = pred;
            while(currentNode->left)
            {
                currentNode = currentNode->left;
            }

            /* If there is a left branch, add the leftmost found child node as left node, after
            * popping the lastly added node, then continue processing recursively
            */
            if(currentNode != pred)
            {
                result.pop_back();
                result.push_back(currentNode);
                lastPushedNodeType = NodeType::Left;
            }
            /*
            * Otherwise, check if it has right child node. 
            * If so, remove the last node in the result vector and push back its right child node.
            */
            else if(pred->right)
            {
                result.pop_back();
                result.push_back(pred->right);
                lastPushedNodeType = NodeType::Right;
            }
            /*
            * If the lastly added node is a right node who does not have any children nodes
            * just add its parent to the result.
            */
            else
            {
                result.push_back(pred->parent);
                lastPushedNodeType = NodeType::Parent;
            }

            postorderTraversal(result);
        }
        /*
        * If the last added node is a parent, it means its child nodes were previously pushed. Thus,
        * it is only examined id it has a parent node in its turn. If so, firstly check if its parent 
        * node has a right child node (aka if the previously added node is a left node) and push it
        * to the result. If the parent node does not have a right child node, then push that parent node.
        * If the previously added node is a parent with no parent, the algorithm stops as it means the root 
        * node has been processed.
        */
        else if(lastPushedNodeType == NodeType::Parent)
        {
            if(pred->parent)
            {
                if(pred->parent->right && pred->parent->right != pred) 
                {
                    result.push_back(pred->parent->right);
                    lastPushedNodeType = NodeType::Right;

                }
                else
                {
                    result.push_back(pred->parent);
                    lastPushedNodeType = NodeType::Parent;
                }

                //continue recursive processing ony if pred has a parent
                postorderTraversal(result);
            }
        }
    }
}

template<class T>
void Node<T>::inorderTraversal(vector<Node<T>*>& result)
{
    enum class NodeType:uint16_t
    {
        Parent,
        Left, 
        Right
    };

    //the first node to be added to result is the leftmost. 
    static NodeType lastPushedNodeType{NodeType::Parent};
    static map<Node*, bool> exploredParentNodes{};

    if(result.empty())
    {
        //find the leftmost node
        Node* currentNode = this;
        while(currentNode->left)
        {
            currentNode = currentNode->left;
        }

        /*
        * Set its node type and push it to the result. At this point, it is known it has no further left branch,
        * but it was not determined if it has right child node. This is done in the next iteration
        * */
        lastPushedNodeType = NodeType::Left;
        result.push_back(currentNode);
        inorderTraversal(result);
    }
    else
    {
        Node<T>* pred = result.back();
        
        if(lastPushedNodeType == NodeType::Left)
        {
            /*
            * If the last pushed node is left type, it has no left child node for sure. However,
            * it is not known if it has a right child node. If so, push its child to result
            * vector. Also, set the last added node's type to right.
            */
            if(pred->right)
            {
                result.push_back(pred->right);
                lastPushedNodeType = NodeType::Right;
            }
            /*
            * Otherwise, it means that the previously added left node has no child nodes. In this case
            * check if it has a parent and push it to the result vector. Also, set last pushed node type
            * to parent.
            */
           else if(pred->parent && exploredParentNodes.find(pred->parent) == exploredParentNodes.end())
           {
                result.push_back(pred->parent);
                lastPushedNodeType = NodeType::Parent;
                //mark the parent node was added, as it won't be removed afterwards
                exploredParentNodes.emplace(make_pair(pred->parent, true));
           }

            // continue the processing recursively
           inorderTraversal(result);
        }
        else if(lastPushedNodeType == NodeType::Right)
        {
            /*
            * If the previously pushed node has right type, check if it has a left child.
            */
            Node* currentNode = pred;
            while(currentNode->left)
            {
                currentNode = currentNode->left;
            }

            /* 
            * If there is a left branch, add the leftmost found child node as left node, after
            * popping the lastly added node, then continue processing recursively.
            */
            if(currentNode != pred)
            {
                result.pop_back();
                result.push_back(currentNode);
                lastPushedNodeType = NodeType::Left;
            }
            /*
            * If it does not have a left child, but has a right child, simply push the right
            * child to the result vector.
            */
            else if(pred->right)
            {
                result.push_back(pred->right);
                lastPushedNodeType = NodeType::Right;

                //check if it has been marked as an added parent node
                if(exploredParentNodes.find(pred) == exploredParentNodes.end())
                {
                    exploredParentNodes[pred]=true;
                }
            }
            /*
            * If the last added node is a right node who does not have any child nodes,
            * check if it has a parent who has been marked as an added parent node. If not, mark it as an added
            * parent node. Then go up in the tree, from parent node to parent node till encountering a node
            * whose parent has not been checked yet. If so, add its parent and continue processing recursively
            */
            else
            {
                Node* currentNode = pred;

                if(currentNode->parent)
                {
                    if(exploredParentNodes.find(currentNode->parent) == exploredParentNodes.end())
                    {
                        exploredParentNodes[currentNode->parent]=true;
                    }
                }

                while(currentNode->parent && exploredParentNodes.find(currentNode->parent) != exploredParentNodes.end())
                {
                    currentNode = currentNode->parent;  
                }

                result.push_back(currentNode->parent);
                lastPushedNodeType = NodeType::Parent;
                exploredParentNodes[currentNode->parent]=true;
            }

            // continue the processing recursively
            inorderTraversal(result); 
        }
        /*
        * If the last added node has parent type, it clearly means it was pushed after a left node was pushed.
        * Thus, 2 situations can occur here: either the parent node has a right child node which has to be pushed,
        * or it does not have a right child, but has a parent which also shall be pushed. In the second situation,
        * the previously added parent node acts as a left node. If none of this situations is encountered, the 
        * algorithm stops.
        */
        else if(lastPushedNodeType == NodeType::Parent)
        {
            if(pred->right)
            {
                result.push_back(pred->right);
                lastPushedNodeType = NodeType::Right;

                // continue the processing recursively
                inorderTraversal(result);
            }
            else if (pred->parent && exploredParentNodes.find(pred->parent) == exploredParentNodes.end())
            {
                result.push_back(pred->parent);
                lastPushedNodeType = NodeType::Parent;
                //mark the parent node was added, as it won't be removed afterwards
                exploredParentNodes.emplace(make_pair(pred->parent, true));

                // continue the processing recursively
                inorderTraversal(result);
            }

            //otherwise do not continue recursive processing as the root node has been achieved
        }
    }
}