#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>

class Plant{
    private:
        bool isRunning;
        double sun;
        int id, dry;
        double growLevel;
        bool grown, dead;
        static std::mutex mtx;
        void grow(double sun);
        void wait(int counter);
        bool checkIfDry();
        bool checkIfGrown();
    public:
        int irrigation;
        Plant();
        Plant(int id, double sun);
        void water();
        void live();
        int getIrrigation();
        double getGrowLevel();
        bool isGrown();
        bool isDead();
        bool used;
        void restart();
        void setSun(double sun);
        double getSun();
        static int growLimit;
};