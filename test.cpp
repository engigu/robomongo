class A { public: void foo(); };
class B : private A { public: void bar() { foo(); } };
int main() { B b; b.foo(); }
