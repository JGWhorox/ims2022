#include <vector>
#include <random>

#include "sim.h"

int executeSim(Army &blueArmy, Army &redArmy, MyMap scenario, int timeframe){
    
    //vkladanie na mapu
    for(auto battalion : blueArmy.battalions){
        scenario.set_occupation(battalion.position, Cell::blue);
    }
    for(auto battalion : redArmy.battalions){
        scenario.set_occupation(battalion.position, Cell::red);
    }


    for (int hour=0; hour <= timeframe; hour++){
        
        //get all battalions into 1 poitner list so I can randomize their engagements
        std::vector<Battalion*> battalions; 
        for ( auto b : blueArmy.battalions ){
            battalions.push_back(&b);
        }
        for ( auto b : redArmy.battalions ){
            battalions.push_back(&b);
        }
        //calculate attack power in the beginning of the turn
        for(auto b : battalions){
            b->attack_power = b->get_base_attack_power();
        }
        
        //eating
        if(hour % 8 == 0){
            for ( auto b : blueArmy.battalions ){
                //TANK MUSI ZRAT VIAC
                for ( auto c : b.companies ){
                    int number_of_units = c->units.size();
                    int number_of_wounded = c->ret_current_wounded_size();

                    c->food = c->food - ((number_of_units - number_of_wounded)+number_of_wounded*2);
                }
            }
        }

        //check okolia
        
        while(!battalions.empty()){
            
            //choses one battalion at random
            int idx = std::rand()% battalions.size();
            Battalion* b = battalions.at(idx);
            
            //removes the battalion from iterable list
            battalions.erase(battalions.begin()+idx);

            
            if(b->in_fight){
                //engagement logic
                if (b->armyID = redArmy.armyID){
                    int enemyAP = b->enemy_Battalion->attack_power;
                }
            }
            else{
                if (b->armyID = blueArmy.armyID){
                    //blue army will try to reinforce position, looks out for the enemy
                }
            }
            
        }

        //logika pohybu    
        
    }
    return 0;
}