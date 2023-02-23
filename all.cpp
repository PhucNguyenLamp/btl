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
    int event ,i = 1, j=-1; //event array
    rescue = -1; //initial
    ifstream data;
    data.open("tc1_input");
    data >> HP >> level >>  remedy >> maidenkiss >> phoenixdown;
    int MaxHP = HP;

    //processing
    while (data >> event){
        
        if (event == 0) {
            rescue = 1;
            break;
        }

        int b=i%10;
        int levelO = i > 6?(b > 5?b : 5) : b;

        if (event == 1||event == 2||event ==3|| event ==4||event ==5){
            if (level > levelO){
                if (level < 10) level++;
            }
            else if (level < levelO) {
                float baseDamage = event==1?1:event==2?1.5:event==3?4.5:event==4?7.5:9.5;
                int damage = baseDamage * levelO * 10;
                HP = HP - damage;
            }

            if (event == 6){
            if (level > levelO){
                level+=2;
                if (level>10) level=10;
            }
            else if (level < levelO) {
                if (remedy>=1){
                    remedy--;
                    break;
                }
                HP/=5;
                if (HP==0) HP = 1;
                j=3;
            }    
            }

            if (HP<=0 && phoenixdown<=0){
                rescue = 0;
                break;
            }
            else if (HP<=0 && phoenixdown>0){
                phoenixdown--;
                HP = MaxHP;
            }

        j--; if (j==0){
            HP *=5;
            if (HP > MaxHP) HP = MaxHP;
        }   
        i++;
        }
        rescue = 1;
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