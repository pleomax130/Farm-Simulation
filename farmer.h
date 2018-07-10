#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <cstdlib>
#include <ctime>
#include "plant.h"
#include "animal.h"
class Farmer{
    private:
        bool isRunning;
        Plant ** field1, **field2, ** field3;
        int size;
        int crops;
        int warehouse;
        void collect(int number);
        void takeToWarehouse();
        void water(int number);
        void wait(int counter);
    public:
        std::string state;
        int progress, fieldNumber;
        Farmer(Plant ** field1, Plant ** field2, Plant ** field3, int size);
        void manage();
        int getWarehouse();
};