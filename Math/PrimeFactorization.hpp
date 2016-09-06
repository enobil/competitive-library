#ifndef PRIME_H
#include "Prime.hpp"
#endif

class PrimeFactorization{
    Prime *_prime;
  public:
    PrimeFactorization(Prime*);
    std::vector<int> factorList(int);
};

PrimeFactorization::PrimeFactorization(Prime *prime){
    _prime = prime;
}

std::vector<int> PrimeFactorization::factorList(int n){
    std::vector<int> v;
    int x = n;
    _prime->isPrimeDyn(n);
    auto it = _prime->list.begin();
    auto itend = _prime->list.end();
    while(x > 1 && it != itend){
        register int i = *it;
        while(!(x % i)){
            v.push_back(i);
            x /= i;
        }
        it++;
    }
    return v;
}
