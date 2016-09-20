#define ll long long

ll modPow(ll a, ll x, ll p) {
	// return a^x mod p
	ll res = 1;
	while (x>0) {
		if (x & 1) res = (res*a) % p;
		a = (a*a) % p;
		x >>= 1;
	}

	return res;
}

ll modInverse(ll a, ll p) {
	// return modular multiplicative of: a mod p, assuming p is prime
	return modPow(a, p - 2, p);
}

ll modBinomial(ll n, ll k, ll p) {
	// return C(n,k) mod p, assuming p is prime
	ll numerator = 1; // n*(n-1)* ... * (n-k+1)
	int i;
	for (i = 0; i<k; i++) numerator = (numerator*(n - i)) % p;

	ll denominator = 1; // k!
	for (i = 1; i <= k; i++) denominator = (denominator*i) % p;

	ll res = modInverse(denominator, p);
	res = (res*numerator) % p;
	return res;
}
