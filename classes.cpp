#include <cstdlib>
#include <vector>
#include <sstream>
#include <iostream>
#include <simlib.h>
#include "classes.h"

/*
use this if you want ot use remove lul
bool Unit::operator==(const Unit & u){
    return this->state == u.state;
}*/


Battalion generate_battalion(int Inf, int Inf_size, int Cs,int Cs_size, int T, int T_size, int armyID, int posx, int posy){
    Battalion b;
    for (int i = 0; i < Inf; i++){
        Company* c =new Company(Inf_size,Inf_size*5,Inf_size*9,Inf_size/10);
        c->type = Company::infantry;
        b.companies.push_back(c);
    }

    for (int i = 0; i < Cs; i++){
        Company* c = new Company(Cs_size,Cs_size*3,Cs_size*9,Cs_size);
        c->type = Company::combat_support;
        b.companies.push_back(c);
    }

    for (int i = 0; i < T; i++){
        Company* c = new Company(T_size,T_size*5,T_size*36,0);
        c->type = Company::tank;
        b.companies.push_back(c);
    }

    b.armyID = armyID;
    b.position = std::make_pair(posx,posy);
    
    return b;
}

void Battalion::call_backup(Army army){
    Battalion closest_bat;
    closest_bat.position.first = -1;
    for (auto bat: army.battalions){
        if (bat.in_fight) continue;
        if (closest_bat.position.first = -1) {
            closest_bat = bat;
            continue;
        }
        
        if (bat.position.first < closest_bat.position.first) closest_bat = bat;
    }
    
    if (closest_bat.position.first = -1) return;

    int Inf;
    int Inf_size; 
    int Cs;
    int Cs_size;
    int T;
    int T_size;
    int armyID = closest_bat.armyID;
    int posx = position.first;
    int posy = position.second;
    for (auto comp : closest_bat.companies) {
        switch (comp->type)
        {
        case Company::infantry:
            Inf += 1;
            Inf_size = comp->units.size() / 2;
            break;
        case Company::combat_support:
            Cs += 1;
            Cs_size = comp->units.size() / 2;
            break;
        case Company::tank:
            T += 1;
            T_size = comp->units.size() / 2;
            break;
        }

        for (int i = 0; i < comp->units.size() / 2; i++){
            comp->units.pop_front();
            comp->units_reinforced_other_battalion += 1;
        }
    }

    Battalion backup = generate_battalion(Inf, Inf_size, Cs, Cs_size, T, T_size, armyID, posx, posy);
    backup.is_backup = true;
    backup.backup_timeout = abs(backup.position.first - closest_bat.position.first) * 3;
    army.battalions.push_back(backup);

}

bool Battalion::update_battalion(double casualties, int munition_lost, int supplies_lost, double survival_modifier, int hour){
    //int number_of_companies = battalion.get_number_of_companies();
    
    //std::vector<Company*> companies_vector;

    for (auto c : this->companies){
        //companies_vector.push_back(&c);
        c->DMG_taken += casualties/(double)c->ret_current_healthy_size();
        c->ammo -= munition_lost/(double)c->ret_current_healthy_size();
        c->supplies -= supplies_lost/(double)c->ret_current_healthy_size();

        while (c->DMG_taken >= 1.0){
            auto x = Random();
            auto u = c->ret_healthy_unit();

            if (u == nullptr){
                return false;
            }

            if (x < 0.18*survival_modifier){
                u->state == Unit::dead;
                c->units_died++;
            }
            else{
                u->state == Unit::wounded;
                u->time_of_last_injury = hour;
                c->units_wounded++;
            }
            c->DMG_taken -= 1.0;
        }
    }
    return true;
    
}

int Battalion::get_number_of_companies(){
    return this->companies.size();
}

int Battalion::get_base_attack_power(){
    int retval;
    for (auto c : companies ){
        if (c->type == Company::tank){
            retval += c->units.size()*250;
        }
        else{
            retval += c->units.size()*10;
        }
         
    }
    return retval;
}

int Battalion::get_number_of_healthy_units(){
    int retval;
    for (auto c : companies ){
            retval += c->units.size();
    }
    return retval;
}
//debug

void Company::remove_dead_units(){
    for (auto u = units.begin(); u != units.end() ; ){
        if (u->dead == Unit::dead){
            units_died++;
            units.erase(u++);
        }
        else
            u++;
    }
}
Unit* Company::ret_healthy_unit(){
    for (auto &u : this->units){
        if (u.state == Unit::healthy){
            return &u;
        }
        else{
            return nullptr;
        }
    }
}

int Company::ret_current_healthy_size(){
    int retval = 0;
    for (auto u : units) {
        if (u.state == Unit::healthy)
            retval++; 
    }
    return retval;
}

int Company::ret_current_wounded_size(){
    int retval = 0;
    for (auto u : units) {
        if (u.state == Unit::wounded)
            retval++; 
    }
    return retval;
}

Company::Company(int u, int a, int f, int s){
    for (size_t i = 0; i < u; i++)
    {
        Unit new_unit;
        new_unit.state = Unit::healthy;
        units.push_back(new_unit);
    }
    ammo = a;
    food = f;
    supplies = s;
}

void Company::heal_units(std::list<Unit> units){
    if (!supplies) return;
    
    for (auto u : units){
        if (u.state == Unit::wounded){
            // TODO add randomness here
            u.state = Unit::healthy;
            supplies--;
        }
    }
}

void Army::report_stats(int hour, bool debug){
    if (!((hour % 24 && debug) || hour % 168 || hour % 720)) return;
    std::stringstream ss;
    int ibat = 0;
    int icomp = 0;
    int iunit = 0;
    ss << "Army stats:" << std::endl;
    ss << "Logistics effectivity: " << std::to_string(logistics_effectivity) << " ";
    ss << "Professionalism: " << std::to_string(professionalism) << " ";
    ss << "Technology level: "  << std::to_string(technology_level) << " ";
    ss << "Anni supplies: " << std::to_string(ammo_supplies) << " ";
    ss << "Food supplies: " << std::to_string(food_supplies) << " ";
    ss << "Combat supplies: "<< std::to_string(combat_supplies) << " ";
    ss << "Battalion stats:" << std::endl;
    for (auto bat: battalions){
        ss << "Battalion " << std::to_string(++ibat) << " ";
        ss << "Position x: " << std::to_string(bat.position.first) << " ";
        ss << "Position y: " << std::to_string(bat.position.second) << " ";
        ss << "State: ";
        if (bat.in_fight) ss << "in_fight ";
        if (bat.moving) ss << "moving ";
        if (bat.is_backup) ss << "is_backup_with_timeout " << std::to_string(bat.backup_timeout) << " ";
        ss << "ACC: " << std::to_string(bat.action_cooldown_counter);
        ss << "Attack power: " << bat.attack_power;
        ss << "Companies: " << std::endl;
        for (auto comp : bat.companies){
            ss << "Company " << std::to_string(++icomp) << " ";
            ss << "Type: ";
            switch (comp->type){
            case Company::infantry:
                ss << "infantry ";
                break;
            case Company::combat_support:
                ss << "combat_support ";
                break;
            case Company::tank:
                ss << "tank ";
                break;
            }
            ss << "DMG taken: " << std::to_string(comp->DMG_taken) << " ";
            ss << "Ammo:" << std::to_string(comp->ammo) << " ";
            ss << "Food" << std::to_string(comp->food) << " ";
            ss << "Supplies" << std::to_string(comp->supplies) << " ";
            ss << "Units died" << std::to_string(comp->units_died) << " ";
            ss << "Units wounded" << std::to_string(comp->units_wounded) << " ";
            ss << "Units recovered" << std::to_string(comp->units_recovered) << " ";
            ss << "Units reinforced other bat" << std::to_string(comp->units_reinforced_other_battalion) << " ";
            ss << "Units: " << std::endl;
            for (auto unit : comp->units){
                ss << "Unit " << std::to_string(++iunit) << " ";
                ss << "State: ";
                switch (unit.state){
                    case Unit::healthy:
                        ss << "healthy ";
                        break;
                    case Unit::wounded:
                        ss << "wounded ";
                        break;
                    case Unit::dead:
                        ss << "dead ";
                        break;
                }
                ss << "Last injury: " << std::to_string(unit.time_of_last_injury) << " ";
                ss << "Medical procedures: " << std::to_string(unit.number_of_medical_procedures) << std::endl;
            }
        }
    }
    std::cout << ss.str() << std::endl;
}
