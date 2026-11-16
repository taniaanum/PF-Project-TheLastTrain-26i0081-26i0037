
;
// Primitive helper utilities, clamping, and screen control


#include<iostream>
#include "util.h"
using namespace std;

int clampInt(int val, int minVal, int maxVal){
   if (val<minVal) return minVal;
   if (val>maxVal) return maxVal;               
   return val;
}

void trimWhitespace(char* str){

}


bool stringEquals(const char* a, const char* b){
    int i=0; 
        while(a[i]!='\0' && b[i]!='\0'){
            if (a[i]!=b[i]) return false;
            i++;
        }
    return a[i]=='\0' && b[i]=='\0';
}


void printHeader(const char* title){
    cout << "===========================================\n";
    cout << " " << title << "\n";
    cout << "===========================================\n";


}


void clearScreen(){

    for (int i=0; i<50; i++) 
    cout << "\n";

}



