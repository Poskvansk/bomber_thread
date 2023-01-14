#include <iostream>
#include <thread>
#include <mutex>

void print_thread_id(int id)
{
    std::cout << "thread #" << id << " is running" << std::endl;
}

void func_1()
{
    for (int i = 0; i > -100; i--)
        std::cout << i << std::endl;
}

void func_2()
{
    for (int i = 0; i < 100; i++)
        std::cout << i << std::endl;
}

int main(int argc, char const *argv[])
{

    std::thread t1(func_1);
    std::thread t2(func_2);

    t1.join();
    t2.join();
    
    return 0;
}
