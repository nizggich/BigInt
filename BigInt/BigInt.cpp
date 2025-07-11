#include "BigInt.h"
#include <stdexcept>
#include <map>
#include "utility.h"

BigInt::BigInt() {
	sign = '+';
	size = 0;
}

BigInt::BigInt(const BigInt& value) {
	sign = value.sign;
	size = value.size;

	for (size_t i = 0; i < capacity; i++) {
		data[i] = value.data[i];
	}

}

BigInt::BigInt(const long long& value1) {
	sign = value1 > 0 ? '+' : '-';
	size = getNumberOfDigits(value1);

	long long tValue = std::abs(value1);
	int index = size - 1;

	for (size_t i = 0; i < size; i++) { //why was i < size - 1 ?
		data[i] = 0;
	}

	while (tValue != 0)
	{
		data[index--] = tValue % 10;
		tValue /= 10;
	}

}

BigInt::BigInt(const std::string& value) {
	char vSign = (value.at(0) == '-') ? '-' : '+';
	std::string nStr = (vSign == '-') ? value.substr(1) : value;

	if (isValid(nStr)) {
		for (size_t i = 0; i < nStr.size() - 1; i++) {
			data[i] = 0;
		}

		for (size_t i = 0; i < nStr.size(); i++) {
			data[i] = nStr.at(i) - '0';
		}
		size = nStr.size();
		sign = vSign;
	}
	else {
		throw std::invalid_argument("String contains invalid characters");
	}
}

int BigInt::getSize() const {
	return size;
}

char BigInt::getSign() const {
	return sign;
}

bool BigInt::isNegative() const {
	return sign == '-';
}

void BigInt::makePositive() {
	sign = '+';
}

void BigInt::makeNegative() {
	sign = '-';
}

BigInt BigInt::abs(const BigInt value) {
	BigInt res = BigInt(value);
	res.sign = '+';
	return res;
}

const BigInt& BigInt::max(const BigInt& a, const BigInt& b) {
	char aSign = a.sign;
	char bSign = b.sign;

	if (aSign - bSign == 0 && a.size != b.size) {
		if (a.isNegative()) {
			return a.size > b.size ? b : a;
		}
		else {
			return a.size > b.size ? a : b;
		}
	}
	else if (aSign - bSign != 0) {
		if (a.isNegative()) {
			return b;
		}
		else {
			return a;
		}
	}

	int aSize = a.getSize();
	int bSize = b.getSize();

	const int* pa = a.data;
	const int* pb = b.data;

	int i = 0;

	while (i < a.size) {
		int aDigit = *(pa + i);
		int bDigit = *(pb + i);

		if (a.isNegative()) {
			if (aDigit > bDigit) {
				return b;
			}
			else if (aDigit == bDigit) {
				i++;
			}
			else {
				return a;
			}
		}
		else {
			if (aDigit > bDigit) {
				return a;
			}
			else if (aDigit == bDigit) {
				i++;
			}
			else {
				return b;
			}
		}
	}

	return a;
}


const BigInt& BigInt::min(const BigInt& a, const BigInt& b) {
	return max(a, b) == a ? b : a;
}

bool BigInt::operator==(const BigInt& value) const {
	if (this == &value) {
		return true;
	}

	for (size_t i = 0; i < capacity; i++) {
		if (data[i] != value.data[i]) {
			return false;
		}
	}

	return true;
}

bool BigInt::operator!=(const BigInt& value) const {
	if (this->operator==(value)) {
		return false;
	}
	else {
		return true;
	}
}

BigInt BigInt::substruct(const BigInt& value) const {
	BigInt thisVal = *this;

	int i = thisVal.getSize() - 1;
	int j = value.getSize() - 1;

	BigInt aMod = abs(thisVal);
	BigInt bMod = abs(value);

	const BigInt& maxVal = max(aMod, bMod);
	const BigInt& minVal = min(aMod, bMod);

	const int* minuend = maxVal.data;
	const int* subtrahend = minVal.data;

	int aDigit = 0;
	int bDigit = 0;

	int loan = 0;
	int res = 0;

	std::string str;

	while (i >= 0) {
		aDigit = *(minuend + i) - loan;
		bDigit = j >= 0 ? *(subtrahend + j) : 0;

		if (aDigit == 0 && i == 0 && j < 0) {
			break;
		}
		else if (i >= 0 && j < 0) {
			res = aDigit;
		}
		else if (aDigit >= bDigit) {
			res = aDigit - bDigit;
			loan = 0;
		}
		else if (aDigit < bDigit && i > 0) {
			res = 10 - bDigit + aDigit;
			loan = 1;
		}

		str.insert(0, std::to_string(res));

		i--;
		j--;
	}

	bool isMaxValIsNegative = maxVal == thisVal ? thisVal.isNegative() : value.isNegative();
	bool isMaxValIsRightVal = aMod != bMod && minVal == aMod;

	if (str.at(0) == '0') {
		int k = 1;
		while (k < str.size() - 1 && str.at(k) == '0')
		{
			k++;
		};
		str = str.substr(k, str.size() - 1);
	}

	BigInt bi = BigInt(str);

	if (isMaxValIsNegative || isMaxValIsRightVal) {
		bi.makeNegative();
	}

	return bi;
}

BigInt BigInt::add(const BigInt& value) const {
	BigInt thisVal = *this;

	int i = getSize() - 1;
	int j = value.getSize() - 1;

	const int* term1 = this->data;
	const int* term2 = value.data;

	int index = 0;
	int transfer = 0;
	int res = 0;

	std::string str;

	while (i >= 0 || j >= 0) {
		int aDigit = *(term1 + i);
		int bDigit = *(term2 + j);

		if (i >= 0 && j < 0) {
			res = aDigit + transfer;
		}
		else if (j >= 0 && i < 0) {
			res = bDigit + transfer;
		}
		else {
			res = aDigit + bDigit + transfer;
		}

		transfer = 0;

		if (res >= 10) {
			res = res % 10;
			transfer = 1;
		}

		str.insert(0, std::to_string(res));

		i--;
		j--;
	}

	if (transfer == 1) {
		str.insert(0, std::to_string(transfer));
	}

	if (thisVal.isNegative() && value.isNegative()) {
		str.insert(0, "-");
		return BigInt(str);
	}

	BigInt aMod = abs(thisVal);
	BigInt bMod = abs(value);

	if (aMod < bMod) {
		str.insert(0, "-");
	}

	return BigInt(str);
}

BigInt BigInt::operator+(const BigInt& value) const {

	const BigInt& thisVal = *this;

	char lsign = sign;
	char rsign = value.sign;

	if (lsign - rsign == 0) {
		return thisVal.add(value);
	}
	else if ((lsign - rsign) != 0) {
		return thisVal.substruct(value);
	}
}


BigInt BigInt::operator-(const BigInt& value) const {
	const BigInt& thisVal = *this;

	int i = size - 1;
	int j = value.size - 1;

	char lSign = sign;
	char rSign = value.sign;

	if (lSign - rSign == 0) {
		return thisVal.substruct(value);
	}
	else if ((lSign - rSign) != 0) {
		BigInt res = thisVal.add(value);
	}

	return BigInt();
}

BigInt BigInt::operator/(const BigInt& divider) const {
	int dividendSize = this->size;
	int dividerSize = divider.getSize();

	if (dividendSize < dividerSize) {
		return 0;
	}
	
	int dividendScale = dividendSize;
	int dividerScale = dividerSize;

	std::string dividendNormStr = toString().insert(0, "0.");
	std::string dividerNormStr = divider.toString().insert(0, "0.");

	double dividendNorm = std::stod(dividendNormStr);
	double dividerNorm = std::stod(dividerNormStr);

	double x0 = 1 / dividerNorm;


	for (int i = 0; i < 5; i++) {
		x0 = x0 * (2 - dividerNorm * x0);
	}

	double value = dividendNorm * x0 * std::pow(10, std::abs(dividendScale - dividerScale));


	BigInt result =  BigInt(int(value));

	if (sign != divider.sign) {
		result.makeNegative();
	}
	
	return result;
}


BigInt BigInt::operator*(const BigInt& value) const {
	
	int i = this->size;
	int j = value.getSize();

	char sign1 = this->getSign();
	char sign2 = value.getSign();

	const int* multiplier1 = nullptr;
	const int* multiplier2 = nullptr;

	int endSize = i + j;
	int* endResult = new int[endSize]{0};

	int multiplyTransfer = 0;
	int sumTransfer = 0;
	int offset = 0;

	int maxIndex = std::max(i, j);
	int minIndex = std::min(i, j);

	if (maxIndex == i) {
		multiplier1 = this->data;
		multiplier2 = value.data;
	}
	else {
		multiplier1 = value.data;
		multiplier2 = this->data;
	}

	for (int k = minIndex - 1; k >= 0; k--) {
		std::string strSum;
		std::string strMultiply;
		int endIndex = endSize - 1;
		int digit2 = *(multiplier2 + k);

		for (int l = maxIndex - 1; l >= 0; l--) { 

			int digit1 = *(multiplier1 + l);
			int product = digit1 * digit2 + multiplyTransfer;
			multiplyTransfer = 0;
			if (product >= 10) {
				multiplyTransfer = product / 10;
				product = product % 10;
			}

			int* p = endResult + endIndex - offset;
			int sum = *p + product + sumTransfer;
			sumTransfer = 0;
			if (sum >= 10) {
				sumTransfer = sum / 10;
				sum %= 10; 
			}

			*p = sum;
			endIndex--;
		}

		if (multiplyTransfer > 0 || sumTransfer > 0) {
			*(endResult + endIndex - offset) = multiplyTransfer + sumTransfer;
			multiplyTransfer = 0;
			sumTransfer = 0;
		}
		offset++;
	}
	
	if (sumTransfer > 0) {
		*endResult = sumTransfer;
	}

	std::string str;
	int strIndex = *(endResult) == 0 ? 1 : 0;

	for (size_t m = strIndex; m < endSize; m++) {
		int val = *(endResult + m);
		str.append(std::to_string(val));
	}

	if (sign1 != sign2) { //����� ������ ������� BigInt, � ����� � ������ ������������� �������� ��� ����. ��� ����� �����������
		str.insert(0, "-");
	}

	delete[] endResult;
	
	return BigInt(str); 
}

BigInt BigInt::operator*(const long long& value) const {
	return *this * BigInt(value);
}

bool BigInt::operator<(const BigInt& value) const {
	return max(*this, value) == *this ? false : true;
};

bool BigInt::operator>(const BigInt& value) const {
	return value < *this;
};

bool BigInt::operator>=(const BigInt& value) const{
	return *this == value || *this > value;
}

bool BigInt::operator<=(const BigInt& value) const {
	return *this == value || *this < value;
}

std::string BigInt::toString() const {
	std::string str;
	for (int i = 0; i < this->size; i++) {
		str.append(std::to_string(this->data[i]));
	}

	if (isNegative()) {
		str.insert(0, 1, sign);
	}

	return str;
}

bool BigInt::pushBackDigit(int digit) {
	if (digit > 9 || size == capacity) {
		return 0;
	}

	data[size] = digit;
	++size;

	return 1;
}

BigInt BigInt::operator=(const BigInt& value) {
	sign = value.sign;
	size = value.size;

	int i;

	for (i = 0; i < capacity; ++i) {
		if (i < value.size) {
			data[i] = value.data[i];
		}
		else {
			data[i] = 0;
		}
	}

	return *this;
}


