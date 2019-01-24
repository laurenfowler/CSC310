#include <iostream>
using namespace std;

class Base
{
	public :
		virtual void iam(); //virtual lets derived classes override function
};

void Base::iam() //member function of base
{
          cout << "base" << endl;
}

class One : public Base //derived class of Base
{
	public :
		void iam() { cout << "one" << endl; }
		void iam2() {	Base::iam();  }
};

class Two: public Base{ //derived class of base
    public: 
        void iam() {cout << "two" << endl;}
        void iam2() { Base::iam();}

};

int main()
{
	Base b;  cout << "Calling b.iam() "; b.iam();

	One derived1;

        cout << "Calling derived1.iam() "; derived1.iam();

	Base *d1Ptr  = &derived1;
	d1Ptr -> iam(); //associates with base class when there is no virtual

    Two derived2;
    cout << "Calling derived1.iam() "; derived2.iam();
    Base *d2Ptr = &derived2;
    d2Ptr -> iam();

}
