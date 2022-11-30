#ifndef CLASSES_H
#define CLASSES_H


// parent classes
class Unit {
  public:
    enum State {healthy, wounded, dead};
    State state; // state of the unit
};

class Brigade {
  public:
    std::list<Unit> units; // number of units
    int ammo; // the amount of ammo
    int food; // the amount of food

    void add_units(int amount);
    void remove_dead_units();
};

// child classes
class Soldier(Brigade) {
    public:
        int antitank; // amount of antitank resources

        Soldier(int u, int a, int f, int at);
        void attack();
        void reposition();
};

class Medic(Brigade) {
    public:
        int meds; // healing resources

        Medic(int u, int a, int f, int m);
        void heal_units(std::list<Unit>);
};

class Tank(Brigade) {
    public:
        Tank(int u, int a, int f);
        void attack();
        void reposition();
};

#endif
