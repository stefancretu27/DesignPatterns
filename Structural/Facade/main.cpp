#include <iostream>
#include <string>

using namespace std;

/*
* Brief description: Provides a simplified interface to a set of interfaces
*
* Use Case:
*  Simplified access to a complex system
*  A complex system contains many dependencies which are decoupled through the facade
*  Introduction of layers within a complex system; the layer help to decouple the complex system
*
* Facade involves creating a simplified interface to a more complex implementation (that can 
* involve multiple classes, interfaces, which can be disposed in layers) while delegating
* (wrapping) calls/requests to the implementation itself.
*
* Implementation-wise, it involves creating a separate interface/class whose emthods wrap
* calls to the interfaces/classes composing the facaed implementation. For this purpose,
* The Facade interface/class should encapsulate refs/ptrs to those interfaces/classes
* so it can perform the calls on the injected dependencies.
*
**                                    ____________________________________
*                                    |           Facade interface -      |
*                                    | wraps calls to interfaces/classes |
*                                    | from the complex subsystem        |
*                                    |                                   |
*                                    | Interface mRef2;                  |
*                                    | Interface mRef1;                  |
*                                    |                                   |
*                                    | void Wrapper()                    |
*                                    |  {mRef1.Method();                 |
*                                    |    mRef2.OtherMethod();}          |
*                                    |___________________________________|
*                                       /                          \
*                                      /  inheritance               \    inheritance
*                  ___________________/________               ________\______________________________
*                  |    Interface 1  -        |              |          Interface2                  |
*                  | initial implementation of|              |  implementing the common interface   |  
*                  | the exposed interface    |              |                                      |         
*                  |                          |              |   void OtherMethod()                 |
*                  |  void Method()           |              |    { doOtherWork();                  | 
*                  |    {doWork();}           |              |      doMoreWork(); }                 |  
*                  |__________________________|              |______________________________________|
*                                                            
*
*/


class Alarm                                                            // (2) 
{
public:
	void alarmOn()
	{
		cout << "Alarm is on and house is secured"<<endl;
	}

	void alarmOff()
	{
		cout << "Alarm is off and you can go into the house"<<endl;
	}
};

class Ac                                                              // (3)
{
public:
	void acOn()
	{
		cout << "Ac is on"<<endl;
	}

	void acOff()
	{
		cout << "AC is off"<<endl;
	}
};

class Tv                                                              // (4)
{
public:
	void tvOn()
	{
		cout << "Tv is on"<<endl;
	}

	void tvOff()
	{
		cout << "TV is off"<<endl;
	}
};

class HouseFacade                                                    // (1)
{
	Alarm alarm;
	Ac ac;
	Tv tv;

public:
	HouseFacade(){}

	void goToWork()                                              // ( 
	{
		ac.acOff();
		tv.tvOff();
		alarm.alarmOn();
	}

	void comeHome()                                             // (5)       Facade 
	{
		alarm.alarmOff();
		ac.acOn();
		tv.tvOn();
	}
};

int main()
{
	HouseFacade hf;

	//Rather than calling 100 different on and off functions thanks to facade I only have 2 functions...
	hf.goToWork();
	hf.comeHome();
}
