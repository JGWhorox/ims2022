#include <vector>
#include <random>

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