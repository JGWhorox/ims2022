#include <iostream>
#include <vector>
#include <random>
#include <simlib.h>

#include "sim.h"
#include "classes.h"
#include "mapgenerator.h"

int executeSim(Army &blueArmy, Army &redArmy, MyMap scenario, int timeframe){
    std::cout << "hue" << std::endl;
    //vkladanie na mapu
    for(auto &battalion : blueArmy.battalions){
        scenario.set_occupation(battalion.position, Cell::blue);
    }
    for(auto &battalion : redArmy.battalions){
        scenario.set_occupation(battalion.position, Cell::red);
    }

    for (int hour=0; hour <= timeframe; hour++){
        
        blueArmy.report_stats(hour,true,false);
        redArmy.report_stats(hour,true,false);

        //get all battalions into 1 poitner list so I can randomize their engagements
        std::vector<Battalion*> battalions_vector; 
        for ( auto &b : blueArmy.battalions ){
            battalions_vector.push_back(&b);
        }
        for ( auto &b : redArmy.battalions ){
            battalions_vector.push_back(&b);
        }
        //calculate attack power in the beginning of the turn
        for(auto b : battalions_vector){
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
            for ( auto b : battalions_vector ){
                //TANK MUSI ZRAT VIAC
                for ( auto c : b->companies ){
                    int number_of_units;
                    int number_of_wounded;

                    if (c->type == Company::tank) {
                        number_of_units = c->units.size()*4;
                        number_of_wounded = c->ret_current_wounded_size()*4;
                    } else{
                        number_of_units = c->units.size();
                        number_of_wounded = c->ret_current_wounded_size();
                    }
                    c->food = c->food - ((number_of_units - number_of_wounded)+number_of_wounded*2);
                }
            }
        }

        //check okolia

        while(!battalions_vector.empty()){

            //choses one battalion at random
            int idx = std::rand()% battalions_vector.size();
            Battalion* b = battalions_vector.at(idx);

            //removes the battalion from iterable list
            battalions_vector.erase(battalions_vector.begin()+idx);

            if (b->is_backup){
                b->backup_timeout--;
                if (b->backup_timeout != 0) continue;
                for (auto bat : blueArmy.battalions) {
                    if (bat.position == b->position && !bat.is_backup) {
                        bat.assign_backup(*b);
                        //blueArmy.battalions.remove(b);
                        for (auto iter = blueArmy.battalions.begin(); iter != blueArmy.battalions.end(); iter++){
                            Battalion &b2 = *iter;
                            if (&b2 == b){
                                blueArmy.battalions.erase(iter);
                                break;
                            }
                        }
                        //if you need to move the battalion add here
                        break;
                    }
                }
                continue;
            }


            if(b->in_fight){
                //engagement logic
                if (b->armyID = redArmy.armyID){
                    
                    b->enemy_Battalion->in_fight = true;
                    
                    //##### config section #####
                    double crit_f = 0.005;
                    double miss = 0.03;
                    double nothing_happens = 0.985;
                    double prof_threshhold = 0.5;
                    //##### config section #####
                    
                    double blue_DMGmodifier  = b->enemy_Battalion->attack_power/(double)b->attack_power;
                    double red_DMGmodifier = (double)b->attack_power/b->enemy_Battalion->attack_power;

                    
                    /*
                    calculates survival modifier based on tech level normalised to modern age 
                     + level of army professionalism which represents combined army command & individual soldiers experience and military education
                    is then reduced by a threshold
                    then it negates it and adds to 1 which, the result of which is then used to modify is an soldier survives being hit
                    ### example ### 
                    modern army (e.g. Germany):
                    TL = 4,2; P = 0,8; 
                    ((4,2/4-1)+(0.8-0,5)) * -1 +1=
                    0.05+0.3 *-1 +1= 0.65

                    older army (e.g. Kazachstan or other CSAT-like countries with partly conscription based recruitment):
                    TL = 3,7; P = 0,45;
                    (-0.075 + -0.05) *-1 +1 = 1.125

                    so a modern day army with higher level of professionalism can expect its soldiers to die in combat 
                    (baseline_chance_to_die_from_being_hit)*0.65
                    but an older army with less technologically developed army and much less professionalism
                    can expect higher soldier deaths
                    

                    possible rework needed
                    */
                    double blue_survival_modifier = ((((blueArmy.technology_level/(double)4)-1)+(blueArmy.professionalism-prof_threshhold))*(-1))+1;
                    double red_survival_modifier = ((((redArmy.technology_level/(double)4)-1)+(redArmy.professionalism-prof_threshhold))*(-1))+1;
                    
                    //should be pretty self explanatory, other than the true shots mechanic - it's quite simple: the fact, that 
                    //a soldier landed a shot on enemy doesnt mean, it has gone through the soldiers armour/dmged a tank -> its a hit, 
                    //but it doens't have to be an automatic casualty 
                    int blue_munitions_lost = 0;
                    int blue_supplies_lost = 0;
                    int blue_true_shots_fired = 0;
                    
                    int red_munitions_lost = 0;
                    int red_supplies_lost = 0;                   
                    int red_true_shots_fired = 0;

                    //calculates the chance of each soldier in battallion firing upon enemy in 1 hour + is able to simulate randomness like shooting and missing or 
                    //f*ckups like jamming of the gun or anything that could be represented by loss of a combat supply (dmged tank/other weapons, missfire, etc)
                    //values configurable in config section above
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
                    
                    double blue_casualties = 0;
                    double red_casualties = 0;

                    //get the average cover of each battalion
                    auto blue_cover = scenario.get_cell(b->enemy_Battalion->position).cover;
                    auto red_cover = scenario.get_cell(b->position).cover;
                    //calculate number of casualties or simply "DMG dealt" 
                    blue_casualties = (double)red_true_shots_fired*red_DMGmodifier*(1.5-blue_cover);
                    red_casualties = (double)blue_true_shots_fired*blue_DMGmodifier*(1.5-red_cover);

                    //updates battalions after each hour in conflict
                    if (!b->enemy_Battalion->update_battalion(blue_casualties,blue_munitions_lost,blue_supplies_lost,blue_survival_modifier,hour)){
                        //blue battalion doesnt have healthy units
                        b->enemy_Battalion->in_fight = false;
                        b->in_fight = false;
                    }
                        
                    if (!b->update_battalion(red_casualties,red_munitions_lost,red_supplies_lost,red_survival_modifier,hour)){
                        //red battalion doesnt have healthy units
                        b->enemy_Battalion->in_fight = false;
                        b->in_fight = false;
                        b->position = std::make_pair(scenario.max_x,b->position.second);
                    }
                        

                }
            }
            else{
                if (b->armyID == blueArmy.armyID){
                    //blue army will try to reinforce position, looks out for the enemy
                }
                //logika pohybu cervenych
                if (b->armyID == redArmy.armyID){
                    if (b->moving){
                        b->moving -= 1.0;
                        if (b->moving < 0.0){
                            b->moving = 0.0;
                        }
                        continue;
                    }else{
                        int posx = b->position.first;
                        int posy = b->position.second;
                        double lowest_cover = 1;
                        double highest_cover = -1;
                        std::pair<int, int> lowest_cover_pos;
                        std::pair<int, int> highest_cover_pos;
                        
                        //looks on 3 cells from its position (to the left)
                        //
                        for (int i = -1; i <= 1; i++) {
                            if (posy+i < 0 || posy+i > scenario.max_y) continue; //don't run out of bounds
                            Cell &current_cell = scenario.get_cell(std::make_pair(posx-1, posy+i));

                            if (current_cell.occupation == Cell::red) continue;
                            //if modry =utok
                            if (current_cell.occupation == Cell::blue) {
                                b->enemy_Battalion = blueArmy.ret_battalion_on_position(std::make_pair(current_cell.posx,current_cell.posy));
                                b->in_fight = true;
                                    
                            } //TODO attack enemy
                            std::cout << current_cell.posx << "<-x cell y->" << current_cell.posy<< std::endl;
                            if (current_cell.cover < lowest_cover) {
                                lowest_cover = current_cell.cover;
                                lowest_cover_pos = std::make_pair(posx-1, posy+i);
                            }

                            if (current_cell.cover > highest_cover) {
                                highest_cover = current_cell.cover;
                                highest_cover_pos = std::make_pair(posx-1, posy+i);
                            }
                        }
                        std::cout << "highest cover: " << std::to_string(highest_cover) << "position x: " << std::to_string(highest_cover_pos.first) << " y: " << std::to_string(highest_cover_pos.second) << std::endl;
                        std::cout << " lowest cover: " << std::to_string(lowest_cover)<< "position x: " << std::to_string(lowest_cover_pos.first) << " y: " << std::to_string(lowest_cover_pos.second) << std::endl;
                        if (highest_cover == -1) continue; //all adjecent cells occupied by red
                        //looks on 3 cells to the left 1 cell column over to see, if there are any enemies
                        //if they are it choose to move to the highest possible cover
                        //else it goes to the lowest cover 
                        bool saw_blue = false;
                        for (int i = -1; i <=1; i++) {
                            if (posy+i < 0 || posy+i > scenario.max_y) continue; //don't run out of bounds
                            Cell c = scenario.get_cell(std::make_pair(posx-2, posy+i));
                            if (c.occupation == Cell::blue) {
                                saw_blue = true;
                                break;
                            }
                        }
                        //set to which cell the bat is moving
                        if (saw_blue) {
                            scenario.set_occupation(std::make_pair(posx, posy), Cell::neutral);
                            scenario.set_occupation(highest_cover_pos, Cell::red);
                            b->position = highest_cover_pos;
                            auto cover = scenario.get_cell(highest_cover_pos).cover;
                            b->moving = (double)2.25*(0.75+cover);
                        } else {
                            scenario.set_occupation(std::make_pair(posx, posy), Cell::neutral);
                            scenario.set_occupation(lowest_cover_pos, Cell::red);
                            b->position = lowest_cover_pos;
                            auto cover = scenario.get_cell(lowest_cover_pos).cover;
                            b->moving = (double)2.25*(0.75+cover);
                        }
                    }
                }
            }
        }   
    }
    return 0;
}