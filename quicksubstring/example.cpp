#include <iostream>
#include "quicksubstring.h"

int main() {

	qs::ProcessingUnit pu("ababba"); // For each string there must be a different processing unit

	std::cout << (pu.Substr("abba") ? "abba is a substring of ababba\n" : "abba is not a substring of ababba\n");
	std::cout << (pu.Substr("baba") ? "baba is a substring of ababba\n" : "baba is not a substring of ababba\n");
	std::cout << (pu.Substr("ba") ? "ba is a substring of ababba\n" : "ba is not a substring of ababba\n");

	return 0;
}