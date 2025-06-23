#include "BigInt.h"
#include <iostream>
#include <stdio.h> 
#include <time.h>

int main() {


	

	BigInt a("23423647823674623"); // это большее
	BigInt b("287879074359889"); // это меньшее

	BigInt c = a * b;
	int a1 = 82345678 * 8;
	long long a2 = 82345678 * 8;
	std::cout << a1 << "\n" << a2;


	//348 * 1234 = 
	//1. 9872 
	//2. 4936  
	//3. 3702
	//res = 429432
}