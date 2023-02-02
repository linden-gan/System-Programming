## C
### C main args
> `int main(int argc, char* argv[]) {`
- argc: arg count
- argv: arg vector
- ./foo -w 66
  - argc = 3, argv[0] = "./foo", argv[1] = "-w", argv[2] = "66"
    (they are all strings)

### GCC
Standard: `gcc -Wall -g -std=c17 hello1.c hello2.c -o hello`.  
`-g`: debug flag  
`-o`: specify output name (no matter object or binary file).   
`-c`: `gcc -Wall -g -std=c17 -c hello.c -o hello.c`: only compile a .c file to object file without linking.

### Array & String
`int arr[] = {1, 2, 3};` or `int arr[3] = {1, 2, 3};` or `int arr[5] = {1, 2, 3};` (has two garbadge buckets)  
`int arr[5] = {0};` or `int arr[5] = {}`: shortcut: five 0's  
`int arr[5];`: a placeholder of 5 garbadges.  
`arr` is a pointer to the array.  
`sizeof(arr);` to know array's size (only work in current scope of arr).  
String array: `char* str` or `char str[] = "Hi";` or `{'H', 'i', '\0'};`  
By the same token, `str` is a pointer to the string.  

Note: for any primitive data types (including those inside struct), if we don't initialize them, they will be garbadges.  
For array, if we `int arr[4];` then it will be garbadges; if we `int arr[4] = {}` then it will be 0's.  

Note: in `char* arr = "Hi";` arr points to a string literal array in static memory, so it can't be modified. Use `char arr[] = "Hi";` if want to modify the string, since it makes a copy of string array in stack.   

String as output parameter:
    
    generate_string(char** s) {  // char** for string output parameter
        *s = "hello";  // in static memory, use strcpy() if want it modifiable
    }
    
    char* res;
    generate_string(&res);
    printf("%s\n", res);


### Error & Exit
- process exit, aka return from main, with status code like exit(0).
  0 means EXIT_SUCCESS. Other numbers mean EXIT_FAILURE.
- Or we can do: return EXIT_FAILURE; return EXIT_SUCCESS;

### Output Parameter
Caller produce and hold data, and pass its reference to callee to let
callee to just modify it.
1. Allocate space for the data. E.g. char* str;
2. Pass this data's ADDRESS to callee. E.g. callee(&str);
3. Inside callee, DEREFERENCE the passed address to modify. E.g.
*str = "Hello\n";
4. After callee, caller can directly use the data. E.g. printf(str);

### Functional pointer

    int negate(int i) {
        return -i;
    }

    int square(int i) {
        return i * i;
    }

    void map(int arr[], int size, int (*operation)(int n)) {
        int i;
        for (i = 0; i < size; i++) {
            arr[i] = (*operation)(arr[i]);  // dereference func ptr and plug in param
        }
    }

    int main(int argc, char** argv) {
        int arr[] = {0, 1, 2, 3};
    // rt type  ptr name  param
        int (*func_ptr)(int n) = negate;  // initialize a func ptr pointing to negate()
        map(arr, 4, func_ptr);

        int i;
        for (i = 0; i < sizeof(arr); i++) {
            printf("%d\n", arr[i]);
        }
    }
    

### malloc() & free()
- `int* num = (int*) malloc(100 * sizeof(int));  // allocate
space in heap to store an array of 100 integers. Return NULL if
allocate failure.`
- free(pointer): pointer must point to the first address of the block
- DO NOT double free
- Always remember to free() after malloc()
- change the pointer to NULL after freed it (defensive programming).

### struct
`struct student { int id; float score };`

`struct student s1 = {2363670, 4.0};`

`struct student s2 = {2363622, 3.0};`

`s2 = s1  // copy and overwrite s1's field to s2's; still have 2
objects, but with exactly same field values`

- So, when passing struct as parameter, compiler simply copy a struct 
  in the callee (everything is passed by value in C), which means changing
  it inside callee would have no effect outside.
- Returning struct is also just copying. We can return a small struct 
  by %rax, which is more efficient, but for larger structs, it's
  better to do malloc or output parameter.
- `typedef long long int lli`: the last token is the alias.
- `typedef struct point_st { int x; int y; } Point, *PointPtr;` define aliases for point struct and its pointer at the 
same time.

### Module, Header File, Preprocessor, Global
- .h file: the interface that only contains declaration and prototype of
a module
- Preprocessor: merely a text replacer directed by #include, #define
  - `cpp -P example.c`: preprocess `example.c` and output the preprocessed version .c file
  - for example: replace `#include "ll.h"` by prototypes in "ll.h"
- Problem: C file includes A and B file, but A file also includes B
file...
  - Solution: header guard: `#ifndef FOO_C_` `#define FOO_C_`... `#endif`
- Macro: `#define PI 3.14`, `#define FOO(x) x + 10`: first token is defined variable, the remains are its value
  - or you can just `#define DEBUG` without value, which serves as a flag
- Command line Define flag: `-D...`
  - `gcc -Wall -g  -DTRACE -o hello hello.c`
  - Code: 
  - `#ifdef TRACE`
  - `#define DEBUG(f) printf("%s\n", f) \\ define DEBUG to debug function`
  - `#else`
  - `#define DEBUG(f) \\ define DEBUG to nothing (ignore it)`
  - `#endif`
- external libraries (like `stdlib.h`, `string.h`) are dynamically linked to .o files
- Functions and global variables are `extern` by default. `extern`
means they can access and can be accessed by things outside of this 
file. Multiple extern variables will be resolved to one location. So, `extern` is an indicator that the definition or declaration is elsewhere.
- `static` + global variable means variables can only be accessed by things in this file (internal linkage). Good to defend personal global variables.
- `static` + local variable means a variable that is created in compiling
time, so it won't vanish after its function's frame.
- `static` + function means the function has internal linkage. Other files cannot see it.
  
### I/O
- ERRNO: global variable for error. When error occurred, program sets
  ERRNO to specific error code.
- perror(message): print customized \<message\> (like "Oops, something
  wrong") and tag with the actual source of error, ERRNO. Use when there might
  be multiple sources of errors
- fread(), fwrite(): use buffer internally to minimize disk access, 
return an Unsigned int for the num of bytes actually read/write, 
implemented by POSIX API functions like read(), write().
- POSIX functions: read(), write(): take a file descriptor instead of
  stream as parameter to indicate where it read/write from, return a 
  Signed int for the num of bytes actually read/write. -1 for error.
- open() return an int as file descriptor to indicate which file it is, 
which is similar to FILE* returned by fopen(). -1 for error.
- DIR *opendir(const char* name): return a directory pointer, NULL for
error.
- struct dirent *readdir(DIR *dirp): return a directory's entry, from
., .., to first_file, second file, ... Each call advances to next file.
NULL for error or reaching the end of directory
- printf("%s\n", direntry->d_name);  // print this entry's name

### Make
- Makefile format: 
- `target: source1 source2 ...`
  - `command`
- make -f <path/to/makefile> target
  - default: if no -f, use Makefile in current directory; if not target,
  use the first target in Makefile as target.
- Can use phony targets like clean, all, for convenience.

## C++
### C++ Basic
- Include:
  - almost like C, but no `.h` anymore
  - for C's header like `<stdlib.h>`, change to `<cstdlib>`
- Namespace:
  - `include` only includes file, which is not equal to using namespace
  - namespace creates a scope where name collision inside the scope is not allowed, but outside is allowed
  - A namespace may spread multiple files, like `std::cout` in `<cstream>`, `std::string` in `<cstring>`
  - If we don't put a class to a namespace, just
  - Usually we need qualifier like `std::` to qualify an object if we use it outside of the namespace
  - For objects not in any namespace, we don't need qualifier
  - We can omit the qualifier by `using std`: use all objects inside std (not very good)
  - Or we can only `using std::string`: better
- Reference: creating alias: `int& y = x`, so y and x refer to the same thing.
Useful when passing reference to a function. (Reference is a better pointer: we
don't need to dereference it.)
  - `swap(a, b);`
  - `int swap(int& x, int& y) {...}`
  - change x and y is equivalent to change a and b
  - Use reference for input parameter, const pointer for output parameter
  - Unlike pointer, when we create a reference, we must initialize it. And this reference cannot change to refer
    another thing after it's created
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
- `this`: a constant pointer to itself

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
      assigning an object to itself`
      - `x_ = src.x_;`
      - `y_ = src.y+;`
    - `}`
    - `return *this;  // return a reference of the object {this} points to`
    - If you don't define your own, C++ can make a synthesized one with simplest behavior
- Destructor: `Point::~Point() {}`
  - No need to call destructor. When a stack object is out of scope, C++ will automatically
  call its destructor. For heap object, we use `delete` keyword
  - Destructor destruct things in reverse order they are constructed
- Destructor, Copy constructor, Assignment constructor usually come all together or not
at all.
- When you don't want to define your own constructor:
  - `Point() = default;`, `Point(const Point& src) = default;`
- When you want to disable user to call some copy constructor or assignment constructor:
  - `Point& operator=(const Point& src) = delete;`

- Nonmember function:
  - Declared outside of the class, though still in the header file.
  - When writing definition in .cc file, do not need to attach the class's namespace before
    it like `double Point::Distance(const Point& p1, const Point& p2);`. Just write `double 
    Distance(const Point& p1, const Point& p2);`.
  - Don't have access to the class's non-public members (cannot directly read or write, but
    can do that by getter() and setter()).
    - but we can use `friend` to give non-member function access to non-public fields.
  - Don't attached to an object (`object.function()`) when it is called.

- use `nullptr` instead of `NULL`
- `new`/`delete` is just like `malloc()`/`free()`:
  - `Point* p1 = new Point(1, 2, 3);`, `int* arr = new int[size];`
  - `delete p1;`, `delete[] arr;`
    - When *object* falls out of scope, destructor will be automatically,
    called, so we don't need to manually use `delete`.
    - which means if a *pointer* falls out of scope, compiler will just
    clean the pointer, so the data pointed by the pointer will cause leak.
  - We can safely ignore the exceptions thrown by new or delete.
  
### Polymorphism
- Template: type parameter
  - `template <typename T>`
  - `int compare(const T &value1, const T &value2);`
  - for main:
  - `compare<Thing>(t1, t1);  // or we can let compiler to infer type`
  - In compile time, functions or classes declared by `template` will be ignored.
  - This creates a problem: the object.o file will be empty.
  - Solution: don't write object.c; just put all implementation into object.h, and include
  the object.h in main to compile them together.
    
### C++ STL
- Containers: store collection of objects.
- Examples:
- Vector: dynamically resizable array. `vector<Tracer> vec;`
  - When insert, resize, sort, this container will make copies...
  - iterator: `vector<Tracer>::iterator it;`
    - iterator overrides lots of operators....
    - `*it` to get element
    - `it++` to move forward by one element
    - `it = vec.begin()`: `vec.begin()` return the first element to the iterator.
    - `it = element`: move our iterator to this element.
    - `for (auto it = vec.begin(); it < vec.end(); it++) { ... }`
    - `vec.end()` returns one element past the last element.
    - `auto` is for type inference
    - for each loop: `for (auto element : container) { cout << element << endl; }`
- `for_each(vec.begin(), vec.end(), &Print);`: a syntax sugar of for loop  
- list: actually a doubly-linked list.
  - so it doesn't support array-like access `lst[2]`
- map: associative collection with an underlying structure `Pair<>`
  - `map<K, V> table;`
  - map also overrides lots of operators....
  - `V result = table[a];`: access a
  - `table[a] = b;`: insert pair (a,b)
  - `table[a];`: will just insert a pair (a, ?), where ? is the default
    declaration of type V.
  - `table.find(a);`: find a, return one pass the end of map, aka
  `table.end()` if not found.
  - map will be sorted automatically.
  
### Smart Pointer
- store smart pointers in a data structure instead. 
  `vector<shared_ptr<int>> vec;`
- `shared_ptr<int> sp(new int(3));` multiple smart pointers share one data. 
  Use reference count to record how many pointers now pointing to this data.
  If count = 0, free the data.
  - `share_ptr<int> copy(sp);` copy constructor
  - `sp.use_count()` return `count reference
- `unique_ptr<int> sp(new int(5));` only one unique pointer is allowed per data.
Copy constructor and assignment operator overload are both disabled.
  - How to transfer the unique ownership?
  - `x.release();` return the pointer that x contains. Cancel x's ownership to it
    so now x holds `nullptr`
  - `unique_ptr<int> y(x.release());` transfer x's ownership to y so now y holds
    `nullptr`
  - `z.reset(y.release())` z free its old value to reset to y's value; at the
  same time y transfer its ownership to z so now y holds `nullptr`
  - Move semantics: `unique_ptr<int> b = move(a);` so now a holds `nullptr`
- `weak_ptr<int> wp;` we cannot dereference a weak pointer, and weak pointer
doesn't count for reference.
  - `w.lock()` return data w points to, usually jointly used with
  `shared_ptr<int> x = w.lock();` to derive a shared pointer from a weak pointer.
  - `w.expired()` return whether w is already a dangling pointer or not.
- Drawbacks: 
  - Smart pointers cannot tell whether data is in heap or stack.
  - Probably reuse a raw pointer.
  
### Inheritance
- `class Child : public Mother, Father { ... };`
  - Can have multiple parents. Almost always we want public inheritance:
  parents' public members will still be public, private will still private...
  For private inheritance, things are weird.
- Dynamic dispatch: always choose the most derived (bottom of the inheritance
  tree) method to invoke.
  - use `virtual` to indicate this function (and its child functions) will be
    added to the virtual table, which means they will be dynamically dispatched.
  - `virtual string function() = 0;` a "pure" virtual function. Doesn't have any
    implementation. Make the class an abstract class (an interface).
  - use `override` to indicate this function override parents'
  - Stylistically, just use `override` on all child functions whose base function
  is `virtual`
- Static dispatch: always look for functions in the promised type.
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
  so actual type (child) 's additional members may not be cleaned.
  - Good practice to declare dtor as virtual.
- Assignment
  - Usually, we cannot assign parent to child
  - But if we assign child to parent, some members of child will be lost.
  - `list<Parent> li; li.push_back(child); // some child's members will be lost`
  
### Casting
- `static_cast<parent>(child);` checked only for compile time
  - work for pointers only
  - error if classes are not related.
  - can cast child to parent (related types)
  - can cast parent to child, but dangerous.
  - can cast void*/T* to T*/void*
  - can cast between float int long ...
  - can cast between any well-defined conversion
- `dynamic_cast<parent>(child);` checked for both compile and runtime
  - work for both pointers and references
  - because it will check dynamically, runtime error will occur if we cast
    a *real* parent object to child, but if the parent is just a pointer (its actual type
    if child), then it's okay and obligated to use dynamic casting, since static casting 
    won't work.
- `reintedyrpret_cast<void*>(num)` cast unrelated types with same size
  - void* to long
  
## Computer Network
- Layout
  - Physical layer: cable
  - Data link layer: computers communicate via ethernet. Use media access control (MAC)
  to specify how those computers cooperate.
  - Network layer: the network that span numerous individual unit. Each unit has a router. 
  Each computer has an internet protocol (IP) for receiving packages.
  - Transport layer: an abstract interface to treat network as data stream
    - TCP: stable transportation
    - UDP: unstable transportation
    - Each IP can have multiple ports to receive data
  - Session
  - Presentation
  - Application
- Client-side programming
  - Figure out IP addresses and port
    - addresses in IPv4 (4-byte) or IPv6 (16-byte)
    - addresses are big endian
    - IPv4:
      - `struct sockaddr_in` includes address family, port number,
        `struct in_addr` (host address), and padding.        
      - Address family: `AF_INET`
    - IPv6:
      - `struct sockaddr_in6` includes includes address family, port number,
        `struct in6_addr` (host address), and padding.
      - Address family: `AF_INET6`
    - port number and address numbers are in network order
    - We want a generic structure:
      - `struct sockaddr_storage` includes `struct sockaddr`
      - usually create a sockaddr_storage, then cast it to sockaddr
    - `htonl()` and `ntohl()`: convert between host and network
      byte order
    - `inet_pton()`; `inet_ntop()`; convert between human readable number string to
    internet addresses. p: presentation (human-readable), n: internet address
    - Domain Name System (DNS)
      - use `getaddrinfo()` to get internet address from DNS name: take in domain name,
        service (port number), and a hint to get `struct addrinfo`.
      - set service to `nullptr` if not sure about the service.
  - Create a socket
    - use function `int socket(int domain, int type, int protocol)`
    - e.g. `int fd = socket(AF_INET, SOCK_STREAM, 0);`
  - Connect to server
    - use function `int connect(int sockfd, const struct sockaddr* addr,
      socklen_t addrlen);` return 0 on success, -1 on failure.
    - input our socket fd, `sockaddr` found by `getaddrinfo()`, and
    `sockaddr`'s length.
  - Read
    - -1 for both recoverable and fatal errors
    - 0 for connection closed
    - if there's any amount of data in server, `read()` will read and return
    immediately, possibly with fewer bytes than we asked.
    - if there's no any data, `read()` will block and wait.
  - Write
    - 0 for connection closed.
    - -1 for both recoverable and fatal errors
    - if in our buffer there's no data to write, `write()` will block and wait.
- Server-side Programming
  - Figure out MY OWN server's address
    - `getaddrinfo()` may return a list of address. Need to loop through them until
    finding a suitable one.
  - Create a socket of SERVER: same
  - Bind (similar to connect):
    - use function `int bind(int sockfd, const struct sockaddr* addr,
      socklen_t addrlen);` return 0 on success, -1 on failure.
    - input our socket fd, `sockaddr` found by `getaddrinfo()`, and
      `sockaddr`'s length.
  - Listen: `int listen(int sockfd, int backlog);`
    - tell OS to keep this socket listening for clients' connections
    - backlog: maximum length of connection queue (the queue of clients waiting for
      connection)
    - return 0 on success, -1 on error
  - Accept: `int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);`
    - input a listening sockfd, return parameters are address and addrlen of clients'
      address. Return a file descriptor.
- Miscellenious
  - Network is big endian; while most of local hosts are little endian
  
### Concurrency
- Main sources of tasks: CPU, disk I/O, Network
- Process
  - completely independent, don't share any resources, produced by `fork()` (clone parent
    to child).
- Thread
  - independent stack, but have shared heap and other resources
- Event Driven Programming
  - when one event is happening/finished, what to do next

### Common mistakes
- sizeof: return the size of data
  - sizeof(long_int_t)
  - sizeof(array): return the size of whole array. But IF array is
  received as a pointer to array (e.g., passed as parameter),
  then it will only return the size of
  the pointer.
- String always ends in '\0'
- 
