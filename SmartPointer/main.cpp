#include"shared_ptr.h"
#include"unique_ptr.h"

using std::cout;
using std::endl;
using std::move;

class A
{
public:
    int _a;
    char _c;

    A()
    {
        _a = 0;
        _c = 'a';
    }
    A(int a, char c):_a(a),_c(c)
    {}
    
};

void test_shared_ptr()
{
    // Shared_ptr<int> sp1(new int(10));
    // sp1.ptrint_count();

    // Shared_ptr<int> sp2(sp1);
    // sp1.ptrint_count();
    // sp2.ptrint_count();

    // Shared_ptr<int> sp3(new int(20));
    // sp2 = sp3;
    // sp1.ptrint_count();
    // sp2.ptrint_count();
    // sp3.ptrint_count();

    Shared_ptr<A> a1(new A(3, 'c'));
    std::cout << "value in a1: ";
    std::cout << (*a1)._a << a1->_c << std::endl;
    std::cout << "pointer count in a1: ";
    a1.ptrint_count();
    std::cout << std::endl;


    Shared_ptr<A> a2(a1);
    std::cout << "pointer count in a1: ";
    a1.ptrint_count();
    std::cout << "value in a2: ";
    std::cout << a2->_a << (*a2)._c << std::endl;
    std::cout << "pointer count in a2: ";
    a2.ptrint_count();
    std::cout << std::endl;


    Shared_ptr<A> a3(new A());
    a2 = a3;
    std::cout << "pointer count in a1: ";
    a1.ptrint_count();
    std::cout << "value in a2: ";
    std::cout << a2->_a << (*a2)._c << std::endl;
    std::cout << "pointer count in a2: ";
    a2.ptrint_count();
    std::cout << "pointer count in a3: ";
    a3.ptrint_count();

    
}


class TestUniPtr
{
private:
    int a;

public:
    TestUniPtr()
    {
        a = 1;
        cout << "TestUniPtr construct" << endl;
    }
    TestUniPtr(int num)
    {
        a = num;
        cout << "TestUniPtr construct" << endl;
    }
    ~TestUniPtr()
    {
        cout << "TestUniPtr destruct" << endl;
    }

    void printSomething()
    {
        cout << "TestUniPtr printSomething" << endl;
    }

    void printResource()
    {
        cout << "TestUniPtr printResource: " << a << endl;
    }

    int getResource()
    {
        return a;
    }

};


void test_unique_ptr()
{
    Unique_ptr<TestUniPtr> p1(new TestUniPtr);
    Unique_ptr<TestUniPtr> p2(move(p1));
    Unique_ptr<TestUniPtr> p3(new TestUniPtr(3));
    p3 = move(p2);

    p1->printSomething();
    // p2->printResource();
    p3->printResource();
}

int main()
{
    test_unique_ptr();
    return 0;
}