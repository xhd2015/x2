//============================================================================
// Name        : x2-test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <regex>
#include <iostream>
#include <cstdio>
using namespace std;


const char* KEY_MAP_STD[]={
    "UNUSED","ESC",
	"1",		"2",			"3",      "4",   "5",  "6",  "7",       "8",    "9",   "0",
	"_",		"=",			"BS",     "TAB", "q",  "w",  "e",       "r",    "t",    "y",
	"u",		"i",			"o",      "p",  "[",  "]",  "Enter",   "CNTL", "a",    "s",
	"d",		"f",			"g",       "h",  "j",  "k",  "l",       ";",    "'",    "`",
	"LSHFT",	"\\",			"z",  	  "x",  "c",  "v",  "b",       "n",    "m",    ",",
	".",      "/",  "RSHFT","*","ALT"," ","CAP","F1","F2","F3","F4","F5","F6",
    "F7","F8","F9","F10","NUML","CtrlBreak","Home","Up","PgUp","-","Left","Center","Right","+","End","Down","PgDn",
	"Ins","Del","Unknown","Unknown","Unknown","F11","F12","Unkown","Unknown","Windows","Unknown","Menu",
	"RESERVED","RESERVED", "RESERVED","RESERVED","RESERVED",
	"RESERVED","RESERVED","RESERVED","RESERVED","RESERVED" ,//10RESERVED
	"RightALT","RigthCTRL"
};

const int KEY_MAP_STD_LEN=sizeof(KEY_MAP_STD)/sizeof(char*);


extern "C" int P;
int main() {
//	for(int i=0;i<KEY_MAP_STD_LEN;++i)
//	   cout << i << ":"<< KEY_MAP_STD[i] << std::endl;
	printf("P=%p\n",P);
	return 0;
}
