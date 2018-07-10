#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include "food.h"
class Animal{
    private:
        static std::mutex mtx;
        Food *foods;
        bool isRunning;
        void eat();
        void move();
        void wait(int counter);
    public:
        std::string state;
        void live();
        Animal(Food * food);
        int getFood();
        static int food;
        static bool used;
};