#include <unordered_set>
#include <set>  // order is important because we wan to check from the smallest prime factor

#ifndef PRIME_H_
#define PRIME_H_
namespace PrimeLib
{
bool isPrimeBasic(int n);

bool isPrime(int n, const std::set<int>& table = std::set<int>());

bool isPrimeByTable(int n, const std::set<int>& table);

bool isPrimeMultiThreads(int n);
}
#endif