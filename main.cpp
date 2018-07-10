#include "visual.h"
using namespace std;
static const int plantsNumber = 10;
static const int animalsNumber = 5;
static const int fieldsNumber = 3;

Plant ** createPlants(double sun){
    Plant ** plants = new Plant*[plantsNumber];
    for (int i = 0; i<plantsNumber; i++){
        plants[i] = new Plant(i, sun);
    }
    return plants;
}

Animal ** createAnimls(Food * food){
    Animal ** animals = new Animal*[animalsNumber];
    for (int i = 0; i<animalsNumber; i++){
        animals[i] = new Animal(food);
    }
    return animals;
}

int main(){
    srand(time(NULL));

    Weather weather = Weather(plantsNumber);
    Plant ** field1 = createPlants(weather.getSun());
    Plant ** field2 = createPlants(weather.getSun());
    Plant ** field3 = createPlants(weather.getSun());
    weather.setFields(field1, field2, field3);
    Farmer farmer = Farmer(field1, field2, field3, plantsNumber);
    Food food = Food();
    Animal ** animals = createAnimls(&food);

    thread* animalsThreads = new thread[animalsNumber];
    for(int i = 0; i < animalsNumber; ++i){
        animalsThreads[i] = thread(&Animal::live, animals[i]);
    }
    thread* field1Threads = new thread[plantsNumber];
    for(int i = 0; i < plantsNumber; ++i){
        field1Threads[i] = thread(&Plant::live, field1[i]);
    }
    thread* field2Threads = new thread[plantsNumber];
    for(int i = 0; i < plantsNumber; ++i){
        field2Threads[i] = thread(&Plant::live, field2[i]);
    }
    thread* field3Threads = new thread[plantsNumber];
    for(int i = 0; i < plantsNumber; ++i){
        field3Threads[i] = thread(&Plant::live, field3[i]);
    }
    thread farmerThread = thread(&Farmer::manage, &farmer);
    thread weatherThread = thread(&Weather::exist, &weather);

    Visual visual = Visual();
    visual.start(field1, field2, field3, animals, &farmer, &weather, plantsNumber, animalsNumber);

    for(int i = 0 ; i < plantsNumber; i++) {
        field1Threads[i].join();
        field2Threads[i].join();
        field3Threads[i].join();
    }
    for(int i = 0 ; i < animalsNumber; i++) {
        animalsThreads[i].join();
    }
    farmerThread.join();
    weatherThread.join();

    for(int i = 0 ; i < plantsNumber ; i++) {
        delete field1[i];
        delete field2[i];
        delete field3[i];
    }
    for(int i = 0 ; i < animalsNumber ; i++) {
        delete animals[i];
    }
    
    return 0;
}