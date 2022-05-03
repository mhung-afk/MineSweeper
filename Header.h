#pragma once
#include <iostream>
#include <stdio.h>
#include <ctime>

#pragma comment (lib, "winmm.lib")

#define ConsoleWidth 100
#define ConsoleHeight 40

#define ClickLeft 0x5A
#define ClickRight 0x58

#define ChangeMusic  0x53

struct CauTrucBang
{
	short SDong = 0;  //dòng
	short SCot = 0;   //cột
	short SSoBom = 0;  //số bom
	short SSoODaMo = 0; //ô đã mở
	short SSoCo = 0; //
};
struct CauTrucO
{
	bool BCoBom = false;  //ô có bom
	bool BDaMo = false;    //ô đã mở
	bool BCamCo = false;   //ô cắm cờ
	short SBomLanCan =0;  //Số bom ở lân cận
};
