#include <cstdlib>
#include <iostream>  // contains cout, cin, endl, string, ...
#include <sstream>  // StringStream lib contains ostringstream, istringstream and stringstream
#include <vector>

// using namespace std;  bad practice because std is a large namespace thus possible to have name collision
using std::vector;
using std::string;

void func1() {
    using namespace std;  // but using this in a small scope is ok
    cout << "Hello" << 2024 << endl;
    cout << "Enter a string:" << endl;
    string echo;
    cin >> echo;
    cout << "Enter an int:" << endl;
    int echo_int;
    cin >> echo_int;
    cout << "Enter a double:" << endl;
    int echo_double;
    cin >> echo_double;
    cout << "You entered " << echo << " and " << echo_int << " and " << echo_double;
}

string func2(const vector<string>& input) {
    std::ostringstream oss;  // using stringstream is much faster than string concat
    for (const auto& element : input) {
        oss << element << ",";
    }
    return oss.str();  // convert everything in oss buffer to a string
}

int main() {
    vector<string> vec{ "A", "B", "C", "D", "E", "F", "G" };
    std::cout << func2(vec) << std::endl;
}