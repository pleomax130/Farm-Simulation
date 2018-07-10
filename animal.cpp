#include "animal.h"

using namespace std;
mutex Animal::mtx;
bool Animal::used = false;
int Animal::food = 0;
Animal::Animal(Food * food){
    Animal::foods = food;
    Animal::isRunning = true;
}

void Animal::wait(int counter){
    for(int i = 0; i<counter; i++){
            this_thread::sleep_for(chrono::milliseconds(100));
        }
}

void Animal::eat(){
    mtx.lock();
    this->state = "eating";
    for(int i=0; i<3; i++){
        if(Animal::food >= 4){
            Animal::food -= 4;
            this->wait(1);
        }

    }
    mtx.unlock();
}

void Animal::move(){
    this->state = "moving";
    this->wait(500);
}

void Animal::live(){
    while(this->isRunning){
        this->move();
        while(!Animal::used){
            Animal::used = true;
            this->eat();
        }
        Animal::used = false;
    }
}

int Animal::getFood(){
    return this->food;
}