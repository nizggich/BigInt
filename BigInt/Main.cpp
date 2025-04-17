#include "BigInt.h"
#include <iostream>

int main() {

	BigInt a = 100;
	BigInt b = 150;
	BigInt c = 150;
	BigInt d = 88;
	BigInt e = 77;
	BigInt f = -200;
	BigInt g = 50;
	BigInt g2 = -450;
	BigInt g3 = 50;
	BigInt k = 99;
	BigInt l = 1;

	BigInt res = b - a;  //50
	BigInt res1 = b - c; //0
	BigInt res2 = e - d; //-11
	BigInt res3 = b + c; //300
	BigInt res4 = f + g; //-150
	BigInt res5 = g2 + g3; //-400
	BigInt res6 = k + l; //100
	BigInt res6 = k + l; //100

	std::cout << std::abs(-9);

}