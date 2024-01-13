## C++ Class
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
  - `Point::Point(const Point& src): x_(src._x), y_(src._y) { }`
  - `Point src(1, 3);`
  - `Point des1(src);`
  - `Point des2 = src;`
  - If you don't define your own, C++ can make a synthesized one with simplest
    behavior (only do shallow copy)
  - Copy is used when pass an object as a parameter or return an object or assign
    one object to the other.
- Overload operator:
  - Overload the assignment sign = (called assignment constructor)
  - `Point& Point::operator=(const Point& src) {`
    - `if (this != &src) {  // check whether this points to src. if so, we are
      assigning an object to itself!`
      - `x_ = src.x_;`
      - `y_ = src.y_;`
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