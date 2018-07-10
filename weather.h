#include "farmer.h"
class Weather{
    private:
        bool isRunning;
        void changeWeather();
        void adjustSun();
        void wait(int counter);
        double sun;
        int fieldSize;
        Plant ** field1, ** field2, ** field3;
    public:
        Weather(int size);
        void setFields(Plant ** field1, Plant ** field2, Plant ** field3);
        void exist();
        double getSun();
};