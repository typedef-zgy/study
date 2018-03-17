//purpose of the test:
//1.test class name and type name inner class.Yeah,now i know,this is called injected class name
template<typename T>
class Test
{
public:
	typedef Test this_type_i;
	typedef Test<T> this_type_o;
	Test(){}
	Test(Test const & r){ typename T::value_type value; }
	template<typename Y> Test(Test<Y> const &){}
	~Test(){}

	Test &  operator=(Test const & r){}
};

template<typename T>
struct type_trails_test
{
	typedef T value_type;
};

int main()
{
	Test< type_trails_test<int> > t;
	Test< type_trails_test<int> > t1(t);
	Test< type_trails_test<int> >::this_type_i t2;
	Test< type_trails_test<int> >::this_type_o t3;
	
	return 0;
}
