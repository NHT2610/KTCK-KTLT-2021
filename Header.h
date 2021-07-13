#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

extern int check;//Bien dieu kien thuc hien cac muc cua menu

struct pet//struct thu cung
{
	string petCode;
	string petName;
	float petWeight{};
	int petAge{};
	string petColor;
};

struct Node
{
	pet data{};
	Node* next{};
};

struct information//la kieu du lieu chua thong tin cua tung node trong danh sach
{
	int index;
	Node* petNode;
};

struct linkedList
{
	Node* head;
	Node* tail;
};

extern string color[5]; //Danh sach cac mau long cua thu cung
//Danh sach cac ham thuc thi chinh 
Node* createANewNode(pet init_data);
void createANewLinkedList(linkedList& petList);
pet* enterPetInformation(linkedList petList, int i);
bool check_petColor(string _petColor);
void deleteAll_petList(linkedList& petList);
void enter_petList(linkedList& petList);
void print(information info);
void print_petList(linkedList& petList);
void addTail(linkedList& petList, Node* newNode);
information searchPetNode(linkedList petList, string feature, int _case);
void deleteHead(linkedList& petList);
void deleteTail(linkedList& petList);
void deletePetNode(linkedList& petList, information info);
void sellPets(linkedList& petList);
void addHead(linkedList& petList, Node* newNode);
void addPets(linkedList& petList, information info);
void update_petColor(information info);
void deletePetWithWeightGreaterThan_k(linkedList& petList);
//Danh sach cac ham dieu khien menu
int menu();
void runMenu(int& yourSelect, linkedList& petList);
int yourSelectFunction(int numberOfOptions);
string selectCommandOption(int _case);
int runSelectCommandOption(string select);
bool checkForEnterNumber(string inputNumber, string dataType);
int childMenu();
int runChildMenu(int& select);