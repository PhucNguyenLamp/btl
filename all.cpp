//#main.h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

//#knight.h
//hoi sinh
void revive(int &HP, int &phoenixdown,int &rescue, int &MaxHP){
        if (HP<=0 && phoenixdown<=0){
            rescue = 0;
        }
        else if (HP<=0 && phoenixdown>0){
            phoenixdown--;
            HP = MaxHP;
        }
}

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

    //line1
    ifstream data,backup;
    data.open("tc1_input");
    string line1;
    getline(data, line1);
    stringstream stream1(line1);
    stream1>> HP >> level >>  remedy >> maidenkiss >> phoenixdown;

    //line2
    string line2;
    getline(data, line2);
    stringstream stream2(line2);

    //line3
    string line3;
    getline(data, line3);
    stringstream stream3(line3);
    string ghost,aclepius,merlin;
    getline(stream3,ghost,',');
    getline(stream3,aclepius,',');
    getline(stream3,merlin);


    int event, i = 1, j=-1, k=-1; //event array
    rescue = 1; //initial
    
    int MaxHP = HP;
    int olevel = level;

    //processing
    while (stream2 >> event){
        //win
        if (event == 0) {
            break;
        }
        //level quai
        int b=i%10;
        int levelO = i > 6?(b > 5?b : 5) : b;
        //quai quen
        if (event == 1||event == 2||event ==3|| event ==4||event ==5){
            if (level > levelO){
                if (level < 10) level++;
            }
            else if (level < levelO) {
                float baseDamage = event==1?1:event==2?1.5:event==3?4.5:event==4?7.5:9.5;
                int damage = baseDamage * levelO * 10;
                HP = HP - damage;
            }
        }
        //phat^.
        if (event == 6 && j<=0&&k<=0){
        if (level > levelO){
            level+=2;
            if (level>10) level=10;
        }
        else if (level < levelO) {
            if (remedy>=1){
                remedy--;
            } else {
            HP/=5;
            if (HP==0) HP = 1;
            j=4; //vi qua luot nay la con 3
            }
        }    
        }
        //con coc
        if (event == 7&&j<=0&&k<=0){
        if (level > levelO){
            level+=2;
            if (level>10) level=10;
        }
        else if (level < levelO) {
            if (maidenkiss>=1){
                remedy--;
            } else {
            level=1;
            k=4;
            }
        }    
        }
        //nam MushMario
        if (event == 11){
            int s1=0;
            int n1 = ((level + phoenixdown)%5 + 1) * 3;
            for (int i=99;i>99-n1*2;i-=2){
                s1+=i;
            }
            HP = HP + (s1%100);
        }
        //nam Fibo
        if (event ==12){
            if (HP ==1) {} else{
            int fibo1=1,fibo2=1,n=0;
            while (fibo2<HP){
                n=fibo2;
                fibo2+=fibo1;
                fibo1=n;
            }
            HP = fibo1;
            }
        }
        //nấm ma 👻
        string ghostEvent = to_string(event);
        backup.open(ghost);
        if(ghostEvent[0]=='1'&&ghostEvent[1]=='3'){
            int len = ghostEvent.length();
            for (int i=2;i<len;i++){
                if (ghostEvent[i] == '1'){
                    
                } else if (ghostEvent[i] == '2'){
                    
                } else if (ghostEvent[i] == '3'){
                    
                } else if (ghostEvent[i] == '4'){

                }
                if (HP > MaxHP) HP = MaxHP;
                revive(HP,phoenixdown,rescue, MaxHP); if (rescue ==0) break;
            }        
        }
       
        //hoi sinh
        revive(HP,phoenixdown,rescue, MaxHP); if (rescue ==0) break;
        //nhat do giua duong

        //postprocessing
        j--; if (j==0){
            HP *=5;
            if (HP > MaxHP) HP = MaxHP;
        }   

        k--; if (k==0){
            level=olevel;
        }   

        i++;
    
    }

    //displaying
    display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 

}

//main.cpp
int main() {
    string file_input = "tc1_input"; // chỗ này lúc nộp nhớ sửa thành argv nha Phúc
    int HP, level, remedy, maidenkiss, phoenixdown, rescue;
    adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    return 0;
}