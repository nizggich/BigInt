#pragma once
#include <string>
#include <iostream>



bool isValid(const std::string& str) {
	for (char c : str) {
		if (c < '0' || c > '9') {
			return false;
		}
	}
	return true;
}

int getNumberOfDigits(const long long& value) {
	int numberOfDigits = 0;
	long tValue = value;

	while (tValue != 0) {
		tValue /= 10;
		numberOfDigits++;
	}

	return numberOfDigits;
}

