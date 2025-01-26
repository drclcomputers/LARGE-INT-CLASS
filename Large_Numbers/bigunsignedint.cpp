#include "bigunsignedint.h"

using namespace big;


//constructors

BIGUNSIGNEDINT::BIGUNSIGNEDINT() { //default constructor
	set_zero();
}

BIGUNSIGNEDINT::BIGUNSIGNEDINT(int num) { //constructor 1
	set_zero();
	if (num > 0) {
		len = 0;
		while (num > 0) {
			bigint[++len] = num % 10;
			num /= 10;
		}
	}
}

BIGUNSIGNEDINT::BIGUNSIGNEDINT(long long num) { //constructor 2
	set_zero();
	if (num > 0) {
		len = 0;
		while (num > 0) {
			bigint[++len] = num % 10;
			num /= 10;
		}
	}
}

BIGUNSIGNEDINT::BIGUNSIGNEDINT(const char* p) { //constructor 3
	//set number to 0
	set_zero();
	if (p != NULL)
		set(p);
}


//set values

void BIGUNSIGNEDINT::set(const char* p) {
	set_zero();

	if (p == nullptr) return;

	short int l = strlen(p);

	//set to element 0 the length of the number
	len = l;

	//set the number to the one in the char array
	for (int i = l; i > 0; i--)
		if (p[l - i] < 48 || p[l - i]>57) {
			throw std::runtime_error("Undecimal symbol!");
			break;
		}
		else
			bigint[i] = (int)p[l - i] - 48;
}

void BIGUNSIGNEDINT::set_zero() {
	len = 1;
	for (int i = 1; i <= 10049; i++) bigint[i] = 0;
}



//Mathematical Operations -----------------------------------------------------------------

//Addition

BIGUNSIGNEDINT BIGUNSIGNEDINT::operator+(BIGUNSIGNEDINT const& obj) {
	BIGUNSIGNEDINT res; // Result of addition
	int mx = std::max(len, obj.len); // Maximum length
	res.len = mx; // Set initial length of result

	bool add = false; // Carry flag for addition

	for (int i = 1; i <= mx; i++) {
		int sum = 0;

		if (i <= len) sum += bigint[i];
		if (i <= obj.len) sum += obj.bigint[i];
		if (add) sum += 1;

		res.bigint[i] = sum % 10;
		add = (sum >= 10);
	}

	if (add) {
		res.len++;
		res.bigint[res.len] = 1;
	}

	return res;
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator+(int n) {
	return *this + BIGUNSIGNEDINT(n);
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator+(long long n) {
	return *this + BIGUNSIGNEDINT(n);
}
void BIGUNSIGNEDINT::operator+=(BIGUNSIGNEDINT const& obj) {
	*this = *this + obj;
}
void BIGUNSIGNEDINT::operator+=(long long obj) {
	*this = *this + BIGUNSIGNEDINT(obj);
}
void BIGUNSIGNEDINT::operator+=(int obj) {
	*this = *this + BIGUNSIGNEDINT(obj);
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator++() {
	return *this + 1;
}

//Substraction

BIGUNSIGNEDINT BIGUNSIGNEDINT::operator-(BIGUNSIGNEDINT const& obj) { //substraction
	if (obj==0) return *this;
	if (*this == obj) return 0;
	BIGUNSIGNEDINT res; //result

	int mn = std::max(len, obj.len);
	bool min = 0;

	res.len = mn;

	//substraction
	if (*this > obj) {
		for (int i = 1; i <= mn; i++) {
			if (min) {
				if (bigint[i] - obj.bigint[i] - 1 >= 0) {
					res.bigint[i] = bigint[i] - obj.bigint[i] - 1, min = 0;
				}
				else {
					res.bigint[i] = bigint[i] - obj.bigint[i] + 9, min = 1;
				}
			}
			else {
				if (bigint[i] - obj.bigint[i] >= 0) {
					res.bigint[i] = bigint[i] - obj.bigint[i], min = 0;
				}
				else {
					res.bigint[i] = bigint[i] - obj.bigint[i] + 10, min = 1;
				}
			}
		}
	}
	else {/*
		for (int i = 1; i <= mn; i++) {
			if (min) {
				if (obj.bigint[i] - bigint[i] - 1 >= 0) {
					res.bigint[i] = obj.bigint[i] - bigint[i] - 1, min = 0;
				}
				else {
					res.bigint[i] = obj.bigint[i] - bigint[i] + 9, min = 1;
				}
			}
			else {
				if (obj.bigint[i] - bigint[i] >= 0) {
					res.bigint[i] = obj.bigint[i] - bigint[i], min = 0;
				}
				else {
					res.bigint[i] = obj.bigint[i] - bigint[i] + 10, min = 1;
				}
			}
		}*/
		return 0;
	}
	for (int i = res.len; i > 1; i--)
		if (res.bigint[i] == 0) res.len--;
		else break;

	return res;
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator-(int n) {
	return *this - BIGUNSIGNEDINT(n);
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator-(long long n) {
	return *this - BIGUNSIGNEDINT(n);
}
void BIGUNSIGNEDINT::operator-=(BIGUNSIGNEDINT const& obj) {
	*this = *this - obj;
}
void BIGUNSIGNEDINT::operator-=(long long obj) {
	*this = *this - BIGUNSIGNEDINT(obj);
}
void BIGUNSIGNEDINT::operator-=(int obj) {
	*this = *this - BIGUNSIGNEDINT(obj);
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator--() {
	return *this - 1;
}

//Multiplication

BIGUNSIGNEDINT BIGUNSIGNEDINT::operator*(BIGUNSIGNEDINT const& obj) { //multiplication
	if (obj==0 || *this==0) { set_zero(); return 0; }

	BIGUNSIGNEDINT res; //result

	int mx = len + obj.len - 1;

	if (mx > 10049) throw std::runtime_error("Value is too large for this type!");

	int add = 0;

	res.len = mx;

	if (*this >= obj) {

		for (int i = 1; i <= len; i++) {
			for (int j = 1; j <= obj.len; j++) {
				res.bigint[i + j - 1] += bigint[i] * obj.bigint[j];
			}
		}

		for (int i = 1; i <= res.len; i++) {
			add += res.bigint[i];
			res.bigint[i] = add % 10;
			add /= 10;
		}
	}
	else {
		for (int i = 1; i <= obj.len; i++) {
			for (int j = 1; j <= len; j++) {
				res.bigint[i + j - 1] += obj.bigint[i] * bigint[j];
			}
		}

		for (int i = 1; i <= res.len; i++) {
			add += res.bigint[i];
			res.bigint[i] = add % 10;
			add /= 10;
		}
	}

	if (add)
		res.bigint[++res.len] = add;

	return res;
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator*(int n) {
	return *this * BIGUNSIGNEDINT(n);
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator*(long long n) {
	return *this * BIGUNSIGNEDINT(n);
}
void BIGUNSIGNEDINT::operator*=(BIGUNSIGNEDINT const& obj) {
	*this = *this * obj;
}
void BIGUNSIGNEDINT::operator*=(long long obj) {
	*this = *this * BIGUNSIGNEDINT(obj);
}
void BIGUNSIGNEDINT::operator*=(int obj) {
	*this = *this * BIGUNSIGNEDINT(obj);
}

//Division

BIGUNSIGNEDINT BIGUNSIGNEDINT::operator/(BIGUNSIGNEDINT const& obj) { //division
	if (obj == 0) throw std::runtime_error("Division by zero!");
	if (*this == 0) return 0;
	if (*this < obj) return 0;
	if (obj == 1) return *this;

	BIGUNSIGNEDINT quotient;
	BIGUNSIGNEDINT remainder;

	for (int i = len; i > 0; --i) {
		remainder = remainder * 10 + bigint[i];

		int digitQuotient = 0;
		while (remainder >= obj) {
			remainder = remainder - obj;
			++digitQuotient;
		}

		quotient.bigint[i] = digitQuotient;
	}

	quotient.len = len;
	while (quotient.len > 1 && quotient.bigint[quotient.len] == 0) {
		--quotient.len;
	}

	return quotient;

}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator/(int n) {
	return *this / BIGUNSIGNEDINT(n);
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator/(long long n) {
	return *this / BIGUNSIGNEDINT(n);
}
void BIGUNSIGNEDINT::operator/=(BIGUNSIGNEDINT const& obj) {
	*this = *this / obj;
}
void BIGUNSIGNEDINT::operator/=(long long obj) {
	*this = *this / BIGUNSIGNEDINT(obj);
}
void BIGUNSIGNEDINT::operator/=(int obj) {
	*this = *this / BIGUNSIGNEDINT(obj);
}

//Remainder

BIGUNSIGNEDINT BIGUNSIGNEDINT::operator%(BIGUNSIGNEDINT const& obj) {
	if (obj == 0 || obj==1) throw std::runtime_error("Division by zero/you cant % by 1!");
	if (*this == 0) return BIGUNSIGNEDINT(0);
	if (*this < obj) return *this; 

	BIGUNSIGNEDINT quotient; 
	BIGUNSIGNEDINT remainder;

	for (int i = len; i > 0; --i) {
		remainder = remainder * 10 + bigint[i];

		int digitQuotient = 0;
		while (remainder >= obj) {
			remainder = remainder - obj;
			++digitQuotient;
		}

		quotient.bigint[i] = digitQuotient;
	}

	quotient.len = len;
	while (quotient.len > 1 && quotient.bigint[quotient.len] == 0) {
		--quotient.len;
	}

	return remainder;
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator%(int n) {
	return *this % BIGUNSIGNEDINT(n);
}
BIGUNSIGNEDINT BIGUNSIGNEDINT::operator%(long long n) {
	return *this % BIGUNSIGNEDINT(n);
}

//---------------------------------------------------------------------------------------------------



//Logic Operations-------------------------------------------------------------------------------

bool BIGUNSIGNEDINT::operator<(BIGUNSIGNEDINT const& obj) {
	if (obj == 0) return 0;
	if (len == obj.len) {
		for (int i = len; i > 0; i--) {
			if (bigint[i] == obj.bigint[i]) continue;
			else if (bigint[i] < obj.bigint[i]) return 1;
			else return 0;
		}
	}
	else
		return len < obj.len;
	return 0;
}
bool BIGUNSIGNEDINT::operator<(int n) {
	return *this < BIGUNSIGNEDINT(n);
}
bool BIGUNSIGNEDINT::operator<(long long n) {
	return *this < BIGUNSIGNEDINT(n);
}

bool BIGUNSIGNEDINT::operator>(BIGUNSIGNEDINT const& obj) {
	if (obj == 0) return 1;
	if (len == obj.len) {
		for (int i = len; i > 0; i--) {
			if (bigint[i] == obj.bigint[i]) continue;
			else if (bigint[i] < obj.bigint[i]) return 0;
			else return 1;
		}
	}
	else
		return len > obj.len;
	return 0;
}
bool BIGUNSIGNEDINT::operator>(int n) {
	return *this > BIGUNSIGNEDINT(n);
}
bool BIGUNSIGNEDINT::operator>(long long n) {
	return *this > BIGUNSIGNEDINT(n);
}

bool BIGUNSIGNEDINT::operator==(BIGUNSIGNEDINT const& obj) {
	int mx = std::max(len, obj.len);
	if (len == obj.len) {
		for (int i = mx; i > 0; i--) {
			if (bigint[i] == obj.bigint[i]) continue;
			else return 0;
		}
	}
	else
		return 0;
	return 1;
}
bool BIGUNSIGNEDINT::operator==(int num) {
	if (num == 0) {
		return len == 1 && bigint[1] == 0;
	}
	return *this == BIGUNSIGNEDINT(num);
}
bool BIGUNSIGNEDINT::operator==(long long num) {
	return BIGUNSIGNEDINT(num) == *this;
}

bool BIGUNSIGNEDINT::operator!=(BIGUNSIGNEDINT const& obj) {
	return !(*this == obj);
}
bool BIGUNSIGNEDINT::operator!=(int num) {
	return !(*this == BIGUNSIGNEDINT(num));
}
bool BIGUNSIGNEDINT::operator!=(long long num) {
	return !(BIGUNSIGNEDINT(num) == *this);
}

bool BIGUNSIGNEDINT::operator<=(BIGUNSIGNEDINT const& obj) {
	if (len < obj.len) return 1;
	if (len > obj.len) return 0;

	if (*this == obj) return 1;

	for (int i = len; i > 0; i--) {
		if (bigint[i] < obj.bigint[i]) return 1;
		if (bigint[i] > obj.bigint[i]) return 0;
	}

	return 1;
}
bool BIGUNSIGNEDINT::operator<=(int n) {
	return *this <= BIGUNSIGNEDINT(n);
}
bool BIGUNSIGNEDINT::operator<=(long long n) {
	return *this <= BIGUNSIGNEDINT(n);
}

bool BIGUNSIGNEDINT::operator>=(BIGUNSIGNEDINT const& obj) {
	if (len < obj.len) return 0;
	if (len > obj.len) return 1;

	if (*this == obj) return 1;

	for (int i = len; i > 0; i--) {
		if (bigint[i] < obj.bigint[i]) return 0;
		if (bigint[i] > obj.bigint[i]) return 1;
	}

	return 1;
}
bool BIGUNSIGNEDINT::operator>=(int n) {
	return *this >= BIGUNSIGNEDINT(n);
}
bool BIGUNSIGNEDINT::operator>=(long long n) {
	return *this >= BIGUNSIGNEDINT(n);
}

void BIGUNSIGNEDINT::operator=(BIGUNSIGNEDINT const& obj) {
	len = obj.len;
	for (int i = 1; i <= obj.len; i++) {
		bigint[i] = obj.bigint[i];
	}
}
void BIGUNSIGNEDINT::operator=(int num) {
	*this = BIGUNSIGNEDINT(num);
}
void BIGUNSIGNEDINT::operator=(long long n) {
	*this = BIGUNSIGNEDINT(n);
}


BIGUNSIGNEDINT big::bigpow(BIGUNSIGNEDINT const& obj, BIGUNSIGNEDINT const& that) {
	BIGUNSIGNEDINT P, A, n;
	P = 1, A = obj, n = that;
	while (n != 0)
	{
		if (n % 2 == 1) {
			P = P * A;
		}
		A = A * A;
		n /= 2;
	}
	return P;
}
BIGUNSIGNEDINT big::bigpow(BIGUNSIGNEDINT const& obj, int n) {
	return big::bigpow(obj, BIGUNSIGNEDINT(n));
}
BIGUNSIGNEDINT big::bigpow(int n, BIGUNSIGNEDINT const& obj) {
	return big::bigpow(BIGUNSIGNEDINT(n), obj);
}


BIGUNSIGNEDINT big::factorial(BIGUNSIGNEDINT const& obj) {
	BIGUNSIGNEDINT fact = 1;
	for (int i = 2; i <= obj; ++i)
		fact *= i;
	return fact;
}
BIGUNSIGNEDINT big::factorial(int n) {
	BIGUNSIGNEDINT fact = 1;
	for (int i = 2; i <= n; ++i)
		fact *= i;
	return fact;
}


bool big::prime(BIGUNSIGNEDINT& obj) {
	BIGUNSIGNEDINT d;
	for (d = 2; d * d < obj; d += 1) {
		if (obj % d == 0)
			return 0;
	}
	if (d * d == obj) return 0;
	return 1;
}


int big::sum_digit(BIGUNSIGNEDINT const& obj) {
	int sum = 0;
	for (int i = 1; i <= obj.bigint[0]; i++)
		sum += obj.bigint[i];
	return sum;
}


BIGUNSIGNEDINT big::bigsqrt(BIGUNSIGNEDINT const& obj) {
	BIGUNSIGNEDINT d;
	for (d = 2; d * d <= obj; d += 1);
	return d-1;
}

BIGUNSIGNEDINT big::bigcbrt(BIGUNSIGNEDINT const& obj) {
	BIGUNSIGNEDINT d;
	for (d = 2; d * d * d <= obj; d += 1);
	return d-1;
}

//----------------------------------------------------------------------------------------


//printing or input

std::ostream& big::operator<<(std::ostream& console, const BIGUNSIGNEDINT& obj) { //print BIGUNSIGNEDINT
	int l = obj.len; //length
	for (int i = l; i > 0; i--) //iterate through loop to get every digit
		console << obj.bigint[i];
	return console;
}

std::istream& big::operator>>(std::istream& console, BIGUNSIGNEDINT& obj) {
	char p[1025] = "";
	console >> p;

	obj.set_zero();

	int l;
	int strlenp=0;
	for (strlenp; p[strlenp] != '\0'; strlenp++);
	obj.len = l = strlenp;
	for (int i = obj.len; i > 0; i--)
		if (p[l - i] < 48 || p[l - i]>57) {
			throw std::runtime_error("Undecimal symbol!");
			break;
		}
		else
			obj.bigint[i] = (int)p[l - i] - 48;

	return console;
}

void big::format_print(const BIGUNSIGNEDINT& obj, int type=5) { 
	//type 1 -> '
	//type 2 -> .
	//type 3 -> ,
	//type 4 -> `
	//type 5 -> space ' '
	char separator;
	switch (type) {
	case 1:
		separator = '\'';
		break;
	case 2:
		separator = '.';
		break;
	case 3:
		separator = ',';
		break;
	case 4:
		separator = '`';
		break;
	default:
		separator = ' ';
		break;
	}
	
	int aux = obj.len % 3, a=aux;
	if (aux) {
		aux = obj.len;
		while (aux>obj.len-obj.len%3) std::cout << obj.bigint[aux--];
		std::cout << separator;
	}

	for (int i = obj.len - a; i > 0; i -= 3) {
		std::cout << obj.bigint[i] << obj.bigint[i - 1] << obj.bigint[i - 2];
		if (i != 3) std::cout << separator;
	}
}

//converting

int big::to_int(BIGUNSIGNEDINT obj) {
	int rez = 0;
	if (obj.len <= 10 && obj <= INT32_MAX) {
		for (int i = obj.len; i > 0; i--) {
			rez = rez * 10 + obj.bigint[i];
		}
	}
	else
		throw std::runtime_error("Integer limit excedeed.");

	return rez;
}

long long big::to_longlong(BIGUNSIGNEDINT obj) {
	long long rez = 0;
	if (obj.len<=19 && obj <= INT64_MAX) {
		for (int i = obj.len; i > 0; i--) {
			rez = rez * 10 + obj.bigint[i];
		}
	}
	else
		throw std::runtime_error("Long long limit excedeed. Cannot convert to primitive C++ data types.");

	return rez;
}


//other functions

BIGUNSIGNEDINT operator+(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) + obj;
}
BIGUNSIGNEDINT operator+(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) + obj;
}

BIGUNSIGNEDINT operator-(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) - obj;
}
BIGUNSIGNEDINT operator-(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) - obj;
}

BIGUNSIGNEDINT operator*(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) * obj;
}
BIGUNSIGNEDINT operator*(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) * obj;
}

BIGUNSIGNEDINT operator/(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) / obj;
}
BIGUNSIGNEDINT operator/(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) / obj;
}

BIGUNSIGNEDINT operator%(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) % obj;
}
BIGUNSIGNEDINT operator%(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) % obj;
}

bool big::operator==(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) == obj;
}
bool big::operator==(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) == obj;
}

bool big::operator>(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) > obj;
}
bool big::operator>(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) > obj;
}

bool big::operator<(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) < obj;
}
bool big::operator<(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) < obj;
}

bool big::operator>=(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) >= obj;
}
bool big::operator>=(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) >= obj;
}

bool big::operator<=(int num, BIGUNSIGNEDINT const& obj) {
	return BIGUNSIGNEDINT(num) <= obj;
}
bool big::operator<=(BIGUNSIGNEDINT const& obj, int num) {
	return BIGUNSIGNEDINT(num) <= obj;
}

//Random Number Generator

BIGUNSIGNEDINT big::bigrandrange(BIGUNSIGNEDINT seed, BIGUNSIGNEDINT min, BIGUNSIGNEDINT max) {
	if (max == 0) max.set(BIGUNSIGNEDINT_MAX);
	BIGUNSIGNEDINT a, c, m;
	a = 1103515245;
	c = 12345;
	m = 2147483648;
	seed = (a * seed + c) % m;
	return min + (seed % (max - min + 1));
}