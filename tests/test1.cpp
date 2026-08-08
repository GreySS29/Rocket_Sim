#include <iostream>
double get (double a, double b, double c){
    a+= b * c;
};


int main ()
{
    double a = 8;
    double b = 1;
    double c = 2;
    a = get(a,b,c);
    std::cout << a;
}