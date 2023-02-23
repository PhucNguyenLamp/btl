#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>
     using namespace std;
  
       
       

int main(){
    int event = 5;
                float baseDamage = event==1?1:event==2?1.5:event==3?4.5:event==4?7.5:9.5;
cout << baseDamage;
}