#include "knight.h"
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
bool levelup(int &level, int &levelO){
        if (level > levelO){
        if (level < 10) level++;
        return true;
        }
        return false;
}
void damage(string &event, int &level, int &levelO, int &HP){
    if (level < levelO) {
    float baseDamage = event=="1"?1:event=="2"?1.5:event=="3"?4.5:event=="4"?7.5:9.5;
    int damage = baseDamage * levelO * 10;
    HP = HP - damage;
    }
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
void HPcontrol(int &HP, int &MaxHP){
    if (HP>MaxHP) HP = MaxHP;
}
void mushmario(int &level,int &phoenixdown, int &HP, int&MaxHP){
                int s1=0,tempHP=HP,primecheck;
            int n1 = ((level + phoenixdown)%5 + 1) * 3;
            for (int i=99;i>99-n1*2;i-=2){
                s1+=i;
            }
            HP = HP + (s1%100);
            for (int i=HP-1;;i++){
                up:; i++;
                for (int j=2;j< HP/2;j++){
                    if (i%j==0) goto up;
                }
                HP = i;
                break;
            }
            HPcontrol(HP,MaxHP);
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
void potioncontrol(int &remedy,int &maidenkiss, int &phoenixdown){
    if (remedy>99) remedy=99;
    if (maidenkiss>99) maidenkiss=99;
    if(phoenixdown>99) phoenixdown=99;
}
void pickup(int &remedy,int &maidenkiss, int &phoenixdown,string &event){
    if (event=="15") remedy++;
    if (event=="16") maidenkiss++;
    if (event=="17") phoenixdown++;
    potioncontrol(remedy,maidenkiss,phoenixdown);
}
void usepotion(int &remedy,int &maidenkiss,int &j,int &k,int &HP,int &MaxHP,int &level,int &olevel){
    if (j>1){
        remedy--;
        HP *=5;
        if (HP > MaxHP) HP = MaxHP;
    } 
    if (k>1){
        maidenkiss--;
        level = olevel;
    }
}
//primecheck for lancelot
bool primeCheck(int MaxHP){
    for (int i=2;i<MaxHP/2;i++){
        if (MaxHP%i==0) return false;
    }
    return true;
}
bool kingCheck(int MaxHP){
    if (MaxHP==999) return true; else return false;
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
    int i = 1, j=-1, k=-1,n=0; //event array
    string event;
    //line1
    ifstream data,backup,backup1,backup2,backup3;
    data.open(file_input);
    string line1;
    getline(data, line1);
    stringstream stream1(line1);
    stream1>> HP >> level >>  remedy >> maidenkiss >> phoenixdown;

    //line2
    string line2,count;
    getline(data, line2);
    stringstream stream2(line2);
    stringstream stream2s(line2);
    while (stream2s >> count){n++;}

    //line3
    string line3;
    getline(data, line3);
    stringstream stream3(line3);
    string ghost,aclepius,merlin;
    getline(stream3,ghost,',');
    getline(stream3,aclepius,',');
    getline(stream3,merlin);
    data.close();

    rescue = -1; //initial
    int MaxHP = HP;
    int olevel=level;
    int as=0,mer=0;
    //processing
    while (stream2 >> event){
        //win ez
        //win
        if(event == "0") { if (HP>0) rescue=1;display(HP, level, remedy, maidenkiss, phoenixdown, rescue); break;};
        //level quai
        int levelO = levelOf(i);
        //quai quen
        if(event == "1" ||event=="2"||event == "3" ||event=="4"||event =="5"){
            if(primeCheck(MaxHP)||kingCheck(MaxHP)) level++;
            else if (levelup(level,levelO)) {} else damage(event,level,levelO,HP);
        }
        //phat^.
        else if (event == "6" && j<=0 && k<=0){
            if(primeCheck(MaxHP)||kingCheck(MaxHP)) level+=2;
        else if (levelup(level,levelO)) levelup(level,levelO); 
        else tiny(level, levelO,HP,remedy,j);
        }    
        
        //con coc
        else if (event == "7" && j<=0 && k<=0){
        if(primeCheck(MaxHP)||kingCheck(MaxHP)) level+=2;
        else if(levelup(level,levelO)) levelup(level,levelO);
        else frog(level,levelO,HP,maidenkiss,k);
        }    
        
        //nam MushMario
        else if (event=="11"){
            mushmario(level,phoenixdown,HP,MaxHP);
        }
        //nam Fibo
        else if (event == "12"){
            fibo(HP);
        }
        //nấm ma 👻
        else if(event[0]=='1'&&event[1]=='3'){
            backup.open(ghost);
            int n13,num,trunggian;
            string nstring,ghostline;
            getline(backup,nstring);
            n13 = stoi(nstring);
            getline(backup,ghostline);
            stringstream stream4(ghostline);
            int len = event.length();
            for (int i=2;i<len;i++){
                //ghost 1
                if (event[i] == '1'){
                    int max,min,maxi=0,mini=0;
                    getline(stream4,nstring,',');
                    max = stoi(nstring);
                    min = max;
                    for (int i=1,j;i<n13;i++){
                        getline(stream4,nstring,',');
                        num = stoi(nstring); 
                        if (num<=min) {min = num; mini=i;}
                        if (num>=max) {max = num; maxi=i;}
                    }
                    HP = HP - (maxi + mini);
                    //ghost 2
                } else if (event[i] == '2'){
                    int initial,mtx=0,mti=0;
                    getline(stream4,nstring,',');
                    initial = stoi(nstring);
                    getline(stream4,nstring,',');
                    num = stoi(nstring);
                    if (initial>num){
                        int check=0,num2=0;
                        for (int i=2;i<n13;i++){
                        getline(stream4,nstring,',');
                        num2 = stoi(nstring);
                        if (num>num2) check++;
                        num=num2;
                    }
                    if (check==n13-2) {
                        mtx = initial;
                        mti = 0;
                    }
                    } else if (initial==num) {
                        mtx = -2;
                        mti = -3;
                    }
                    else if (initial<num){
                        int check=0,num2=0,down=0,count,mtxtemp,mtitemp;
                        for (int i=2;i<n13;i++){
                        getline(stream4,nstring,',');
                        num2 = stoi(nstring);
                        if (num<num2&&down==0) {
                            check++;
                            num=num2;
                        }
                        else if (num>num2&&down==0){
                            down=1; check++;
                            mtxtemp=num;
                            mtitemp=i-1;
                            num=num2;
                        }
                        else if (num>num2&&down==1){
                            check++;
                            num=num2;
                        }
                        }
                        if (check==n13-2&&down==0){
                            mtx = num2;
                            mti = n13-1;
                        } else if (check==n13-2&&down==1){
                            mtx = mtxtemp;
                            mti = mtitemp;
                        } else {
                            mtx = -2;
                            mti = -3;
                        }
                    }
                    HP = HP - (mtx + mti);
                    //ghost 3
                } else if (event[i] == '3'){
                    int maxi2=0,mini2=0,xi,numi=1,max,min;
                    getline(stream4,nstring,',');
                    xi = stoi(nstring);
                    if (xi<0) xi = -xi;
                    xi = (17 * xi + 9)%257;
                    max=xi;min=xi;
                    for (int i=1,j;i<n13;i++){
                        getline(stream4,nstring,',');
                        xi = stoi(nstring); 
                        if(xi<0) xi = -xi;
                        xi = (17 * xi + 9)%257;
                        if(xi>max){maxi2=numi; max=xi;} 
                        if(xi<min){mini2=numi; min=xi;}
                        numi++;
                    }
                    HP = HP - (maxi2+mini2);
                    //nam 4
                } else if (event[i] == '4'){
                    int max2_3x,max2_3i=0,max1_3x,max1_3i=0;   
                    int xi,numi=1;
                    getline(stream4,nstring,',');
                    xi = stoi(nstring);
                    if (xi<0) xi = -xi;
                    xi = (17 * xi + 9)%257;
                    max1_3x=xi;
                    max2_3x=xi;
                    for (int i=1,j;i<3;i++){
                        getline(stream4,nstring,',');
                        xi = stoi(nstring); 
                        if(xi<0) xi = -xi;
                        xi = (17 * xi + 9)%257;
                        if(xi>max1_3x){max1_3x=xi;max1_3i=numi;} 
                        numi++;
                    } stream4.seekg(0,ios::beg);
                    getline(stream4,nstring,','); numi=1;
                    for (int i=1;i<3;i++){
                        getline(stream4,nstring,',');
                        xi = stoi(nstring); 
                        if(xi<0) xi = -xi;
                        xi = (17 * xi + 9)%257;
                        if((xi>max2_3x&&max2_3x<max1_3x)||(max2_3x==max1_3x)){max2_3x=xi;max2_3i=numi;}
                        numi++;
                    }
                    if (max2_3x==max1_3x) {
                        max2_3x = -5; max2_3i = -7;
                    }          
                    HP = HP - (max2_3x + max2_3i);
                }
                HPcontrol(HP,MaxHP);
                revive(HP,phoenixdown,rescue, MaxHP); if (rescue ==0) break;
                backup.close();
                //nam debug
                stream4.seekg(0,ios::beg);
            } backup.close();
        }
        //luom thuoc
        else if (event =="15"||event=="16"||event=="17"){
            pickup(remedy,maidenkiss,phoenixdown,event);
            usepotion(remedy,maidenkiss,j,k,HP,MaxHP,level,olevel);
        }
        //god of thuoc
        else if (event=="19"&&as==0){
            string thuoc,dong;
            int row,col,thuocint;
            backup2.open(aclepius);
            getline(backup2,thuoc); 
            row = stoi(thuoc);
            getline(backup2,thuoc); col = stoi(thuoc);
            for (int i=0;i<row;i++){
                int soluong=0;
                getline(backup2,dong);
                stringstream dongstream(dong); //cho nay nho sua istringstream
                for (int j=0;j<col;j++){
                    getline(dongstream, thuoc,' ');
                    thuocint = stoi(thuoc);
                    if ((thuocint==16||thuocint==17||thuocint==18)&&soluong<3){
                        soluong++;
                        if (thuocint==16) remedy++;
                        else if (thuocint==17) maidenkiss++;
                        else phoenixdown++;
                    }
                }
            }
            potioncontrol(remedy,maidenkiss,phoenixdown);
            usepotion(remedy,maidenkiss,j,k,HP,MaxHP,level,olevel);
            as++;
        }
        //bo$$ cuoi 💀☠
        else if (event=="99"){
            if(primeCheck(MaxHP)){
                if (level>=8){
                    level = 10;
                } else{
                    rescue =0;
                    display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
                    break;
                }

            } else if (kingCheck(MaxHP)) {
                    rescue=0;
                    display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
                    break;
            }
            else {
                if (level==10){
                } else {
                    rescue =0;
                    display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
                    break;
                }
            }
        }
        // merlin
        else if (event=="18"&&mer==0){
            string item,dongmerlin;
            int row;
            backup3.open(merlin);
            getline(backup3,dongmerlin);
            row = stoi(dongmerlin);
            for (int i=0;i<row;i++){
                getline(backup3,dongmerlin);
                if ((dongmerlin.find("merlin")!=string::npos||dongmerlin.find("Merlin")!=string::npos)) HP+=3;
                else if ((dongmerlin.find('m')!=string::npos||dongmerlin.find('M')!=string::npos)&&(dongmerlin.find("e")!=string::npos||dongmerlin.find("E")!=string::npos)&&(dongmerlin.find('r')!=string::npos||dongmerlin.find('R')!=string::npos)&&(dongmerlin.find("l")!=string::npos||dongmerlin.find('L')!=string::npos)&&(dongmerlin.find("i")!=string::npos||dongmerlin.find('I')!=string::npos)&&(dongmerlin.find('n')!=string::npos||dongmerlin.find('N')!=string::npos)) HP+=2;
            }
            HPcontrol(HP,MaxHP);
            mer++;
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
        if (i==n&&HP>0) rescue=1;
        //displaying
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
        //hoi sinh
        if (rescue ==0) break;
        //nhat do giua duong
        if (k<=0) olevel = level;
        i++;
    
    }

}
