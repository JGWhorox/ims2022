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
