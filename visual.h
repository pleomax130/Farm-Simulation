#include "weather.h"
class Visual{
    private:
        void initColors();
        void drawLegend();
        void drawFields(int id, Plant * plant, const int *fieldY, const int * fieldX);
        void drawBarrier();
        void drawFood(int food);
        void drawAnimals(Animal * animal);
        void drawFarmer(Farmer * farmer);
        void drawSun(int color1, int color2);
        void drawWeather(Weather * weather);
        void drawWarehouse(Farmer * farmer);
        void drawPlantDetails(Plant * plant);
    public:
        void start(Plant ** field1, Plant ** field2, Plant ** field3, Animal ** animals, Farmer * farmer, Weather * weather, int numPlants, int numAnimals);
        Visual();
        ~Visual();
};