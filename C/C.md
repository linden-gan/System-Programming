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
String as output parameter:
```
    generate_string(char** s) {  // char** for string output parameter
        // *s = "hello";  ->  not recommended because "hello" is in static memory
        strcpy(*s, "hello");  // strcpy can make *s modifiable
    }
    char* res;
    // We will change the pointer *res to point to other string,
    // so we have to pass in the pointer's pointer.
    generate_string(&res);
    printf("%s\n", res);
```
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

### Common mistakes
- sizeof: return the size of data
  - sizeof(long_int_t)
  - sizeof(array): return the size of whole array. But IF array is
  received as a pointer to array (e.g., passed as parameter),
  then it will only return the size of
  the pointer.
- String always ends in '\0'
