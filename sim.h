#include <list>

#include "classes.h"
#include "mapgenerator.h"

/*blueArmy,redArmy,map,timeframe*/
void print_units(Army &blueArmy, Army &redArmy, int hour);
int executeSim(Army &blueArmy, Army &redArmy, MyMap scenario, int timeframe);