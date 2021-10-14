#include"date.h"

#include <iostream>

struct  test
{
	int *p;
	test(int * a) :p(a) {}

	void foo(test & a)
	{
		std::cout << this;

	}
	static int ddd()
	{
		return 0;
	}

};



int main()
{
	setlocale(0, "ru");

	datastart();

	return 0;
}