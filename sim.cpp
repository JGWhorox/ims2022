#include <vector>
#include <random>
#include <simlib.h>

#include "sim.h"
#include "mapgenerator.h"

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
            //red army calculation
            if (b->armyID == redArmy.armyID){
                b->attack_power *= redArmy.technology_level*redArmy.professionalism;
            }
            //blue army calculation
            else{ 
                b->attack_power *= blueArmy.technology_level*blueArmy.professionalism;
            }
            
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
                    double blue_DMGmodifier  = b->enemy_Battalion->attack_power/(double)b->attack_power;
                    double red_DMGmodifier = (double)b->attack_power/b->enemy_Battalion->attack_power;
                    
                    //##### config section #####
                    double crit_f = 0.005;
                    double miss = 0.03;
                    double nothing_happens = 0.985;
                    //##### config section #####
                    
                    int blue_munitions_lost = 0;
                    int blue_supplies_lost = 0;
                    int blue_true_shots_fired = 0;
                    
                    int red_munitions_lost = 0;
                    int red_supplies_lost = 0;                   
                    int red_true_shots_fired = 0;

                    for (int i = 0; i < b->enemy_Battalion->get_number_of_healthy_units(); i++){                   
                        auto x = Random()/**b->enemy_Battalion->Professionalism*/;
                        
                        if (x < crit_f){ //critical failure - failed to hit, lost 1 munition and 1 supply to repair equipment
                            blue_munitions_lost += 1;
                            blue_supplies_lost += 1;
                        }
                        else if (x < miss){ // big failure - failed to hit, and lost munition
                            blue_munitions_lost += 1;
                        }
                        else if (x < nothing_happens){ 
                            // did not encounter enemy - didn't fire
                        }
                        else{ // hit target
                            blue_munitions_lost += 1;
                            blue_true_shots_fired += 1;
                        }
                    }
                    for (int i = 0; i < b->get_number_of_healthy_units(); i++){                   
                        auto x = Random()/**b->enemy_Battalion->Professionalism*/;
                        if (x < 0.02){ //critical failure - failed to hit, lost 1 munition and 1 supply to repair equipment
                            red_munitions_lost += 1;
                            red_supplies_lost += 1;
                        }
                        else if (x < 0.18){ // big failure - failed to hit, and lost munition
                            red_munitions_lost += 1;
                        }
                        else if (x < 0.985){ // did not encounter enemy
                            
                        }
                        else{ // hit target
                            red_munitions_lost += 1;
                            red_true_shots_fired += 1;
                        }
                    }
                    
                    int blue_casualties = 0;
                    int red_casualties = 0;

                    blue_casualties = red_true_shots_fired*red_DMGmodifier/**(1,5-enemycover)*/;
                    red_casualties = blue_true_shots_fired*blue_DMGmodifier;

                    //treba dorobiť random zapisovanie dmg do battalionu po engagemente, dostať sem enemy/friendly cover




                }
            }
            else{
                if (b->armyID = blueArmy.armyID){
                    //blue army will try to reinforce position, looks out for the enemy
                }
            }

            //logika pohybu 
            int posx = b->position.first;
            int posy = b->position.second;
            double lowest_cover = 1;
            double highest_cover = -1;
            std::pair<int, int> lowest_cover_pos;
            std::pair<int, int> highest_cover_pos;
            for (size_t i = -1; i <= 1; i++) {
                if (posy+i < 0 || posy+i > 25) continue; //don't run out of bounds
                Cell current_cell = scenario.get_cell(std::make_pair(posx-1, posy+i));

                if (current_cell.occupation == Cell::red) continue;
                if (current_cell.occupation == Cell::blue) continue; //TODO attack enemy

                if (current_cell.cover < lowest_cover) {
                    lowest_cover = current_cell.cover;
                    lowest_cover_pos = std::make_pair(posx-1, posy+i);
                }

                if (current_cell.cover > highest_cover) {
                    highest_cover = current_cell.cover;
                    highest_cover_pos = std::make_pair(posx-1, posy+i);
                }
            }

            if (highest_cover == -1) continue; //all adjecent cells occupied by red

            bool saw_blue = false;
            for (size_t i = -1; i <=1; i++) {
                if (posy+i < 0 || posy+i > 25) continue; //don't run out of bounds
                Cell c = scenario.get_cell(std::make_pair(posx-2, posy+i));
                if (c.occupation == Cell::blue) {
                    saw_blue = true;
                    break;
                }
            }

            if (saw_blue) {
                scenario.set_occupation(std::make_pair(posx, posy), Cell::neutral);
                scenario.set_occupation(highest_cover_pos, Cell::red);
                b->position = highest_cover_pos;
            } else {
                scenario.set_occupation(std::make_pair(posx, posy), Cell::neutral);
                scenario.set_occupation(lowest_cover_pos, Cell::red);
                b->position = lowest_cover_pos;
            }
        }   
    }
    return 0;
}