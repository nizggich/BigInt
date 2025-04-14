#pragma once
#include <string>

class BigInt
{
	static const int capacity = 256;
	int data[capacity];
	char sign{'+'};
	int size{0};

	BigInt substruct(const BigInt& val) const;
	BigInt add(const BigInt& val) const;	
	
public:
	BigInt();
	BigInt(const BigInt& value);
	BigInt(const long long& value);
	BigInt(const std::string& value);

	int getSize() const; 
	char getSign() const;
	static const int getCapacity();
	const int* getData() const;

	bool isNegative() const;
	void makePositive();
	void makeNegative();
	BigInt abs(const BigInt value) const;

	static const BigInt& max(const BigInt& a, const BigInt& b);
	static const BigInt& min(const BigInt& a, const BigInt& b);

	bool operator==(const BigInt& value) const;
	bool operator!=(const BigInt& value) const;
	BigInt operator+(const BigInt& value) const;
	BigInt operator-(const BigInt& value) const;

};
