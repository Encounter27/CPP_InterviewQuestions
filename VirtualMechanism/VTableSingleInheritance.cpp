/************************************************
 * Vtable Memory layout for Base and Drive class.
 * **********************************************/
#include<iostream>
#include<stdio.h>

using namespace std;

typedef void (*FunPTR)();

class Base
{
		int m_base1;
		int m_base2;

	public:
		Base()
		{
			m_base1 = 100;
			m_base2 = 200;	   
		}

		virtual void Fun1()
		{
			cout << "| Base::Fun1   |" << endl;
		}

		virtual void Fun2()
		{
			cout << "| Base::Fun2   |" << endl;
		}
};

class Derive: public Base
{
		int m_derive1;
		int m_derive2;

	public:
		Derive()
		{
			m_derive1 = 300;
			m_derive2 = 400;
		}

		virtual void Fun1()
		{
			cout << "| Derive::Fun1 |" << endl;
		}

		virtual void Fun3()
		{
			cout << "| Derive::Fun3 |" << endl;
		}
};

int main()
{
	Base ob;
	int* vPtrBase = (int*)(&ob);
	int* vTableBase = (int*)(*vPtrBase);

	cout << "\n\n Base clas Memory Layout:-\n\n";

	cout << "       --------\n";
	cout << " +-->>|  VPTR  |<--- " << vPtrBase << "[&ob]" << endl;
	cout << " |     --------\n";
	cout << " |    |m_base1 |<--- " << vPtrBase+1 <<'['<<*(vPtrBase + 1) <<"]\n";
	cout << " |     --------\n";
	cout << " |    |m_base2 |<--- " << vPtrBase+2 <<'['<<*(vPtrBase + 2) <<"]\n";
	cout << " |     --------\n";

	cout << " |\n |\n |                           VTable of Base\n | \n";

	FunPTR Fun1Ptr = (FunPTR)*(vTableBase + 0);
	cout << " |                           ---------------\n";
	cout << " +-->> *VPTR-----> "<< vTableBase;
   	Fun1Ptr();
	cout << "                             ---------------\n";
	cout << "                   ";
	cout << vTableBase+1;
	FunPTR Fun2Ptr = (FunPTR)*(vTableBase + 1);
	Fun2Ptr();
	cout << "                             ---------------\n";

	/*-------------------------------------------------------------------------------*/

	Derive od;
	int* vPtrDerive = (int*)(&od);
	int* vTableDerive = (int*)(*vPtrDerive);
	cout <<"\n\n\n-------------------------------------------\n";	
	cout << " Derive clas Memory Layout:-\n\n";

	cout << "       -----------\n";
	cout << " +-->>|   VPTR    |<--- " << vPtrDerive <<"[&od]" << endl;
	cout << " |     -----------\n";
	cout << " |    |  m_base1  |<--- " << vPtrDerive+1 <<'[' << *(vPtrDerive+1) <<"]\n";
	cout << " |     -----------\n";
	cout << " |    |  m_base2  |<--- " << vPtrDerive+2 <<'[' << *(vPtrDerive+2) <<"]\n";
	cout << " |     -----------\n";
	cout << " |    | m_derive1 |<--- " << vPtrDerive+3 <<'[' << *(vPtrDerive+3) <<"]\n";
	cout << " |     -----------\n";
	cout << " |    | m_derive2 |<--- " << vPtrDerive+4 <<'[' << *(vPtrDerive+4) <<"]\n";
	cout << " |     -----------\n";

	cout << " |\n |\n |                          VTable of Derive\n |\n";

	cout << " |                           ---------------\n";
	cout << " +-->> *VPTR-----> " <<  vTableDerive;
	Fun1Ptr = (FunPTR)*(vTableDerive + 0);
	Fun1Ptr();

	cout << "                             ---------------\n";
	cout << "                   ";
	cout << vTableDerive + 1;
	Fun2Ptr = (FunPTR)*(vTableDerive + 1);
	Fun2Ptr();

	cout << "                             ---------------\n";
	cout << "                   ";
	cout << vTableDerive + 2;
	FunPTR Fun3Ptr = (FunPTR)*(vTableDerive + 2);
	Fun3Ptr();
	cout << "                             ---------------\n\n";

	return 0;
}

