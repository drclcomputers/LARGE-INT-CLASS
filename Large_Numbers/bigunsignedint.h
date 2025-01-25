#pragma once
#include<iostream>

#define len bigint[0]

namespace big {

	class BIGUNSIGNEDINT {
	public:
		short* bigint=new short[10050];

		BIGUNSIGNEDINT(); //default constructor

		BIGUNSIGNEDINT(int num); //constructor 1

		BIGUNSIGNEDINT(long long num); //constructor 2

		BIGUNSIGNEDINT(char* p); //constructor 3


		void set(char* p = nullptr);

		void set_zero();


		BIGUNSIGNEDINT operator+(BIGUNSIGNEDINT const& obj);
		BIGUNSIGNEDINT operator+(int n);
		BIGUNSIGNEDINT operator+(long long n);
		void operator+=(BIGUNSIGNEDINT const& obj);
		void operator+=(long long obj);
		void operator+=(int obj);

		BIGUNSIGNEDINT operator-(BIGUNSIGNEDINT const& obj);
		BIGUNSIGNEDINT operator-(int n);
		BIGUNSIGNEDINT operator-(long long n);
		void operator-=(BIGUNSIGNEDINT const& obj);
		void operator-=(long long obj);
		void operator-=(int obj);

		BIGUNSIGNEDINT operator*(BIGUNSIGNEDINT const& obj);
		BIGUNSIGNEDINT operator*(int n);
		BIGUNSIGNEDINT operator*(long long n);
		void operator*=(BIGUNSIGNEDINT const& obj);
		void operator*=(long long obj);
		void operator*=(int obj);

		BIGUNSIGNEDINT operator/(BIGUNSIGNEDINT const& obj);
		BIGUNSIGNEDINT operator/(int n);
		BIGUNSIGNEDINT operator/(long long n);
		void operator/=(BIGUNSIGNEDINT const& obj);
		void operator/=(long long obj);
		void operator/=(int obj);

		BIGUNSIGNEDINT operator%(BIGUNSIGNEDINT const& obj);
		BIGUNSIGNEDINT operator%(int n);
		BIGUNSIGNEDINT operator%(long long n);

		bool operator<(BIGUNSIGNEDINT const& obj);
		bool operator<(int n);
		bool operator<(long long n);

		bool operator>(BIGUNSIGNEDINT const& obj);
		bool operator>(int n);
		bool operator>(long long n);

		bool operator==(BIGUNSIGNEDINT const& obj);
		bool operator==(int num);
		bool operator==(long long num);

		bool operator<=(BIGUNSIGNEDINT const& obj);
		bool operator<=(int n);
		bool operator<=(long long n);

		bool operator>=(BIGUNSIGNEDINT const& obj);
		bool operator>=(int n);
		bool operator>=(long long n);

		void operator=(BIGUNSIGNEDINT const& obj);
		void operator=(int num);
		void operator=(long long n);

		/*
		BIGUNSIGNEDINT custom_pow(BIGUNSIGNEDINT const& obj) {
			if (BIGUNSIGNEDINT(0) == obj) return 1;
			if (obj % 2 == 1) return (*this * custom_pow((obj-1)));
			BIGUNSIGNEDINT P = custom_pow((BIGUNSIGNEDINT(obj/2)));
			return P * P;
		}
		BIGUNSIGNEDINT custom_pow(int n) {
			return custom_pow(BIGUNSIGNEDINT(n));
		}*/


		friend std::ostream& operator<<(std::ostream& console, const BIGUNSIGNEDINT& obj);

		friend std::istream& operator>>(std::istream& console, BIGUNSIGNEDINT& obj);

		int to_int();

		long long to_longlong();

	};

	BIGUNSIGNEDINT operator+(int num, BIGUNSIGNEDINT const& obj);
	BIGUNSIGNEDINT operator+(BIGUNSIGNEDINT const& obj, int num);

	BIGUNSIGNEDINT operator-(int num, BIGUNSIGNEDINT const& obj);
	BIGUNSIGNEDINT operator-(BIGUNSIGNEDINT const& obj, int num);

	BIGUNSIGNEDINT operator*(int num, BIGUNSIGNEDINT const& obj);
	BIGUNSIGNEDINT operator*(BIGUNSIGNEDINT const& obj, int num);

	BIGUNSIGNEDINT operator/(int num, BIGUNSIGNEDINT const& obj);
	BIGUNSIGNEDINT operator/(BIGUNSIGNEDINT const& obj, int num);

	BIGUNSIGNEDINT operator%(int num, BIGUNSIGNEDINT const& obj);
	BIGUNSIGNEDINT operator%(BIGUNSIGNEDINT const& obj, int num);

	bool operator==(int num, BIGUNSIGNEDINT const& obj);
	bool operator==(BIGUNSIGNEDINT const& obj, int num);

	bool operator>(int num, BIGUNSIGNEDINT const& obj);
	bool operator>(BIGUNSIGNEDINT const& obj, int num);

	bool operator<(int num, BIGUNSIGNEDINT const& obj);
	bool operator<(BIGUNSIGNEDINT const& obj, int num);

	bool operator>=(int num, BIGUNSIGNEDINT const& obj);
	bool operator>=(BIGUNSIGNEDINT const& obj, int num);

	bool operator<=(int num, BIGUNSIGNEDINT const& obj);
	bool operator<=(BIGUNSIGNEDINT const& obj, int num);

}