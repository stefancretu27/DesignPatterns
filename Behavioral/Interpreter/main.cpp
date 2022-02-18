#include "ExpressionProcessor.hpp"

int main()
{
    ExpressionProcessor ep;
    
    double result = ep.Calculate("1+24-8+3-21");
    cout<<result<<endl;

    result = ep.Calculate("1+2+xy");
    cout<<result<<endl;

    ep.variables['x'] = 3;
    result = ep.Calculate("10-2-x");
    cout<<result<<endl;

    result = ep.Calculate("1");
    cout<<result<<endl;

    ep.variables['y'] = 8;
    result = ep.Calculate("-y");
    cout<<result<<endl;

    ep.variables['z'] = -8.2;
    result = ep.Calculate("z - 2 + 3.5 + 15.15");
    cout<<result<<endl;

    result = ep.Calculate("2/");
    cout<<result<<endl;

    result = ep.Calculate("23.56+1.2");
    cout<<result<<endl;

    result = ep.Calculate("1+3*2/1-2.5+4/2+1.5");
    cout<<result<<endl;

    result = ep.Calculate("2/2+3.9-4.5/3");
    cout<<result<<endl;

    return 0;
}