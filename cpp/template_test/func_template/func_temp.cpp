/*
1.func templates dose not allow partial specialization.
2.if you want to customize a function base template and want that custom
  ization to participate in overload resolution(or,to always be used in 
  the case of exact match),make it a plain old function, not a speciali-
  zation.And,if you do provide overloads,avoid also providing specializ-
  ations.(order affect the result.)
3.If you're writing a function base template,prefer to write it as a 
  single function template that should never be specialized or overload-
  ed,and then implement the function template entirely as a simple hand-
  off to a class template containing a static function with the same si-
  gnature.Everyone can specialize that -- both fully and partially,and 
  without affecting the results of overload resolution.
4.nontemplate functions are first-class citizens.Then compare the base 
  the base template,then compare the specialized template of that base 
  template.
*/
#include<iostream>

using std::cout;
using std::endl;

//case1:priority
int test_case1(int){ cout << "1-1" << endl; return 0; } //(1-1)
template<typename T> T test_case1(T){ cout << "1-2" << endl; return T(); } //(1-2)
template<> float test_case1<float>(float){ cout << "1-3" << endl; return 0; } //(1-3)

//case2:order
//order1
//(2-1)
template<typename T>
void test_case2(T)
{
	cout << "2-1" << endl;
}

//(2-2)
template<typename T>
void test_case2(T*)
{
	cout << "2-2" << endl;
}

//(2-3)
template<>
void test_case2(int *)
{
	cout << "2-3" << endl;
}

//order2
//(2-4)
template<typename T>
void test_case22(T)
{
	cout << "2-4" << endl;
}

//(2-5)
template<>
void test_case22(int *)
{
	cout << "2-5" << endl;
}

template<typename T>
void test_case22(T *)
{
	cout << "2-6" << endl;
}

int main()
{
	//test case 1
	test_case1(100);		//(1-1)
	test_case1((long)100);		//(1-2)	
	test_case1((float)0.1);		//(1-3)
	test_case1(double(0.23));	//(1-2)

	//test case 2
	//the location of the specialized template function 2-3 or 2-5 affect the match result.
	int ic2 = 0;
	int *pic2 = NULL;
	
	test_case2(ic2);		//2-1	
	test_case2(pic2);		//2-3

	test_case22(ic2);		//2-4
	test_case22(pic2);		//2-6

	return 0;

