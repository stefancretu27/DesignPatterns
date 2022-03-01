#include "NodeTraversals.hpp"
#include "IterableClass.hpp"
#include <string>


/*
* Iterator is a design pattern involving the implementation of a template class (Iterator<T>)
* which is used for traversing data structures, especially those own defined (not off the shelf).
* They are provided by STL and are implicitly used in for ranged loops.
*
* In its sense, it hold a pointer to the current element in the data structure. In this regard,
* its interface should overload, at least, ++ and != operators in order to offers support required
* by for loops.
* Additionaly, class T that iterator is supposed to work on must implement begin() and end()
* methods, so it becomes iterable
*/

int main()
{
    Node<string> root{"A"};
    Node<string> n1{"B", &root}, n2{"C", &root};
    Node<string> n3{"D", &n1}, n4{"E", &n1};
    Node<string> n5{"F", &n2};
    Node<string> n6{"G"}, n7{"H"}, n8{"I"}, n9{"J"}, n10{"K"};
    n3.setAsRightNode(&n6);
    n6.setAsLeftNode(&n7);
    n7.setAsRightNode(&n8);
    n3.setAsLeftNode(&n9);
    n6.setAsRightNode(&n10);

    cout<<endl<<"classic binary tree recursive preorder traversal "<<endl;
    classicPreOrderTraversal(&root);

    cout<<endl<<"binary tree recursive preorder traversal with nodes being pushed to input vector "<<endl;
    vector<Node<string>*> result;
    root.preorderTraversal(result);
    for(Node<string>* n : result)
    {
        cout<< n->value << " ";
    }

    cout<<endl<<"classic binary tree recursive postorder traversal "<<endl;
    classicPostOrderTraversal(&root);

    cout<<endl<<"binary tree recursive postorder traversal with nodes being pushed to input vector "<<endl;
    vector<Node<string>*> result2;
    root.postorderTraversal(result2);
    for(Node<string>* n : result2)
    {
        cout<< n->value << " ";
    }

    cout<<endl<<"classic binary tree recursive inorder traversal "<<endl;
    classicInOrderTraversal(&root);

    cout<<endl<<"binary tree recursive inorder traversal with nodes being pushed to input vector "<<endl;
    vector<Node<string>*> result3;
    root.inorderTraversal(result3);
    for(Node<string>* n : result3)
    {
        cout<< n->value << " ";
    }

    cout<<endl<<" BFS output "<<endl;
    BFS(&root);



    cout<<endl<<" IterableClass and IteratorClass"<<endl;
    IterableClass<int> intBuffer{2};
    intBuffer.addElementBack(0, 4);
    intBuffer.addElementBack(1, 3);
    intBuffer.addElementBack(2, 2);
    intBuffer.addElementBack(3, 1);
    IterableClass<int> copy{intBuffer};
    intBuffer.addElementsBack({9, 6, 8, 7});

    for( auto&& elem : intBuffer)
        cout<<elem<<" ";

    cout<<endl;
    for( auto&& elem : copy)
        cout<<elem<<" ";

    copy = intBuffer;
    cout<<endl;
    for( auto&& elem : copy)
        cout<<elem<<" ";

    cout<<endl;
    IterableClass<int>::iterator it = intBuffer.begin();
    cout<<*it<<endl;

    for(IterableClass<int>::iterator iter{intBuffer.begin()}; iter != intBuffer.end(); ++iter)
        cout<<*iter<<" ";

    return 0;
}