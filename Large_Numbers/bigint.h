#pragma once
#include<iostream>

#define len bigint[0]

namespace big {

	class BIGINT {
	public:
		short* bigint=new short[10050];

		BIGINT(); //default constructor

		BIGINT(int num); //constructor 1

		BIGINT(long long num); //constructor 2

		BIGINT(char* p); //constructor 3


		void set(char* p = nullptr);

		void set_zero();


		BIGINT operator+(BIGINT const& obj);
		BIGINT operator+(int n);
		BIGINT operator+(long long n);
		void operator+=(BIGINT const& obj);
		void operator+=(long long obj);
		void operator+=(int obj);

		BIGINT operator-(BIGINT const& obj);
		BIGINT operator-(int n);
		BIGINT operator-(long long n);
		void operator-=(BIGINT const& obj);
		void operator-=(long long obj);
		void operator-=(int obj);

		BIGINT operator*(BIGINT const& obj);
		BIGINT operator*(int n);
		BIGINT operator*(long long n);
		void operator*=(BIGINT const& obj);
		void operator*=(long long obj);
		void operator*=(int obj);

		BIGINT operator/(BIGINT const& obj);
		BIGINT operator/(int n);
		BIGINT operator/(long long n);
		void operator/=(BIGINT const& obj);
		void operator/=(long long obj);
		void operator/=(int obj);

		BIGINT operator%(BIGINT const& obj);
		BIGINT operator%(int n);
		BIGINT operator%(long long n);

		bool operator<(BIGINT const& obj);
		bool operator<(int n);
		bool operator<(long long n);

		bool operator>(BIGINT const& obj);
		bool operator>(int n);
		bool operator>(long long n);

		bool operator==(BIGINT const& obj);
		bool operator==(int num);
		bool operator==(long long num);

		bool operator<=(BIGINT const& obj);
		bool operator<=(int n);
		bool operator<=(long long n);

		bool operator>=(BIGINT const& obj);
		bool operator>=(int n);
		bool operator>=(long long n);

		void operator=(BIGINT const& obj);
		void operator=(int num);
		void operator=(long long n);

		/*
		BIGINT custom_pow(BIGINT const& obj) {
			if (BIGINT(0) == obj) return 1;
			if (obj % 2 == 1) return (*this * custom_pow((obj-1)));
			BIGINT P = custom_pow((BIGINT(obj/2)));
			return P * P;
		}
		BIGINT custom_pow(int n) {
			return custom_pow(BIGINT(n));
		}*/


		friend std::ostream& operator<<(std::ostream& console, const BIGINT& obj);

		friend std::istream& operator>>(std::istream& console, BIGINT& obj);

		int to_int();

		long long to_longlong();

	};

	BIGINT operator+(int num, BIGINT const& obj);
	BIGINT operator+(BIGINT const& obj, int num);

	BIGINT operator-(int num, BIGINT const& obj);
	BIGINT operator-(BIGINT const& obj, int num);

	BIGINT operator*(int num, BIGINT const& obj);
	BIGINT operator*(BIGINT const& obj, int num);

	BIGINT operator/(int num, BIGINT const& obj);
	BIGINT operator/(BIGINT const& obj, int num);

	BIGINT operator%(int num, BIGINT const& obj);
	BIGINT operator%(BIGINT const& obj, int num);

	bool operator==(int num, BIGINT const& obj);
	bool operator==(BIGINT const& obj, int num);

	bool operator>(int num, BIGINT const& obj);
	bool operator>(BIGINT const& obj, int num);

	bool operator<(int num, BIGINT const& obj);
	bool operator<(BIGINT const& obj, int num);

	bool operator>=(int num, BIGINT const& obj);
	bool operator>=(BIGINT const& obj, int num);

	bool operator<=(int num, BIGINT const& obj);
	bool operator<=(BIGINT const& obj, int num);

}