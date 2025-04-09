#include"fraction.h"
BigInteger bigOne(1LL);
BigInteger bigZero(0LL); 

void rightBoost(BigInteger& a, const BigInteger& b) {
	BigInteger boostB(b);
	for (int i = 1; BigInteger(boostB * 10).lessThanIt(a); ++i) {
		boostB *= 10;
	}
	while (b.lessThanIt(BigInteger(a - boostB))) {
		a -= boostB;
	}
}
void leftBoost(const BigInteger& a, BigInteger& b) {
	BigInteger boostA(a);
	for (int i = 1; BigInteger(boostA * 10).lessThanIt(b); ++i) {
		boostA *= 10;
	}
	while (a.lessThanIt(BigInteger(b - boostA))) {
		b -= boostA;
	}
}


BigInteger evclid(BigInteger a, BigInteger b) {
	if (a == bigZero || b == bigZero) { return bigOne; }
	/*if (a > b) {
		while (a % b != 0) {
			a -= b;
			if (b > a) { std::swap(a, b); }
		}
		return b;
	}
	else {
		while (b % a != 0) {
			b -= a;
			if (a > b) { std::swap(a, b); }
		}
		return a;
	}*/
	/*if (a > b) {
		if (a % b == 0) { return b; }
		a -= b;
		return evclid(a, b);
	}
	else {
		if (b % a == 0) { 
			return a; }
		b -= a;
		return evclid(b, a);
	}*/
	while (a != b) {
		if (a > b) { rightBoost(a, b);  a -= b; }
		else { leftBoost(a, b); b -= a; }
		//std::cout << a << " " << b << std::endl;
	}
	return a;
}

bool operator== (const fraction& X, const fraction& Y) {
	return X.isEqual(Y);
}
bool operator!= (const fraction& X, const fraction& Y) {
	return !(X.isEqual(Y));
}
bool operator< (const fraction& X, const fraction& Y) {
	return X.isLess(Y);
}
bool operator> (const fraction& X, const fraction& Y) {
	return !(X.isLess(Y));
}
std::ostream& operator<< (std::ostream& out, const fraction& A) {
	if (A.numerator_ == 0 || A.denominator_ == 0) { out << 0; }
	else if (A.denominator_ == 1) { out << A.numerator_; }
	else { out << to_string(A.numerator_) << "/" << to_string(A.denominator_); }
	return out;
}
fraction operator/(const fraction& X, const fraction& Y) {
	fraction tmp(X);
	return tmp /= Y;
}
fraction operator*(const fraction& X, const fraction& Y) {
	fraction tmp(X);
	return tmp *= Y;
}
fraction operator+(const fraction& X, const fraction& Y) {
	fraction tmp(X);
	return tmp+= Y;
}
fraction operator-(const fraction& X, const fraction& Y) {
	fraction tmp(X);
	return tmp -= Y;
}
