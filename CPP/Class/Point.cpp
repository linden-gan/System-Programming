#include <iostream>
#include <memory>
#include <string>
#include <sstream>

using std::string;
using std::ostringstream;
using std::shared_ptr;
using std::unique_ptr;
using std::cout;
using std::endl;
using std::move;

class Point {
    private:
        double x;
        double y;
    public:
        Point(double x, double y) : x(x), y(y) {}

        string toString() {
            ostringstream oss;
            oss << "(" << x << ", " << y << ")" << std::endl;
            return oss.str();
        }
};

void func1() {
    shared_ptr<Point> sp(new Point(3, 4));
    shared_ptr<Point> sp2(sp);
}

void func2(unique_ptr<Point> up) {
    std::cout << up->toString();
}

void func3() {

}

int main() {
    unique_ptr<Point> up(new Point(2, 1));
    func2(up.release());
}
