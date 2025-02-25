#include <stdlib.h>
#include <stdio.h> // printf
#include <string.h> // strcpy, strcat
#include <assert.h>

void sizeof_incorrect_demo(int arr[]) {
    // sizeof is a compile-time unary operator
    // %lu: unsigned long
    printf("%lu\n", sizeof(arr)); // output pointer's size 8 since arr is a pointer
}
void array_demo() {
    // cases with initialization list
    int arr1[] = {1, 2, 3}; // most basic one
    char arr2[2] = {'a', 'b'}; // better style to explicitly allocate length
    int arr3[3] = {}; // shortcut to create three zeros
    int arr4[4] = {0}; // also a shortcut to create four zeros
    int arr5[5] = {1, 2}; // {1, 2, 0, 0, 0}
    char* arr6[6] = {"abc", "def"}; // {"abc", "def", NULL, NULL, NULL, NULL}
    // the principle of these is using default value (0, NULL) to pad an array
    // if its size is bigger than the size of initialization list

    // cases without initialization list
    int arr7[7]; // seven garbages
    int* arr8[8]; // eight garbages
    // if we don't have initializaiton list, data of all types will be garbage, including struct's field
    // int arr9[]; // grammar error

    printf("arr1's size is %lu\n", sizeof(arr1)); // output actual size 3 * 4 
    // because compiler knows arr1 is an array since it's in this func stack
    sizeof_incorrect_demo(arr1);
}

void string_demo() {
    // initialization
    char* s1 = "aa"; // a pointer to literal in static memory, so can't be modified!
    char s2[] = "bb"; // equivalent to an array in stack, so can be modified
    char s3[] = {'c', 'c', '\0'}; // need \0 when initialize like this
    printf("s3's length is %lu\n", strlen(s3)); // output 2: strlen doesn't count \0!

    // strcpy
    char s4[strlen(s3) + 1]; // + 1 for \0
    strcpy(s4, s3); // will copy \0, if src > des then overflow
    printf("s4 is: %s\n", s4);

    // strncpy
    int n = 5;
    char s5[10];
    strncpy(s5, s3, n); // {'c', 'c', '\0', '\0', '\0', garbage, ...}
    // pad \0 till we write n elements if s3 < n
    // when n > s5, overflow
    printf("s5 is %s\n", s5);

    // strcat
    char s6[10] = "abc";
    strcat(s6, "def"); // concat def to abc, overwrite abc's \0, add \0 after def
    // overflow is also possible
    printf("s6 is %s\n", s6);

    // strncat
    char s7[10];
    strncat(s7, "abc", 2); // {'a', 'b', '\0'}
    strncat(s7, "def", 4); // {'a', 'b', 'd', 'e', 'f'}
    // if n < src, only copy n element of src, plus \0
    // if n > src, copy whole src, plus \0, NO PADDING
    // overflow is also possible when n > des
    printf("s7 is %s\n", s7);

    // memcpy
    char s8[] = "Ytterbium";
    struct {
        char name[100];
        int age;
    } p1, p2;
    memcpy(p1.name, s8, strlen(s8) + 1); // + 1 because memcpy won't add \0
    p1.age = 1;
    memcpy(&p2, &p1, sizeof(p1)); // memcpy struct
    printf("p2's name is %s; p2's age is %d", p2.name, p2.age);

    // malloc
    char s9[] = "Promethium";
    char* s10 = (char*) malloc(strlen(s9) + 1); // + 1 for \0
    strcpy(s10, s9);
    printf("s10 is %s\n", s10);
    free(s10);
}

double next_arithmetic_term(double curr, double k) {
    return curr + k;
}
double next_geometric_term(double curr, double k) {
    return curr * k;
}
void make_sequence(
    double seq[], int size, double a, double k,  // array as output parameter
    double (*get_next_term)(double curr, double k))
{
    assert(size > 0);
    seq[0] = a;
    for (int i = 1; i < size; i++) {
        seq[i] = (*get_next_term)(seq[i-1], k);
    }
}
void array_as_output_param_and_functional_pointer_demo() {
    int size = 10;
    double seq1[size];
    double seq2[size];
    // No need to pass &seq1 because we won't change the pointer seq1.
    // We will change the data seq1 points to.
    make_sequence(seq1, size, 0.1, 4, next_arithmetic_term);
    make_sequence(seq2, size, 10, -0.5, next_geometric_term);
    for (int i = 0; i < size; i++) {
        printf("%.2f, ", seq1[i]);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("%.2f, ", seq2[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    array_demo();
    string_demo();
    array_as_output_param_and_functional_pointer_demo();
}