#ifndef _FRACTIONS_
#define _FRACTIONS_
#include "biginteger.h"
BigInteger evclid(BigInteger a, BigInteger b);
extern BigInteger bigOne;
extern BigInteger bigZero;

class fraction {
	BigInteger numerator_;
	BigInteger denominator_;
	void swap(fraction& other) {
		std::swap(numerator_, other.numerator_);
		std::swap(denominator_, other.denominator_);
	}
public:
	fraction() :numerator_(bigZero), denominator_(bigOne) {}
	fraction(int n) :numerator_(n), denominator_(bigOne) {}
	fraction(const BigInteger& numerator, const BigInteger& denominator) :numerator_(numerator), denominator_(denominator) { reduceFraction(); }
	fraction(const fraction& X) : numerator_(X.numerator_), denominator_(X.denominator_) {};
	fraction(fraction&& X) noexcept : numerator_(std::move(X.numerator_)), denominator_(std::move(X.denominator_)) {}
	fraction& operator= (fraction&& other) noexcept {
		fraction tmp(std::move(other));
		swap(tmp);
		return *this;
	}

	fraction& operator+=(const fraction& other) {
		if (denominator_ == other.denominator_ || other.denominator_ == bigZero || denominator_ == bigZero) { numerator_ += other.numerator_; }
		else {
			numerator_ *= other.denominator_;
			//std::cout << numerator_<< " ";
			BigInteger tmp(other.numerator_ * denominator_);
			//std::cout << tmp << " ";
			numerator_ += tmp;
			//std::cout << numerator_ << " ";
			denominator_ *= other.denominator_;
			//std::cout << fraction(numerator_,denominator_);
		}
		reduceFraction();
		return *this;
	}
	fraction& operator-=(const fraction& other) {
		if (numerator_ == bigZero || denominator_ == bigZero) {
			numerator_ = -(other.numerator_);
			denominator_ = other.denominator_;
		}
		else if (other.numerator_ == bigZero || other.denominator_ == bigZero) {}
		else if (denominator_ == other.denominator_) {
			numerator_ -= (other.numerator_);
		}
		else {
			numerator_ *= other.denominator_;
			BigInteger tmp(other.numerator_ * denominator_);
			//std::cout << numerator_ << std::endl;
			//std::cout << tmp << std::endl;
			numerator_ -= tmp;
			denominator_ *= other.denominator_;
			//std::cout << *this;
		}
		if (numerator_ == bigZero) { denominator_ = bigZero; }
		reduceFraction();
		return *this;
	}
	fraction& operator*=(const fraction& other) {
		if (denominator_ == other.numerator_) { denominator_ = other.denominator_; }
		else if (numerator_ == other.denominator_) { numerator_ = other.numerator_; }
		else {
			numerator_ *= other.numerator_;
			denominator_ *= other.denominator_;
		}
		reduceFraction();
		return *this;
	}
	fraction& operator/=(const fraction& other) {
		if (numerator_ == other.numerator_) { numerator_ = other.denominator_; }
		else if (denominator_ == other.denominator_) { denominator_ = other.numerator_; }
		else {
			numerator_ *= other.denominator_;
			denominator_ *= other.numerator_;
			//std::cout << *this << std::endl;
		}
		numerator_.setSign(denominator_);
		reduceFraction();
		return *this;
	}
	fraction& operator= (const fraction& other) {
		denominator_ = other.denominator_;
		numerator_ = other.numerator_;
		return *this;
	}
	fraction& operator= (const int& other) {
		numerator_ = other;
		denominator_ = bigOne;
		return *this;
	}
	fraction operator-() const {
		fraction F(*this);
		F.numerator_ = -numerator_;
		return F;
	}

	//bool operations
	bool isEqual(const fraction& other)const {
		return (numerator_ == other.numerator_ && denominator_ == other.denominator_);
	}
	bool isLess(const fraction& other)const {
		BigInteger tmp(other.numerator_ / other.denominator_);
		return (numerator_ / denominator_) < tmp;
	}

	BigInteger getBigInteger() {
		if (denominator_ == bigOne) { return numerator_; }
		return bigZero;
	}
	BigInteger getNumerator() {
		return numerator_;
	}
	BigInteger getDenominator() {
		return denominator_;
	}

	fraction& reduceFraction() {
		BigInteger a(numerator_.abc());
		if (a == bigOne) { return*this; }
		BigInteger b(denominator_.abc());
		//std::cout << a << " " << b;
		BigInteger coof = evclid(a, b);
		if (coof != bigOne) {
			numerator_ /= coof;
			denominator_ /= coof;
		}
		return*this;
	}

	friend std::ostream& operator<< (std::ostream& out, const fraction& A);
};

bool operator== (const fraction& X, const fraction& Y);
bool operator!= (const fraction& X, const fraction& Y);
bool operator< (const fraction& X, const fraction& Y);
bool operator> (const fraction& X, const fraction& Y);
fraction operator/ (const fraction& X, const fraction& Y);
fraction operator* (const fraction& X, const fraction& Y);
fraction operator+ (const fraction& X, const fraction& Y);
fraction operator- (const fraction& X, const fraction& Y);
#endif