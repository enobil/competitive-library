#include <cmath>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <cassert>
#define PRIME_H

class Prime{
    bool isPrimeDynSub(int);
    int _maxPrime = 3;
    int _capacity;
  public:
    Prime(int size);
    bool isPrime(int);
    bool isPrimeDyn(int);
    bool *set;
    std::vector<int> list;
};

Prime::Prime(int size){
    _capacity = size;
    set = (bool*) malloc(sizeof(bool) * size);
    memset(set, false, sizeof(bool) * size);
    set[2] = true;
    set[3] = true;
    list.push_back(2);
    list.push_back(3);
}

bool Prime::isPrimeDyn(int n){
    assert(n < _capacity);
    if(_maxPrime >= n)
        return set[n];
    for(_maxPrime+=2; _maxPrime<n; _maxPrime+=2){
        if(isPrimeDynSub(_maxPrime)){
            set[_maxPrime] = true;
            list.push_back(_maxPrime);
        }
    }
    if(isPrimeDynSub(_maxPrime)){
        set[_maxPrime] = true;
        list.push_back(_maxPrime);
    }
    return set[n];
}

bool Prime::isPrimeDynSub(int n){
    if(n % 3 == 0)
        return false;
    int l = sqrt(n) + 1;
    for(auto it = list.begin(); it != list.end(); it++){
		if (*it > l)
			break;
        if(!(n % (*it)))
            return false;
    }
    return true;
}

bool Prime::isPrime(int n){
    if(n == 2 || n == 3)
        return true;
    if(n % 2 != 0 || n % 3 != 0 || n < 2)
        return false;
    int l = sqrt(n) + 1;
    for(int i=5; i<=l; i+=2){
        if(n % i == 0)
            return false;
    }
    return true;
}
