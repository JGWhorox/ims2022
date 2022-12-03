#include "classes.h"

/*
use this if you want ot use remove lul
bool Unit::operator==(const Unit & u){
    return this->state == u.state;
}*/


Battalion generate_battalion(int Inf, int Inf_size, int Cs,int Cs_size, int T, int T_size, int armyID, int posx, int posy){
    Battalion b;
    for (int i = 0; i < Inf; i++){
        b.companies.push_back(new Infantry(Inf_size,Inf_size*5,Inf_size*9,Inf_size/10));
    }

    for (int i = 0; i < Cs; i++){
        b.companies.push_back(new CombatSupport(Cs_size,Cs_size*3,Cs_size*9,Cs_size));
    }

    for (int i = 0; i < T; i++){
        b.companies.push_back(new Tank(T_size,T_size*5,T_size*36));
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
    
    //backup logic
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

int Company::ret_current_wounded_size(){
    int retval = 0;
    for (auto u : units) {
        if (u.state == Unit::wounded)
            retval++; 
    }
    return retval;
}

Infantry::Infantry(int u, int a, int f, int at){
    for (size_t i = 0; i < u; i++)
    {
        Unit new_unit;
        new_unit.state = Unit::healthy;
        units.push_back(new_unit);
    }
    ammo = a;
    food = f;
    antitank = at;
}

void Infantry::attack(){
    //TODO
    return;
}

void Infantry::reposition(){
    //TODO
    return;
}

CombatSupport::CombatSupport(int u, int a, int f, int s){
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

void CombatSupport::heal_units(std::list<Unit> units){
    if (!supplies) return;
    
    for (auto u : units){
        if (u.state == Unit::wounded){
            // TODO add randomness here
            u.state = Unit::healthy;
            supplies--;
        }
    }
}

Tank::Tank(int u, int a, int f){
    for (size_t i = 0; i < u; i++)
    {
        Unit new_unit;
        new_unit.state = Unit::healthy;
        units.push_back(new_unit);
    }
    ammo = a;
    food = f;
}

void Tank::attack(){
    //TODO
    return;
}

void Tank::reposition(){
    //TODO
    return;
}

