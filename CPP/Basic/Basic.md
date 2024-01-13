## C++ Basic
- scope resolution operator `::`
  - used to mark a function or class to its associated class or namespace.
- Include:
  - almost like C, but no `.h` anymore.
  - for C's header like `<stdlib.h>`, change to `<cstdlib>`.
- Namespace:
  - `include` only includes file, which is not equal to using namespace.
  - namespace creates a scope where name collision inside the scope is not allowed, but outside is allowed.
  - A namespace may spread multiple files, like `std::cout` in `<cstream>`, `std::string` in `<cstring>`.
  - Usually we need qualifier like `std::` to qualify an object if we use is outside of the namespace.
  - For objects not in any namespace, we don't need qualifier.
  - We can omit the qualifier by `using std`: use all objects inside std (not very good).
  - Or we can only `using std::string`: better.
- Reference: creating alias: `int& y = x`, so y and x refer to the same thing.
Useful when passing reference to a function. (Reference is a better pointer: we
don't need to dereference it.).
  - `swap(a, b);`
  - `int swap(int& x, int& y) {...}`
  - change x and y is equivalent to change a and b.
  - Use reference for input parameter, const pointer for output parameter.
  - Unlike pointer, when we create a reference, we must initialize it. And this reference cannot change to refer another thing after it's created.
- const: `const int i`
  - `i` will not change within current function *scope* (current function, 
    the callee, callee's callee). const parameter cannot be changed
    inside a function.
  - We can pass a const/non-const as a const parameter, but we cannot pass
  a const as a non-const parameter: try to declare parameters that won't change
  as const for better flexibility for your function.
  - `int* const p = &x`: a constant pointer: the pointer itself's value cannot
  be changed.
  - `const int* p = &x`: a pointer that points to some constant data types.
  We can change where the pointer points to, but we cannot change the
  data by dereferencing the pointer.
  - `const int* const p = &x`: both a constant pointer and points to some
  constant data type.
  - `const int& p = x`: create a constant reference: cannot change the data
  via this reference.