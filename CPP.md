## C++
### C++ Basic
- scope resolution operator `::`
  - used to mark a function or class to its associated class or namespace.
- Include:
  - almost like C, but no `.h` anymore.
  - for C's header like `<stdlib.h>`, change to `<cstdlib>`.
- Namespace:
  - `include` only includes file, which is not equal to using namespace.
  - namespace creates a scope where name collision inside the scope is not allowed, but outside is allowed.
  - A namespace may spread multiple files, like `std::cout` in `<cstream>`, `std::string` in `<cstring>`.
  - Usually we need qualifier like `std::` to qualify an object if we use it outside of the namespace.
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
  - Unlike pointer, when we create a reference, we must initialize it. And this reference cannot change to refer
    another thing after it's created.
- const: `const int i`
  - i will not change within current function *scope* (current function, 
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
    
### C++ Class
- Seperation of declaration and definition.
- Initialization: `Point p;  // default constructor`, 
  `const Point p(x1, x2);  // construct a constant point (its members cannot be changed)`
- const method: `bool Compare(const Point p1, const Point p2) const {...}`
  - method that won't change the object's fields.
  - a constant object can only be called on its constant method.
- class's members are private by default; struct's members are public by
default.
- Convention: use `x_`, `y_` for private member in a class.
- `this`: a constant pointer to itself.

- constructor
  - default constructor: constructor that doesn't take any arguments
  - default synthetic constructor: when you don't define any constructor,
  system will make one for you which doesn't take any arguments and will put
  garbadge data to members that are primitive data and call default constructor
  for members that are objects. If you have reference or const member, it will fail.
  If you defined any ctor, system will not generate default synthetic ctor.
  - `Point arr[3];`: initialize an array of Points by calling each Point's
  default constructor.
  - Initialization: `Point(const int x, const int y, const int z): x_(x), 
    y_(2 * y), z_(z + 3) { }`
    - before ctor body, compiler will first initialize things in the list.
    - the initialization order is determined by the
      members' declaration order, not by order in the list.
    - members that are not in the list will be
      initialized by their default ctor first before actual constructor body.
- Copy constructor:
  - construct an object by copying an existing one. Previously we don't have this object,
    different from assignment construction where it assign/copy an object to an existing one.
  - `Point::Point(const Point& src): x_(src._x), y_(src_y) { }`
  - `Point src(1, 3);`
  - `Point des(src);`
  - `Point des1 = src;`
  - If you don't define your own, C++ can make a synthesized one with simplest
    behavior (only do shallow copy)
  - Copy is used when pass an object as a parameter or return an object or assign
    one object to the other.
- Overload operator:
  - Overload the assignment sign = (called assignment construction)
  - `Point& Point::operator=(const Point& src) {`
    - `if (this != &src) {  // check whether this points to src. if so, we are
      assigning an object to itself!`
      - `x_ = src.x_;`
      - `y_ = src.y+;`
    - `}`
    - `return *this;  // return a reference of the object {this} points to`
    - If you don't define your own, C++ can make a synthesized one with simplest behavior
- Destructor: `Point::~Point() {}`
  - No need to call destructor. When a stack object is out of scope, C++ will automatically
  call its destructor. For heap object, we must use `delete` keyword to invoke destructor to free it from memory.
  - Destructor destruct things in reverse order they are constructed.
- Destructor, Copy constructor, Assignment constructor usually come all together or not
at all.
- When you don't want to define your own constructor:
  - `Point() = default;`, `Point(const Point& src) = default;`
- When you want to disable user to call some copy constructor or assignment constructor:
  - `Point& operator=(const Point& src) = delete;`

- Nonmember function:
  - Declared outside of the class scope, though still in the header file.
  - When writing definition in .cc file, do not need to attach the class's namespace before
    it like `double Point::Distance(const Point& p1, const Point& p2);`. Just write `double 
    Distance(const Point& p1, const Point& p2);`.
  - Don't have access to the class's non-public members (cannot directly read or write, but
    can do that by getter() and setter()).
    - but we can use `friend` to give non-member function access to non-public fields.
      It needs to be declared within the class scope.
  - Don't attached to an object (`object.function()`) when it is called.
  - Actually, nonmember function "of a class" can be not relevant to that class at all. (just like `printf()`, `sort()`)
  - We use nonmember when not modifying this class but return a new object, or when the operator is commutative.

- static function & field
  - Independant from individual instance. Shared by all instances.
  - `class::stat_function();`

- use `nullptr` instead of `NULL`
- `new`/`delete` is just like `malloc()`/`free()`:
  - `Point* p1 = new Point(1, 2, 3);`, `int* num = new int(333);`, `int* arr = new int[size];`
  - `delete p1;`, `delete[] arr;`
    - When stack objects falls out of scope, their destructors will be automatically
      called in reverse order they were created, so we don't need to manually use `delete`.
    - which means if a *pointer* falls out of scope, compiler will just
      clean the pointer, so the data pointed by the pointer will cause leak.
    - so whenever we used new to create a heap object, we need delete it.
  - We can safely ignore the exceptions thrown by new or delete.
  
### Polymorphism
- Template: type parameter, written as the first token of function or class
  - `template <typename T>`
  - `int compare(const T &value1, const T &value2);`
  - for main:
  - `compare<Thing>(t1, t1);  // or we can let compiler to infer type`
  - In compile time, functions or classes declared by `template` will be ignored.
  - This creates a problem: the object.o file will be empty.
  - Solution: don't write object.c; just put all implementation into object.h, and include
  the object.h in main to compile them together.
    
### C++ STL
- Containers: store collection of objects. But C++ containers store by values, which means it needs copy a lot.
- Examples:
- vector: dynamically resizable array. `vector<Tracer> vec;`
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
  
### Smart Pointer
- A kind of pointer that helps us automatically delete object when no pointer on it.
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
  - `unique_ptr<int> y(x.release());` transfer x's ownership to y so now y holds
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
  
### Inheritance
- `class Child : public Mother, Father { ... };`
  - Can have multiple parents. Almost always we want public inheritance (
    parents' public members will still be public, private will still private).
    For private inheritance, things are weird.
- Dynamic dispatch: for `B` derived from `A`, `B b();`, `A* a = &b;`, when call `a.func();`,
  always choose B's function to invoke if B has one, because we always choose the most derived
  (bottom of the inheritance tree) method to invoke.
  - use `virtual` to indicate this function (and its child functions) will be
    added to the virtual table, which means they will be dynamically dispatched.
  - virtual functions in base class are open to be overrided by functions in derived class.
  - `virtual string function() = 0;` a "pure" virtual function. Doesn't have any
    implementation. Make the class an abstract class (an interface).
  - use `override` to indicate this function override parents' virtual function.
  - Stylistically, just use `override` on all child functions whose base function
    is `virtual`
- Static dispatch: when we don't use `virtual` keyword. Always look for functions in the promised type.
- ctor cannot be inherited. Child should have its own ctor.
  - if child has none (synthesized ctor needed), then compiler will first invoke
    parent's default ctor, then initialize child's remaining members by default. If
    parent has no default ctor, then compiler error.
  - there's no `virtual` ctor
  - If parent contains only member `x`, and child contains `y` and inherit `x`,
    then we can write child's constructor: `Child(int x, int y): Parent(x), y_(y);`
- dtor can be dispatched. When destruct a child, we first invoke its own dtor, then
  invoke its base class's dtor.
  - if we statically dispatch a dtor, promised type (parent)'s dtor will be invoked,
    so actual type (child) 's additional members may not be cleaned. Static dispatching
    a dtor is almost always a mistake.
  - Good practice to declare dtor as virtual.
- Assignment
  - Usually, we cannot assign parent to child.
  - But if we assign child to parent, some members of child will be lost. It's called object slicing.
  - `list<Parent> li; li.push_back(child); // some child's members will be lost`
  
### Casting
- `Parent* p = static_cast<Parent*>(&child);` checked only for compile time.
  - `p` is `nullptr` if failed.
  - can cast pointers, not reference, of related types.
  - compile time error if types are not related.
  - can cast child to parent (related types).
  - can cast parent to child (casting downward), but dangerous.
  - can cast `void*`/`T*` to `T*`/`void*`.
  - can cast between `float` `int` `long` ...
  - can cast between any well-defined conversion.
- `Parent* p = dynamic_cast<Parent*>(&child);` checked for both compile and runtime.
  - `p` is `nullptr` if failed.
  - can cast pointers or reference of related types.
  - compile time error if types are not related.
  - because it will check dynamically, runtime error will occur if we cast
    a *real* parent object to child (casting downward), but if the parent is just a pointer (its actual type
    is child), then it's okay and obligated to use dynamic casting, since static casting won't work.
- `void* ptr = reinterpret_cast<void*>(num)` cast unrelated types with same size. Reinterpret the bit data.
  - `void*` to `long`
