// This module compares the speed difference between dynamically calling a
// method from related classes via templating, against calling a method through
// polymorphism. The templated call should be much faster.
#include <random>
class ABC
{
    public:
        virtual void run() =0;
};
class A: public ABC
{
    public:
        void run() override
        {
        }
};
class B: public ABC
{
    public:
        void run() override
        {
        }
};

// Globals
A a;
B b;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
unsigned mod = 2;

void function(ABC &t)
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
