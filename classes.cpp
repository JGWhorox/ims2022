#include "classes.h"

Brigade::remove_dead_units(){
    for (auto u : units){
        if (u.state == unit::dead){
            units.remove(u);
        }
    }
}

Soldier::Soldier(int u, int a, int f, int at){
    for (size_t i = 0; i < units; i++)
    {
        Unit new_unit;
        new_unit.state == Unit::healthy;
        units.push_back(new_unit);
    }
    ammo = a;
    food = f;
    antitank = at;
}

Soldier::attack(){
    //TODO
    return;
}

Soldier::reposition(){
    //TODO
    return;
}

Medic::Medic(int u, int a, int f, int m){
    for (size_t i = 0; i < units; i++)
    {
        Unit new_unit;
        new_unit.state == Unit::healthy;
        units.push_back(new_unit);
    }
    ammo = a;
    food = f;
    meds = m;
}

Medic::heal_units(std::list<Unit> units){
    if (!resources) return;
    
    for (auto u : units){
        if (u.state == Unit::wounded){
            // TODO add randomness here
            u.state == Unit::healthy;
            resources--;
        }
    }
}

Tank::Tank(int u, int a, int f){
    for (size_t i = 0; i < units; i++)
    {
        Unit new_unit;
        new_unit.state == Unit::healthy;
        units.push_back(new_unit);
    }
    ammo = a;
    food = f;
}

Tank::attack(){
    //TODO
    return;
}

Tank::reposition(){
    //TODO
    return;
}

