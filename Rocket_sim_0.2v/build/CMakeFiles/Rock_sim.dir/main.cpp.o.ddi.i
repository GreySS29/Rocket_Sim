# 0 "/home/greys/Documents/Doc/C+/my_progect/Rocket_Sim/Rocket_sim_0.2v/main.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3
# 0 "<command-line>" 2
# 1 "/home/greys/Documents/Doc/C+/my_progect/Rocket_Sim/Rocket_sim_0.2v/main.cpp"
import gravity_temp;

struct Cat {
    double mass;
};

struct Dog {
    double mass;
};

int main() {
    Cat c{4.5};
    Dog d{12.0};

    auto s = add_mass(c, d);
}
