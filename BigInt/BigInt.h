#pragma once
#include <string>

class BigInt
{
	static const int capacity = 256;
	int data[capacity];
	char sign{ '+' };
	int size{ 0 };

	BigInt substruct(const BigInt& value) const;
	BigInt add(const BigInt& value) const;

public:
	BigInt();
	BigInt(const BigInt& value);
	BigInt(const long long& value);
	BigInt(const std::string& value);

	int getSize() const;
	char getSign() const;
	static const int getCapacity();

	bool isNegative() const;
	void makePositive();
	void makeNegative();

	static const BigInt& max(const BigInt& a, const BigInt& b);
	static const BigInt& min(const BigInt& a, const BigInt& b);
	static BigInt abs(const BigInt value);

	bool operator==(const BigInt& value) const;
	bool operator!=(const BigInt& value) const;
	bool operator<(const BigInt& value) const;
	bool operator>(const BigInt& value) const;
	BigInt operator+(const BigInt& value) const;
	BigInt operator-(const BigInt& value) const;
	BigInt operator/(const BigInt& value) const;
	BigInt operator*(const BigInt& value) const;

};
