/**
 * authors Johann A. Gawron - xgawro00, Patrik Slovák - xslova21
 * project Military Simulator
 * file main.cpp
 * brief implementation of Military simulator main file for the subject Modelling and simulations
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

#include <vector>

//custom includes
#include "main.h"
#include "mapgenerator.h"
#include "classes.h"
#include "scenario_config.h"
#include "sim.h"

int main(int argc, char** argv){
    Army blueArmy;
    Army redArmy;
    MyMap map;

    configureScenario(blueArmy,redArmy,map);

    int retval = executeSim(blueArmy, redArmy, map, 300/*720 is 1 month in hours*/);
    
    return 0;
}