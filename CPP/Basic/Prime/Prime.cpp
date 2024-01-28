#include <algorithm>
#include <cassert>
#include <set>

namespace PrimeLib
{
bool isPrimeBasic(int n) {
    assert(n > 1);
    if (n == 4) {
        return false;
    }
    for (int f = 3; f <= n / 2; f += 2) {
        if (n % f == 0) {
            return false;
        }
    }
    return true;
}

bool isPrime(int n, const std::set<int>& table = std::set<int>()) {
    if (table.size() < 3) {
        return isPrimeBasic(n);
    } else {
        return isPrimeByTable(n, table);
    }
}

bool isPrimeByTable(int n, const std::set<int>& table) {
    int maxPrime = *table.end();
    if (n <= maxPrime) {
        return table.find(n) != table.end();
    }
    // cbegin: constant iter: won't change the value this iter points to
    // [&n]: capture list: capture n to this lambda from outsides by reference
    std::for_each(table.cbegin(), table.cend(), [&n](const int& p){
        // if (p > n / 2) {
        //     return true;
        // } this looks faster but the if statement actually doubles the time
        if (n % p == 0) {
            return false;
        }
    });
    for (int f = maxPrime + 2; f <= n / 2; f += 2) {
        if (n % f == 0) {
            return false;
        }
    }
    return true;
}
} // namespace Prime
