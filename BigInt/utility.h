#pragma once
#include <string>
#include <iostream>


//test test
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


std::string add(const int* term1, int size1, const int* term2, int size2) {
	int i = size1 - 1;
	int j = size2 - 1;

	int index = 0;
	int transfer = 0;
	int res = 0;

	std::string str;

	while (i >= 0 || j >= 0) {
		int aDigit = *(term1 + i);
		int bDigit = *(term2 + i);

		if (i == 0) {
			res = aDigit + transfer;
		}
		else if (j == 0) {
			res = aDigit + transfer;
		}
		else {
			res = aDigit + bDigit + transfer;
		}

		if (res >= 10) {
			res = res % 10;
			transfer = 1;
		}

		str.insert(index++, std::to_string(res));

		i--;
		j--;
	}

	if (transfer == 1) {
		str.insert(0, std::to_string(transfer));
	}

	return str;
}
