## Smart Pointer
- A kind of pointer that helps us automatically delete object when no pointer on it. `#include <memory>`
- Store smart pointers in STL data structure to avoid copy.
  `vector<shared_ptr<Point>> vec;`
- `shared_ptr<int> sp(new int(3));` multiple smart pointers share one data. 
  Use reference count to record how many pointers now pointing to this data.
  If count = 0, free the data.
  - `share_ptr<int> copy_ptr(sp);` copy constructor
  - `sp.use_count()` return count reference
  - `sp.unique()` return true if count == 1
- `unique_ptr<int> sp(new int(5));` only one unique pointer is allowed per data.
  Copy constructor and assignment operator overload are both disabled.
  - How to transfer the unique ownership?
  - `x.release();` return the pointer that x contains. Cancel x's ownership to it
    so now x holds `nullptr`
  - `unique_ptr<int> y(x.release());` transfer x's ownership to y so now x holds
    `nullptr`
  - `z.reset(y.release())` z free its old value to reset to y's value; at the
    same time y transfer its ownership to z so now y holds `nullptr`
  - Move semantics: `unique_ptr<int> b = move(a);` so now `a` holds `nullptr`
- `weak_ptr<int> wp;` we cannot dereference a weak pointer, and weak pointer
  doesn't count for reference.
  - can resolve reference cycle problem (two struct have two smart pointers pointing to
    each other, so they will never be deleted).
  - `w.lock()` return a derived shared pointer, usually jointly used with
    `shared_ptr<int> x = w.lock();`.
  - `w.expired()` return whether w is already a dangling pointer or not.
    Dangling means the data the weak pointer points to has been deleted.
  
- Drawbacks of smart pointers: 
  - Smart pointers cannot tell whether data is in heap or stack.
  - Smart pointers may reuse a raw pointer.