## Polymorphism
- Template: type parameter, written as the first token of function or class
  - `template <typename T>`
  - `int compare(const T &value1, const T &value2);`
  - for main:
  - `compare<Thing>(t1, t1);  // or we can let compiler to infer type`
  - In compile time, functions or classes declared by `template` will be ignored.
  - This creates a problem: the object.o file will be empty.
  - Solution: don't write object.c; just put all implementation into object.h, and include
  the object.h in main to compile them together.
## Inheritance
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
  