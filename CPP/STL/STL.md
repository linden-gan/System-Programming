## C++ STL
- Containers: store collection of objects. But C++ containers store by values, which means it needs copy a lot.
- Examples:
- vector: dynamically resizable array. `#include <vector>`, `vector<Tracer> vec;`
  - When insert, resize, sort, this container will make copies...
  - iterator: `vector<Tracer>::iterator it;`: an iterator class associated with vector class
    - iterator overrides lots of operators....
    - `*it` dereference to get element
    - `it++` to move forward by one element
    - `it = vec.begin()`: `vec.begin()` returns an iterator pointing to the first element.
    - `it = element`: move our iterator to this element.
    - `for (auto it = vec.begin(); it < vec.end(); it++) { ... }`
    - `vec.end()` returns an iterator pointing to one element past the last element.
    - `auto` is for type inference
    - Even simpler: for each loop: `for (auto element : container) { cout << element << endl; }`

- STL Algorithms
  - `for_each(vec.begin(), vec.end(), &Print);`: a syntax sugar of for loop . `&Print` is a function pointer.
  - `sort(vec.begin(), vec.end(), optional &comp);`
  - `min_element(vec.begin(), vec.end(), optional &comp)`
  - `binary_search(vec.begin(), vec.end(), optional &comp)`
  - C++ anonymous function: `[](type param1, type param2) { ... }`
 
- list: actually a doubly-linked list.
  - so it doesn't support array-like access `lst[2]`
- map: associative collection with an underlying structure `Pair<>`, implemented as a search tree O(log n).
  - `map<K, V> table;`
  - map also overrides lots of operators....
  - `V result = table[a];`: access a
  - `table[a] = b;`: insert pair (a,b)
  - `table[a];`: will just insert a pair (a, ?), where ? is the default
    declaration of type V.
  - `table.find(a);`: if found, return an iterator pointing to the key value pair `pair`. 
    If not found, return `table.end()`.
  - map will be sorted automatically.
- unordered_set: O(1)