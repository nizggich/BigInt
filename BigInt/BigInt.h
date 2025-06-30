#pragma once
#include <string>

class BigInt
{
	static const int capacity = 256;
	static const int llongMaxDigits = 19;
	int data[capacity];
	char sign{ '+' };
	int size{ 0 };

	BigInt substruct(const BigInt& value) const;
	BigInt add(const BigInt& value) const;
	bool pushBackDigit(int digit);

public:
	BigInt();
	BigInt(const BigInt& value);
	BigInt(const long long& value);
	BigInt(const std::string& value);

	std::string toString() const;

	int getSize() const;
	char getSign() const;

	bool isNegative() const;
	void makePositive();
	void makeNegative();

	static const BigInt& max(const BigInt& a, const BigInt& b);
	static const BigInt& min(const BigInt& a, const BigInt& b);
	static BigInt abs(const BigInt value);

	BigInt operator=(const BigInt& value);
	bool operator==(const BigInt& value) const;
	bool operator!=(const BigInt& value) const;
	bool operator<(const BigInt& value) const;
	bool operator>(const BigInt& value) const;
	bool operator>=(const BigInt& value) const;
	bool operator<=(const BigInt& value) const;
	BigInt operator+(const BigInt& value) const;
	BigInt operator-(const BigInt& value) const;
	BigInt operator/(const BigInt& divider) const;
	BigInt operator*(const BigInt& value) const;
	BigInt operator*(const long long& value) const;
};
