#include <iostream>
using std::cout;
using std::endl;

//1.test class name and type name inner class.Yeah,now i know,this is called injected class name
template<typename T>
class TestInjected
{
public:
	TestInjected(){}
	TestInjected(TestInjected const & r){ }
	template<typename Y> TestInjected(TestInjected<Y> const &){}
	~TestInjected(){}

	//TestInjected is ok.TestInjected<T> is ok.
	TestInjected &  operator=(TestInjected const & r){}
};

//2.test specialization
template<typename T1, typename T2>
class TestSpec
{
public:
	TestSpec(){ cout << "base template TestSpec" << endl; }
};

template<typename T>
class TestSpec<T, T>
{
public:
	TestSpec() { cout << "partial template TestSpec" << endl; }
};

template< >
class TestSpec<void, void>
{
public:
	TestSpec() { cout << "full specialization template TestSpec" << endl; }
};

//3.non-type parameters
//see cppreference http://en.cppreference.com/w/cpp/language/template_parameters
template<typename T, int MAX_SIZE>
class TestNonType
{
public:
	TestNonType() { cout << "[Non-Type]MAX_SIZE:" << MAX_SIZE << endl; }
};

template<const char* name>
class TestNonTypeLink
{
public:
	TestNonTypeLink() { cout << "[Non-Type]TestNonTypeLink name:" << name << endl; }
};

const char* internal = "internal";
extern const char* external = "external";
const char internal1[] = "internal1";
extern const char external1[] = "external1";

int main()
{
	//test2
	//partial ordering(cppreference)
	TestSpec<int, int> spec1;
	//can't compiled.Only is the primary template is found by name
	//its partial specializations are considered.
	//TestSpec<int> spec2;
	TestSpec<void, void> spec3;

	//test3
	TestNonType<int, 5> non_type1;
	TestNonType<int, 10> non_type2;
	
	//TestNonTypeLink<internal> non_type_inter; //err:internal and external is no a adderss of an variable.
	//TestNonTypeLink<external> non_type_exter;
	//TestNonTypeLink<internal1> non_type_inter1;
	TestNonTypeLink<external1> non_type_exter1;

	return 0;
}
