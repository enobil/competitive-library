#define BITMANIPULATION_H
#include <cassert>

int count1s(int n) {
	int r = 0;
	while (n) { r += n % 2; n /= 2; }
	return r;
}

int lg2(int n) {
	int r = -1;
	assert(n > 0);
	while (n) { r++; n /= 2; }
	return r;
}

int pow2Ceil(int n) {
	if (count1s(n) == 1)
		return n;
	return 1 << (1 + lg2(n));
}
