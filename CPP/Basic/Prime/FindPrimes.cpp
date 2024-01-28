#include <algorithm>
#include <cassert>
#include <fstream>
#include <set>
#include "Prime.h"

using namespace PrimeLib;

// return a pointer (stack space is limited) to a set of primes in range [min, max)
std::set<int>* getPrimesInRangeByTable(int min, int max, const std::set<int>& table) {
    assert(min >= 2 && max > min);
    std::set<int>* res = new std::set<int>();
    if (min == 2) {  // special case...
        res->insert(2);
        min++;
    }
    if (min % 2 == 0) {  // always starts from odd num so we can hop by 2
        min++;
    }
    for (int n = min; n < max; n += 2) {
        if (isPrime(n, table)) {
            res->insert(n);
        }
    }
    return res;
}

int main() {
    int max = 9999999;
    std::ofstream file;
    file.open("primes");
    std::set<int>* primes = new std::set<int>();
    int left = 2;
    int right = 50;
    while (left < max) {
        std::set<int>* ret = getPrimesInRangeByTable(left, right, *primes);
        std::set<int>* newPrimes = new std::set<int>();
        std::set_union(primes->cbegin(), primes->cend(), ret->cbegin(), ret->cend(), newPrimes->begin());
        std::swap(primes, newPrimes);
        delete ret;
        delete newPrimes;
        left = right;
        right = std::min(right * 2, max);
    }
    file << primes << std::endl;
    delete primes;
    return 0;
}