//http://en.cppreference.com/w/cpp/language/dependent_name
//The typename disambiguator for dependent name
//typename使用规则:
//1.名称出现在一个模板中
//2.名称是受限的
//3.名称不是用于指定基类继承的列表中，也不是位于引入构造函数的成员初始化列表
//4.名称依赖于模板参数
//ps:1,2,3需要同时被满足
class Base
{
public:
	Base(int i){}
	Base(const Base& b){}
	virtual ~Base(){}
};

template<typename T>
class X : public Base
{
public:
	typedef int C;
	int D;
};

template<typename T>
class S : X<T>::Base
{
public:
	S():X<T>::Base(typename X<T>::Base(0)){}
	X<T> f()
	{
		typename X<T>::C *p;
		//X<T>::D* q; no typename so D * q
	}

	X<int>::C *s;
};

class U
{
public:
	X<int>::C *pc;
};

template<typename T>
class M
{
public:
	typename X<T>::C *pc;
};

//The template disambiguator for dependent names

template<typename T>
class Shell
{
public:
	template<int N>
	class In
	{
	public:
		template<int M>
		class Deep
		{
		public:
			virtual void f();
		};
	};
};

template<typename T, int N>
class Weird
{
public:
	void case1(typename Shell<T>::template In<N>::template Deep<N> *p)
	{
		p->f();
	}
};


int main()
{
	return 0;
}
