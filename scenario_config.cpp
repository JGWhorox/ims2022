#include "scenario_config.h"

void configureScenario(Army &blueArmy,Army &redArmy, MyMap &map){
    //setupScenario
    /*
    ############## MAP ##############
    ############ EXAMPLE ############
                    X
            1   2   3   4   5
           ___ ___ ___ ___ ___
        1 | B |   |   |   | R |     
           --- --- --- --- ---
        2 | B |   |   |   | R |     
           --- --- --- --- ---
    Y   3 |   | B |   |   | R |     
           --- --- --- --- ---
        4 |   | B |   |   | R |     
           --- --- --- --- ---
        5 |   | B |   |   | R |     
           --- --- --- --- ---
                      
    ############## MAP ##############
    ############ EXAMPLE ############
    */
    int map_size_x = 10;
    int map_size_y = 10;
    map = MyMap(map_size_x,map_size_y);
    std::list<std::pair<int, int>> blue_line;
    for (size_t y = 0; y < map_size_y; y++)
    {
        //change for different generation 
        //default moves line one cell to the right after middle point
        if (y < map_size_y/2){
            blue_line.push_back(std::make_pair(map_size_x/3,y));
        } else {
            blue_line.push_back(std::make_pair(map_size_x/3+1,y));
        }
    }
    map.set_blue_line(blue_line);

    //configure armies 
    //scuffed way of identifying armies in simulation algorithm #temporary #make your life easier, not harder
    blueArmy.armyID = 1;
    redArmy.armyID = 2;

    //config of national resources
    blueArmy.ammo_supplies = 5000.0;
    blueArmy.combat_supplies = 5000.0;
    blueArmy.food_supplies = 10000.0;

    redArmy.ammo_supplies = 5000.0;
    redArmy.combat_supplies = 5000.0;
    redArmy.food_supplies = 10000.0;

    blueArmy.logistics_effectivity = 0.95;
    blueArmy.technology_level = 4.2;
    blueArmy.professionalism = 0.95;

    redArmy.logistics_effectivity = 0.80;
    redArmy.technology_level = 4.2;
    redArmy.professionalism = 0.95;

    //config of army sizes and
    //config initial position armies on the mapmake_pair(1,1)
    blueArmy.battalions.push_back(generate_battalion(4,150,1,50,1,10,blueArmy.armyID,map_size_x/3,2)); //600 Infantry + 50 Combat Support units + 10 Tanks with crew
    blueArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,blueArmy.armyID,map_size_x/3,4));
    blueArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,blueArmy.armyID,map_size_x/3+1,6));
    blueArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,blueArmy.armyID,map_size_x/3+1,8));
    
    redArmy.battalions.push_back(generate_battalion(4,150,1,50,1,10,redArmy.armyID,map_size_x,2));
    redArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,redArmy.armyID,map_size_x,4));
    redArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,redArmy.armyID,map_size_x,6));
    redArmy.battalions.push_back(generate_battalion(5,130,1,50,0,0,redArmy.armyID,map_size_x,8));
}