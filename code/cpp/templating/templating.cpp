// This module compares the speed difference between dynamically calling a
// method from related classes via templating, against calling a method through
// polymorphism. The templated call should be much faster.
#include <random>
class A
{
    public:
        void run()
        {
        }
};
class B
{
    public:
        void run()
        {
        }
};

// Globals
A a;
B b;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
unsigned mod = 2;

template<typename T>
void function(T t)
{
    t.run();
}

void execute()
{
    for (int i = 0; i < 1'000'000; i++)
    {
        if ((seed % mod++) % 2)
            function(a);
        else
            function(b);
    }
}
