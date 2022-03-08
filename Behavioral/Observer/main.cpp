#include "RatGameObserver.hpp"

#include "Observer.hpp"

int main()
{
    MyObservableClass obj{3};
    MyObserver observer{};

    obj.subscribe(observer);
    obj.setValue(7);
    return 0;
}