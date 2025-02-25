#include <vector>

template<typename T>
class CuckooSet {
private:
    std::vector<T> _table;
    int _size;

    int hash1(const T& key) {
        return std::hash<T>(key) % _table.size();
    }

    int hash2(const T& key) {
        return (std::hash<T>(key) * 7) % _table.size();
    }

public:
    CuckooSet(int capacity = 17) : _table(capacity), _size(0) {}

    bool insert(const T& key) {
        int i1 = hash1(key);
        int i2 = hash2(key);
        return false;
    }
};