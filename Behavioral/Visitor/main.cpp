#include "DoubleDispatchVisitor.hpp"
#include "STD_Variant_Visit.hpp"

#include <vector>
#include <variant>


int main()
{
    Value v2{2};
    Value v3{3};
    Value v4{4};
    AdditionExpression addExpr{v2, v3};
    MultiplicationExpression mulExpr(v4, addExpr);
    AdditionExpression add2(mulExpr, mulExpr);

    ExpressionPrinter expPrint{};
    expPrint.visit(add2);
    cout<<expPrint.str()<<endl;


    cout<<"variant and visit"<<endl;
    variant<int, double, char, float*> var;

    float* ptrF = new float{2.7182};
    var = ptrF;
    cout<<*get<float*>(var)<<endl;

    var = 17;
    cout<<get<0>(var)<<endl;

    //create a vector whose each element is an alternative of a variant. This way it ca ne created a vector
    // holding distinct value types, as its template argument is variant
    vector<variant<int, double, char, string>> vec {10, 3.1415, '%', "hello"};
    for(auto&& alternative: vec) 
    {
        visit([](auto&& arg){std::cout << arg << " ";}, alternative);
    }

    //using functor
    cout<<endl<<"use functor"<<endl;
    for(auto&& alternative: vec) 
    {
        visit(Functor(), alternative);
    }

    return 0;
}