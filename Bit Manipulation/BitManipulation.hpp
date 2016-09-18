#define BITMANIPULATION_H
#include <cassert>

int setBits_naive(unsigned long long n) {
	int r = 0;
	while (n) { r += n % 2; n >>= 1; }
	return r;
}

int setBits_optimized(unsigned long long n){
    int r = 0;
    while (n) { n &= (n - 1); ++r; }
    return r;
}

int lg2(int n) {
	int r = -1;
	assert(n > 0);
	while (n) { ++r; n >>= 1; }
	return r;
}

unsigned long long pow2Ceil(int n) {
	if (count1s(n) == 1)
		return n;
	return (unsigned long long)1 << (1 + lg2(n));
}
