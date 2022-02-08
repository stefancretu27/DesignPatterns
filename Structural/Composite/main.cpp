

#include "SingleValue_ManyValues.hpp"

/*
* The composite design pattern involves treating scalar and composed objects in a similar manner.
*
* Concretely, there are classes which model the smallest piece in the data set one works with (such as a node in a graph).
* Also, oftentimes are used classes that encapsulate collections of such pieces (vectors, lists etc), together with the former. 
* When working with these 2 types of classes, some operations can be treated the same way. That is, both the single piece class
* and the collection of pieces class could provided a similar API, but with corresponding implementations, that are distinct.
*
* The common interface methods are encapsulated in an interface class from which the above described 2 types of classes inherit
* and override. In some cases, this interface can be switched to a template base class, such that the overall structure follows 
* the CRTP idiom, with some methods specific to Derived types being called in this base class.
*
* This interface often encapsulates methods that overload begin() and end(), which are methods commonly used in STL containers
* for iterating over: for loops, range-based for loops (under the hood) etc. As the derived types override this methods, the
* types they model can be treated afterwards as containers when iterating over.
*/

int main()
{
    SingleValue single_value{1};
    SingleValue single_value2{2};
    
    ManyValues other_values{};
    other_values.add(2);
    other_values.add(3);
    
    cout<<sum({&single_value, &other_values, &single_value, &other_values})<<" "<<sum2({&single_value, &other_values, &single_value, &other_values})<<endl;

    cout<<sum({&single_value, &other_values})<<" "<<sum2({&single_value, &other_values})<<endl;
    
    cout<<sum({&other_values, &other_values})<<" "<<sum2({&other_values, &other_values})<<endl;
    
    ManyValues2 other_values2{};
    SingleValue single_value3{11};
    other_values2.add(22);
    other_values2.add(23);
    other_values2.add(single_value3.mValue);
    other_values2.add(other_values);

    cout<<sum3({&other_values2, &other_values2})<<" "<<sum({&other_values2, &other_values2})<<endl;
    cout<<sum3({&other_values, &other_values2})<<" "<<sum({&other_values, &other_values2})<<endl;
    cout<<sum3({&other_values, &single_value2, &other_values2})<<" "<<sum({&other_values, &single_value2, &other_values2})<<endl;

    return 0;
}
