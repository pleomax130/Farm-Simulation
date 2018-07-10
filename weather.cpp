#include "weather.h"

using namespace std;

Weather::Weather(int size){
    Weather::fieldSize = size;
    Weather::isRunning = true;
    double value = (double) ((rand()%10)+0) / 10;
    this->sun = value;
}

void Weather::wait(int counter){
    for(int i = 0; i<counter; i++){
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void Weather::adjustSun(){
    for(int i = 0; i < this->fieldSize; i++){
        field1[i]->setSun(this->sun);
        field2[i]->setSun(this->sun);
        field3[i]->setSun(this->sun);
    }
}

void Weather::setFields(Plant ** field1, Plant ** field2, Plant ** field3){
    this->field1 = field1;
    this->field2 = field2;
    this->field3 = field3;
}

void Weather::changeWeather(){
    double value = (double) ((rand()%10)+0) / 10;
    //cout<<value<<endl;
    this->sun = value;
    this->adjustSun();
}

void Weather::exist(){
    while(this->isRunning){
        this->changeWeather();
        this->wait(20);
    }
}

double Weather::getSun(){
    return this->sun;
}