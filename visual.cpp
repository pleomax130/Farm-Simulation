#include "ncurses.h"
#include "visual.h"
#include <iostream>
#include <string>

static const int field1Y[] = {22, 22, 20, 20, 18, 18, 16, 16, 14, 14};
static const int field1X[] = {77, 75, 77, 75, 77, 75, 77, 75, 77, 75};
static const int field2Y[] = {22, 22, 20, 20, 18, 18, 16, 16, 14, 14};
static const int field2X[] = {71, 69, 71, 69, 71, 69, 71, 69, 71, 69};
static const int field3Y[] = {22, 22, 20, 20, 18, 18, 16, 16, 14, 14};
static const int field3X[] = {65, 63, 65, 63, 65, 63, 65, 63, 65, 63};

const std::string Standing = "standing";
const std::string Moving = "moving";
const std::string MovingBack = "movingBack";
const std::string Watering = "watering";
const std::string Collecting = "collecting";

Visual::Visual(){
    initscr();
    noecho();
    curs_set(0);
    initColors();
}

void Visual::initColors() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(2, COLOR_GREEN, COLOR_GREEN); // zielony
    init_pair(3, COLOR_YELLOW, COLOR_YELLOW); // zolty
    init_pair(4, COLOR_RED, COLOR_RED); // czerwony
    init_pair(5, COLOR_YELLOW, COLOR_BLACK); // zolte kreski
    init_pair(6, COLOR_RED, COLOR_BLACK); // czerwone kreski
    init_pair(7, COLOR_WHITE, COLOR_WHITE); // bialy
    init_pair(8, COLOR_CYAN, COLOR_CYAN); // cyan farmer
    init_pair(9, COLOR_BLACK, COLOR_BLACK); //czarny
    init_pair(10, COLOR_MAGENTA, COLOR_MAGENTA);
    bkgd(COLOR_PAIR(1));
}

Visual::~Visual(){
    endwin();
}


void Visual::drawLegend(){
    attron(COLOR_PAIR(1));
    move(7,16);
    printw("Jedzenie:");
    move(9,1);
    printw("Magazyn");
    move(15,1);
    printw("Farmer:");
    attron(COLOR_PAIR(8));
    move(16,1);
    addch('h');
    move(16,2);
    attron(COLOR_PAIR(1));
    printw("-poruszanie sie");
    attron(COLOR_PAIR(7));
    move(17,1);
    addch('h');
    move(17,2);
    attron(COLOR_PAIR(1));
    printw("-podlewanie");
    attron(COLOR_PAIR(10));
    move(18,1);
    addch('h');
    move(18,2);
    attron(COLOR_PAIR(1));
    printw("-zbieranie");
    move(19,1);
    printw("Slonce:");
    attron(COLOR_PAIR(7));
    move(20,1);
    addch('h');
    move(20,2);
    attron(COLOR_PAIR(1));
    printw("-slabe");
    attron(COLOR_PAIR(4));
    move(21,1);
    addch('h');
    move(21,2);
    attron(COLOR_PAIR(1));
    printw("-srednie");
    attron(COLOR_PAIR(3));
    move(22,1);
    addch('h');
    move(22,2);
    attron(COLOR_PAIR(1));
    printw("-mocne");
    move(15,23);
    printw("Roslina:");
    attron(COLOR_PAIR(2));
    move(16,23);
    addch('h');
    move(16,24);
    attron(COLOR_PAIR(1));
    printw("-slabo rozwinieta");
    attron(COLOR_PAIR(3));
    move(17,23);
    addch('h');
    move(17,24);
    attron(COLOR_PAIR(1));
    printw("-srednio rozwinieta");
    attron(COLOR_PAIR(4));
    move(18,23);
    addch('h');
    move(18,24);
    attron(COLOR_PAIR(1));
    printw("-dojrzala");
}

void Visual::drawBarrier(){
    const int barrierY[] = {0,1,2,3,4,5};
    const int barrierX[] = {20,21,22,23,24,25,26,27};
    attron(COLOR_PAIR(1));
    for(int i = 0; i<6; i++){
        move(barrierY[i], barrierX[0]);
        addch('|');
        move(barrierY[i], 44);
        addch('|');
    }
    for(int i = 20; i<45; i++){
        move(barrierY[5], i);
        addch('-');
    }
}

void Visual::drawSun(int color1, int color2){
    attron(COLOR_PAIR(color1));
    move(1,73);
    addch('\\');
    move(4,77);
    addch('\\');
    move(1,77);
    addch('/');
    move(4,73);
    addch('/');
    attron(COLOR_PAIR(color2));
    move(2,74);
    addch('h');
    move(2,75);
    addch('h');
    move(2,76);
    addch('h');
    move(3,74);
    addch('h');
    move(3,75);
    addch('h');
    move(3,76);
    addch('h');
}

void Visual::drawFields(int id, Plant * plant, const int * fieldY, const int * fieldX){
    move(fieldY[id], fieldX[id]);
    if(plant->isDead()){
        attron(COLOR_PAIR(1));
        addch('X');
    }
    else{
        if(plant->getGrowLevel()<=Plant::growLimit/2)
            attron(COLOR_PAIR(2));
        else if(plant->getGrowLevel()>Plant::growLimit/2 && plant->getGrowLevel()<Plant::growLimit)
            attron(COLOR_PAIR(3));
        else
            attron(COLOR_PAIR(4));
        move(fieldY[id], fieldX[id]);
        addch('h');
    }
    
}

void Visual::drawFood(int food){
    attron(COLOR_PAIR(1));
    move(7,25);
    printw("    ");
    move(7,25);
    printw("%d", food);
}

void Visual::drawAnimals(Animal * animal){
    int y = rand()%5;
    int x = (rand()%21)+23;
    attron(COLOR_PAIR(7));
    move(y,x);
    addch('h');
}

void Visual::drawFarmer(Farmer * farmer){
    if(farmer->state.compare(Watering) == 0){
        attron(COLOR_PAIR(9));
        for(int i=54; i<61; i++){
            move(14, i);
            addch('h');
        }
        attron(COLOR_PAIR(7));
        if(farmer->fieldNumber == 1){
            move(14,61);
        }
        else if(farmer->fieldNumber == 2){
            attron(COLOR_PAIR(9));
            move(14,61);
            addch('h');
            attron(COLOR_PAIR(7));
            move(14,67);
        }
        else if(farmer->fieldNumber == 3){
            attron(COLOR_PAIR(9));
            move(14,67);
            addch('h');
            attron(COLOR_PAIR(7));
            move(14,73);
        }
        addch('h');
    }
    else if(farmer->state.compare(Collecting) == 0){
        attron(COLOR_PAIR(9));
        for(int i=54; i<61; i++){
            move(14, i);
            addch('h');
        }
        attron(COLOR_PAIR(10));
        if(farmer->fieldNumber == 1)
            move(14,61);
        else if(farmer->fieldNumber == 2){
            attron(COLOR_PAIR(9));
            move(14,61);
            addch('h');
            attron(COLOR_PAIR(10));
            move(14,67);
        }
        else if(farmer->fieldNumber == 3){
            attron(COLOR_PAIR(9));
            move(14,67);
            addch('h');
            attron(COLOR_PAIR(10));
            move(14,73);
        }
        addch('h');
    }
    else if(farmer->state.compare(Moving) == 0){
        attron(COLOR_PAIR(8));
        move(14, farmer->progress * 3);
        addch('h');
        attron(COLOR_PAIR(9));
        if(farmer->progress > 0){
            move(14, (farmer->progress-1) * 3);
            addch('h');
            move(14, (farmer->progress-2) * 3);
            addch('h');
        }
    }
    else if(farmer->state.compare(MovingBack) == 0){
        attron(COLOR_PAIR(9));
        move(14,73);
        addch('h');
        move(14,61);
        addch('h');
        attron(COLOR_PAIR(8));
        move(14, 60-(farmer->progress * 3));
        addch('h');
        attron(COLOR_PAIR(9));
        if(farmer->progress < 58){
        move(14, 60-(farmer->progress-1) * 3);
        addch('h');
        move(14, 60-(farmer->progress-2) * 3);
        addch('h');
        }
    }
}

void Visual::drawWeather(Weather * weather){
    double x = weather->getSun();
    if(x<0.3)
        drawSun(1,7);
    else if (x>=0.3 && x<0.6)
        drawSun(6,4);
    else
        drawSun(5,3);
}

void Visual::drawWarehouse(Farmer * farmer){
    attron(COLOR_PAIR(1));
    move(10,1);
    printw("    ");
    move(10,1);
    printw(std::to_string(farmer->getWarehouse()).c_str());
}

void Visual::drawPlantDetails(Plant * plant){
    attron(COLOR_PAIR(1));
    move(19,45);
    printw("woda:");
    move(20,45);
    printw("slonce:");
    move(21,45);
    printw("wzrost:");
    move(22,45);
    printw("dojrzala:");
    move(19,54);
    printw("    ");
    move(19,54);
    printw("%d", plant->getIrrigation());
    move(20,54);
    printw("    ");
    move(20,54);
    printw("%.1f", plant->getSun());
    move(21,54);
    printw("    ");
    move(21,54);
    printw("%.0f", plant->getGrowLevel());
    move(22,54);
    printw("    ");
    move(22,54);
    bool grown = plant->isGrown();
    if(grown)
        printw("tak");
    else
        printw("nie");
}

void Visual::start(Plant ** field1, Plant ** field2, Plant ** field3, Animal ** animals, Farmer *farmer, Weather *weather, int numPlants, int numAnimals){
    drawLegend();
    drawBarrier();
    int ch;
    nodelay(stdscr, TRUE);
    for (;;) {
        if ((ch = getch()) != 27) {
            for(int i = 0 ; i < numPlants; i++) {
                drawFields(i, field3[i], field1Y, field1X);
                drawFields(i, field2[i], field2Y, field2X);
                drawFields(i, field1[i], field3Y, field3X);
            }
            drawPlantDetails(field1[0]);
            drawFood(Animal::food);
            attron(COLOR_PAIR(9));
            for(int i=0; i<5; i++)
                for(int j=21; j<44; j++){
                    move(i,j);
                    addch('h');
                }
            for(int i = 0 ; i < numAnimals; i++) {
                drawAnimals(animals[i]);
            }
            drawFarmer(farmer);
            drawWarehouse(farmer);
            drawWeather(weather);
            timeout(125);
        }
        else {
            return;
        }
    }
}