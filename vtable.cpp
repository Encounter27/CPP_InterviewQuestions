/************************************************
 * Vtable Memory layout for Base and Drive class.
 * **********************************************/
#include<iostream>
#include<stdio.h>

using namespace std;

typedef void (*FunPTR)();

class Base 
{
	int id;
	public:

	Base(){ id = 100; }

	virtual void Fun1()
	{
		cout << "Base::Fun1" << endl;
	}
	virtual void Fun2()
	{
		cout << "Base::Fun2" << endl;
	}
};

class Derive: public Base
{
	public:

	virtual void Fun1()
	{
		cout << "Derive::Fun1" << endl;
	}
	virtual void Fun3()
	{
		cout << "Derive::Fun3" << endl;
	}
};

int main()
{

	/**************************************************
	Base clas Memory Layout.
	**************************************************/
	Base ob;

	int* vPtrBase = (int*)(&ob);
	cout << "Address of VPTR      = " << vPtrBase      << endl;
	cout << "Address of id        = " << vPtrBase+1    << endl;
	cout << "Value of id          = " << *(vPtrBase+1) << endl;

	int* vTableBase = (int*)(*vPtrBase);
	cout << "Address of vTableBase    = " <<  vTableBase   << endl;

	FunPTR Fun1Ptr = (FunPTR)*(vTableBase + 0);
	Fun1Ptr();

	FunPTR Fun2Ptr = (FunPTR)*(vTableBase + 1);
	Fun2Ptr();

	/**************************************************
	Derive clas Memory Layout.
	**************************************************/
	cout <<"-------------------------------------------\n";	
	Derive od;

	int* vPtrBaseDerive = (int*)(&od);
	cout << "Address of VPTR      = " << vPtrBaseDerive      << endl;
	cout << "Address of id        = " << vPtrBaseDerive+1    << endl;
	cout << "Value of id          = " << *(vPtrBaseDerive+1) << endl;

	int* vTableBaseDerive = (int*)(*vPtrBaseDerive);
	cout << "Address of vTableBase    = " <<  vTableBaseDerive   << endl;

	Fun1Ptr = (FunPTR)*(vTableBaseDerive + 0);
	Fun1Ptr();

	Fun2Ptr = (FunPTR)*(vTableBaseDerive + 1);
	Fun2Ptr();

	FunPTR Fun3Ptr = (FunPTR)*(vTableBaseDerive + 2);
	Fun3Ptr();

	return 0;
}

