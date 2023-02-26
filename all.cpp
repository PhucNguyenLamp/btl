//#main.h
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

//#knight.h
//level quai
int levelOf(int i){
        int b=i%10;
        int levelO = i > 6?(b > 5?b : 5) : b;
    return levelO;
}
//event 0
bool event0(int event){
    if (event == 0)
    return true; else return false;
}
//event 1-5
bool event1_5(int event){
    if (event == 1||event == 2||event ==3|| event ==4||event ==5)
    return true; else return false;
}
bool levelup(int &level, int &levelO){
        if (level > levelO){
        if (level < 10) level++;
        return true;
        }
        return false;
}
void damage(int &event, int &level, int &levelO, int &HP){
    if (level < levelO) {
    float baseDamage = event==1?1:event==2?1.5:event==3?4.5:event==4?7.5:9.5;
    int damage = baseDamage * levelO * 10;
    HP = HP - damage;
    }
}
bool event6(int event,int j, int k){
    if (event == 6 && j<=0&&k<=0) return true; else return false;

}
void tiny(int &level, int &levelO, int &HP, int &remedy, int &j){
    if (level < levelO) {
        if (remedy>=1){
        remedy--;
        } else {
        HP/=5;
        if (HP==0) HP = 1;
        j=4; //vi qua luot nay la con 3
        }
    }
}
bool event7(int event,int j, int k){
    if (event == 7 && j<=0&&k<=0) return true; else return false;
}
void frog(int &level, int &levelO, int &HP, int &maidenkiss, int &k){
        if (level < levelO) {
        if (maidenkiss>=1){
            maidenkiss--;
        } else {
        level=1;
        k=4;
        }
}
}
bool event11(int event){
    if (event == 11)
    return true; else return false;
}
void mushmario(int &level,int &phoenixdown, int &HP){
                int s1=0;
            int n1 = ((level + phoenixdown)%5 + 1) * 3;
            for (int i=99;i>99-n1*2;i-=2){
                s1+=i;
            }
            HP = HP + (s1%100);
}
bool event12(int event){
    if (event == 12)
    return true; else return false;
}
void fibo(int &HP){
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
bool event13(string &ghostEvent){
    if (ghostEvent[0]=='1'&&ghostEvent[1]=='3')
    return true; else return false;
}
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
void HPcontrol(int &HP, int &MaxHP){
    if (HP>MaxHP) HP = MaxHP;
}
void potioncontrol(int &remedy,int &maidenkiss, int &phoenixdown){
    if (remedy>99) remedy=99;
    if (maidenkiss>99) maidenkiss=99;
    if(phoenixdown>99) phoenixdown=99;
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
    int event, i = 1, j=-1, k=-1,n=0; //event array
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
    stringstream stream2s(line2);
    while (stream2s >> event){n++;}

    //line3
    string line3;
    getline(data, line3);
    stringstream stream3(line3);
    string ghost,aclepius,merlin;
    getline(stream3,ghost,',');
    getline(stream3,aclepius,',');
    getline(stream3,merlin);

    rescue = -1; //initial
    int MaxHP = HP;
    int olevel = level;

    //processing
    while (stream2 >> event){
        //win
        if(event0(event)) break;
        //level quai
        int levelO = levelOf(i);
        //quai quen
        if(event1_5(event)){
            if(levelup(level,levelO)) {} else damage(event,level,levelO,HP);
        }
        //phat^.
        if (event6(event,j,k)){
        if (levelup(level,levelO)) levelup(level,levelO); 
        else tiny(level, levelO,HP,remedy,j);
        }    
        
        //con coc
        if (event7(event,j,k)){
        if(levelup(level,levelO)) levelup(level,levelO);
        else frog(level,levelO,HP,maidenkiss,k);
        }    
        
        //nam MushMario
        if (event11(event)){
            mushmario(level,phoenixdown,HP);
        }
        //nam Fibo
        if (event12(event)){
            fibo(HP);
        }
        //nấm ma 👻
        string ghostEvent = to_string(event);
        backup.open(ghost);
        if(event13(ghostEvent)){
            int n13,num,trunggian;
            string nstring;
            getline(backup,nstring);
            n13 = stoi(nstring);
            int len = ghostEvent.length();
            getline(backup,nstring,',');
            for (int i=2;i<len;i++){
                //ghost 1
                if (ghostEvent[i] == '1'){
                    int max,min,maxi=0,mini=0,numi=1;
                    max = stoi(nstring);
                    min = max;
                    for (int i=2,j;i<=n13;i++){
                        getline(backup,nstring,',');
                        num = stoi(nstring); 
                        if (num<min) {min = num; mini=numi;}
                        if (num>max) {max = num; maxi=numi;}
                        numi++;
                    }
                    HP = HP - (maxi + mini);
                    //ghost 2
                } else if (ghostEvent[i] == '2'){
                    // int initial;
                    // getline(backup,nstring,',');
                    // initial = stoi(nstring);
                    // for (int i=2,j;i<=n13;i++){
                    //     getline(backup,nstring,',');
                    //     num = stoi(nstring);
                    //     if (initial>num){

                    //     } else if (initial==num) break;
                    //     else if (initial<num){

                    //     }
                    // }
                    //ghost 3
                } else if (ghostEvent[i] == '3'){
                    int maxi2=0,mini2=0,xi,numi=1,max,min;
                    xi = stoi(nstring);
                    if (xi<0) xi = -xi;
                    xi = (17 * xi + 9)%257;
                    max=xi;min=xi;
                    for (int i=1,j;i<n13;i++){
                        getline(backup,nstring,',');
                        xi = stoi(nstring); 
                        if(xi<0) xi = -xi;
                        xi = (17 * xi + 9)%257;
                        if(xi>max){maxi2=numi; max=xi;} 
                        if(xi<min){mini2=numi; min=xi;}
                        numi++;
                    }
                    HP = HP - (maxi2+mini2);
                    //nam 4
                } else if (ghostEvent[i] == '4'){
                    int max2_3x,max2_3i;   
                    int maxi2=0,mini2=0,xi,numi=1,max,min;
                    xi = stoi(nstring);
                    if (xi<0) xi = -xi;
                    xi = (17 * xi + 9)%257;
                    max=xi;min=xi;
                    for (int i=1,j;i<n13;i++){
                        getline(backup,nstring,',');
                        xi = stoi(nstring); 
                        if(xi<0) xi = -xi;
                        xi = (17 * xi + 9)%257;
                        if(xi>max){maxi2=numi; max=xi;} 
                        if(xi<min){mini2=numi; min=xi;}
                        numi++;
                    }          
                    HP = HP - (max2_3x + max2_3i);
                }
                HPcontrol(HP,MaxHP);
                revive(HP,phoenixdown,rescue, MaxHP); if (rescue ==0) break;
            }        
        }
        //clock
        revive(HP,phoenixdown,rescue, MaxHP);
        j--; if (j==0){
            HP *=5;
            if (HP > MaxHP) HP = MaxHP;
        }   

        k--; if (k==0){
            level=olevel;
        }   
        if (i==n&&HP>0) rescue =1;
        //displaying
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
        //hoi sinh
        if (rescue ==0) break;
        //nhat do giua duong

        i++;
    
    }

}

//main.cpp
int main() {
    string file_input = "tc1_input"; // chỗ này lúc nộp nhớ sửa thành argv nha Phúc
    int HP, level, remedy, maidenkiss, phoenixdown, rescue;
    adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    return 0;
}