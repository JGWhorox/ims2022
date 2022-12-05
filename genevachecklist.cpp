/**
 * authors Johann A. Gawron - xgawro00, Patrik Slovák - xslova21
 * project Military Simulator
 * file genevachecklist.cpp
 * brief implementation of Military simulator main file for the subject Modelling and simulations
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

#include <vector>

//custom includes
#include "genevachecklist.h"
#include "mapgenerator.h"
#include "classes.h"
#include "scenario_config.h"
#include "sim.h"

int main(int argc, char** argv){
    //std::cout << "Welcome to your week's purgatory" << std::endl;
    Army blueArmy;
    Army redArmy;
    MyMap map;

    configureScenario(blueArmy,redArmy,map);

    int retval = executeSim(blueArmy, redArmy, map, 100/*720 is 1 month in hours*/);
    
    return 0;
}