#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>
#include<vector>
#include <list>
#include <thread>
#include <windows.h>
#include <limits>
#include <random>
#include <unordered_map>
struct point
{
	int x;
	int y;

};
#include <cstdlib>
#include <ctime>
struct move 
{
	point hope;
	bool IsHit; 

};
#define SEA '_'
#define SHIP '#'
#define MISS '*'
#define HIT 'x' 
