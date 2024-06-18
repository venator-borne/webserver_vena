#include <iostream>
#include <vector>
#include <memory>
using namespace std;

int main(int argc, char const *argv[])
{
    shared_ptr<int> p = make_shared<int>(10);
    cout << *p << endl;
    return 0;
}
