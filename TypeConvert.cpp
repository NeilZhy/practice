#include<stdio.h>
#include<iostream>
using namespace std;

void FunTest()
{
	//ǿת
	int a = 10;
	double d = (double)a;
	printf("%lf %d\n",d,a);
	//����������͵�ת��  (static_cast)
	int b = 10;
	double c = static_cast<double>(b);
	printf("%lf %d\n",c,a);
	//������������͵�ת��
	int q = 10;
	int *p = reinterpret_cast<int*>(&q);
	printf("%d %d\n",q,*p);
	//ɾ��������const����
	const int x = 3;
	int *r = const_cast<int*>(&x);
	*r = 30;
	printf("%d %d\n",x,*r);

}


////������������͵�ת��
typedef void (*Fun)();

int DoSomething(int i)
{
	printf("DoSomething()\n");
	return 0;
}

//dynamic_cast�����麯�������ת��
class A
{
public:
	virtual void test()
	{
		cout<<"virtual void test()"<<endl;
	}
};
class B:public A
{
	
};

void Test(A* pa)
{
	B* pb1 = static_cast<B*>(pa);
	B* pb2 = dynamic_cast<B*>(pa);
	cout<<"pb1: "<<pb1<<endl;
	cout<<"pb2: "<<pb2<<endl;

}

//explicit�ؼ�����ֹ����ת�����캯�����е���ʽת���ķ���

class C
{
public:
	explicit C(int a )
	{
		cout<<"C(int a)"<<endl;
	}
	C(const C& c)
	{
		cout<<"C(const C& c)"<<endl;
	}
private:
	int _a;
};

void test()
{
	C c(1);
//	C c1 = 2;

}

int main()
{
	A a;
	B b;
	Fun f = reinterpret_cast<Fun>(DoSomething);
	FunTest();
	f();
	Test(&a);
	Test(&b);
	test();
	return 0;
}