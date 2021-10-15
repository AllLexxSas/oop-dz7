#pragma once


#ifndef STREAM_H
#define STREAM_H



#include <string>
#include <ostream>
#include <iostream>
#include <memory>



class Date
{
private:
	int day;
	int month;
	int year;
	int QuantityDay(int & _month)
	{
		return (28 + (_month + (int)floor(_month / 8)) % 2 + 2 % _month + 2 * floor(1 / _month));
	}
public:
	Date() {};
	Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year)
	{
		if (_month < 1 || _month > 12)
		{
			std::cout << "месяц введен не правильно\n";
			return;
		}
		else if (_day < 1 || _day > QuantityDay(_month)) 
		{
			std::cout << "день введен не правильно\n";
			return;
		}
		else if (_year < 0)
		{
			std::cout << "год введен не правильно\n";
		}

		//day = _day; month = _month; year = _year;
	}
	~Date()
	{
		//std::cout << "Delete Data" << std::endl;
	}

	const int GetDay()const
	{
		return day;
	}

	const int GetMonth()const
	{
		return month;
	}

	const int GetYear()const
	{
		return year;
	}
	friend std::ostream& operator <<(std::ostream &o, Date& data);
};

template<typename T>
class SmartSointer
{
private:
	T *m_date;
public:
	SmartSointer(T *_date = nullptr) :m_date(_date)
	{}

	~SmartSointer()
	{
		delete m_date;
	}

	const T* operator -> ()const
	{
		return m_date;
	}

	T& operator *()const
	{
		return *m_date;
	}

	operator T*()const
	{
		return m_date;
	}
	friend std::ostream& operator <<(std::ostream &o, SmartSointer& ss);

	SmartSointer & operator = (SmartSointer& d)
	{
		if (&d == this)
			return *this;

		delete m_date;
		m_date = d.m_date;
		d.m_date = nullptr;
		return *this;
	}
};


Date* comparsionData(SmartSointer<Date> &d1, SmartSointer<Date> &d2)
{
	if ((d2->GetYear() + d2->GetMonth() + d2->GetDay()) >
		(d1->GetYear() + d1->GetMonth() + d1->GetDay())) {
		return new Date(d2->GetDay(), d2->GetMonth(), d2->GetYear());
	}
	return new Date(d1->GetDay(), d1->GetMonth(), d1->GetYear());
}

void ExchangeDates(SmartSointer<Date> &d1, SmartSointer<Date> &d2)
{
	SmartSointer<Date> temp;
	temp = d1;
	d1 = d2;
	d2 = temp;
}

std::ostream& operator <<(std::ostream &o, Date& data)
{
	o << data.GetDay() << "." << data.GetMonth() << "." << data.GetYear() << std::endl;
	return o;
}

std::ostream& operator <<(std::ostream &o, SmartSointer<Date>& ss)
{
	o << *ss << std::endl;
	return o;
}

void test_ptr() {
	std::unique_ptr <Date> d1(new Date(12, 3, 1955));
	std::unique_ptr <Date> d2;

	d2 = std::move(d1);

	std::cout << *d2;
	d1.swap(d2);
	std::cout << *d1;


	std::shared_ptr<Date> d3(new Date(24, 07, 1983));
	{
		std::shared_ptr<Date> d4(d3);

		std::cout << *d3;
		std::cout << *d4;
	}
	std::cout << *d3;

}


int datastart()
{
	//проверка первого задания
	SmartSointer<Date> today(new Date(31, 12, 2021));
	SmartSointer<Date> date;

	std::cout << today;

	date = today;
	std::cout << date;

	//проверка второго задания
	SmartSointer<Date> date1(new Date(2, 7, 2009));
	SmartSointer<Date> date2(new Date(13, 4, 2020));

	SmartSointer<Date> test(comparsionData(date1, date2));
	std::cout << "первая дата - " << date1;
	std::cout << "вторая дата - " << date2;

	std::cout << "близкая к нам дата - "  << test;

	ExchangeDates(date1, date2);

	std::cout << "даты после смены местаии:\n";

	std::cout << "первая дата - " << date1;
	std::cout << "вторая дата - " << date2;

	//разбирался с умными указателями из stl
	test_ptr();
	return 0;
}


#endif // STREAM_H
