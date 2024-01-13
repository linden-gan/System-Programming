## Casting
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