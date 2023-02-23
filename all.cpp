//#main.h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

//#knight.h

//knight.cpp
void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    //inital
    int event ,i = 1; //event array
    int MaxHP = HP;
    level = 1; // 1-> 10 
    rescue = -1; //initial
    ifstream data;
    data.open("tc1_input");
    data >> HP >> level >>  remedy >> maidenkiss >> phoenixdown;

    //processing
    while (data >> event){
        if (event == 0) {
            rescue = 1;
            break;
        }
        if (event == 1||event == 2||event ==3|| event ==4||event ==5){
            
        }
    }
    //rescue = 

    //displaying
    end:display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 

}

//main.cpp
int main() {
    string file_input = "tc1_input"; // chỗ này lúc nộp nhớ sửa thành argv nha Phúc
    int HP, level, remedy, maidenkiss, phoenixdown, rescue;
    adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    return 0;
}