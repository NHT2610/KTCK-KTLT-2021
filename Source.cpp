#include "Header.h"

int check;//Bien dieu kien thuc hien cac muc cua menu
string color[] = { "vang","nau","trang","den","xam" };//Danh sach cac mau long cua thu cung

Node* createANewNode(pet init_data)
{
	Node* newNode = new Node;
	if (newNode == NULL)//Truong hop khong du bo nho
	{
		cout << "Khong du bo nho!" << endl;
		return NULL;
	}
	newNode->data = init_data;
	newNode->next = NULL;
	return newNode;
}

void createANewLinkedList(linkedList& petList)
{
	petList.head = petList.tail = NULL;
}

bool check_petColor(string _petColor)
{
	int i = 0;
	while (i <= color->length())
	{
		if (_stricmp(_petColor.c_str(), color[i].c_str()) == 0)
			return true;//So sanh mau sac nhap vao voi danh sach cac mau, neu trung voi mau nao thi return true
		i++;
	}
	return false;
}

void addTail(linkedList& petList, Node* newNode)
{
	if (petList.head == NULL)
	{
		petList.head = petList.tail = newNode;
		return;
	}
	petList.tail->next = newNode;
	petList.tail = newNode;
}

pet* enterPetInformation(linkedList petList, int i)
{
	pet* newPet = new pet;
	string s = "end";
	cout << "# Nhap thong tin cho thu cung thu " << i << ":" << endl;
	//Nhap ma thu cung
	string _petCode;
	do
	{
		cout << "Nhap ma thu cung: ";
		getline(cin, _petCode);
		if (_stricmp(_petCode.c_str(), s.c_str()) == 0)
			return NULL;
		//Kiem tra xem ma thu cung vua nhap da ton tai trong danh sach hay chua
		if (searchPetNode(petList, _petCode, 1).petNode)
		{
			cout << "Vui long kiem tra ma cua thu cung ban vua nhap!" << endl;
			system("pause");
			continue;
		}
	} while (_petCode.length() != 7 || !checkForEnterNumber(_petCode, "integer") || searchPetNode(petList, _petCode, 1).petNode);
	newPet->petCode = _petCode;
	//Nhap ten thu cung
	string _petName;
	do
	{
		cout << "Nhap ten thu cung: ";
		getline(cin, _petName);
		if (_stricmp(_petName.c_str(), s.c_str()) == 0)
			return NULL;
	} while (1 > _petName.length() || _petName.length() > 30);
	newPet->petName = _petName;
	//Nhap can nang thu cung
	string _petWeight;
	do
	{
		cout << "Nhap can nang thu cung: ";
		getline(cin, _petWeight);
		if (_stricmp(_petWeight.c_str(), s.c_str()) == 0)
			return NULL;
	} while (!checkForEnterNumber(_petWeight, "real") || (0 > stof(_petWeight) || stof(_petWeight) >= 100));
	newPet->petWeight = stof(_petWeight);
	//Nhap tuoi thu cung
	string _petAge;
	do
	{
		cout << "Nhap tuoi thu cung: ";
		getline(cin, _petAge);
		if (_stricmp(_petAge.c_str(), s.c_str()) == 0)
			return NULL;
	} while (!checkForEnterNumber(_petAge, "integer") || (0 < stoi(_petAge) && stoi(_petAge) > 20));
	newPet->petAge = stoi(_petAge);
	//Nhap mau thu cung
	string _petColor;
	do
	{
		cout << "Nhap mau thu cung (mau sac chi gom: vang, nau, trang, den, xam): ";
		getline(cin, _petColor);
		if (_stricmp(_petAge.c_str(), s.c_str()) == 0)
			return NULL;
	} while (!check_petColor(_petColor));
	newPet->petColor = _petColor;
	return newPet;
}

void enter_petList(linkedList& petList)
{
	cout << "Nhap thong tin cua tung thu cung lien tuc, nhap 'end' de dung nhap" << endl;
	cout << "(Danh sach chi ghi nhan nhung thu cung da nhap du thong tin)" << endl;
	int i = 0;
	while (true)
	{
		pet* newPet = enterPetInformation(petList, i);
		if (newPet == NULL)//Neu nhap chuoi "end" thi break va ket thuc qua trinh nhap
			break;
		Node* newNode = createANewNode(*newPet);
		addTail(petList, newNode);
		i++;
	}
}

void deleteAll_petList(linkedList& petList)
{
	if (petList.head == NULL)
		return;
	Node* node = petList.head;
	while (node != NULL)
	{
		deleteHead(petList);
		node = petList.head;
	}
}

void print(information info)
{
	cout << left << setw(10) << info.index << left << setw(15) << info.petNode->data.petCode << left << setw(31) << info.petNode->data.petName << left << setw(20) << info.petNode->data.petWeight << left << setw(15) << info.petNode->data.petAge << left << setw(15) << info.petNode->data.petColor << endl;
}

void print_petList(linkedList& petList)
{
	cout << endl << "BANG DANH SACH THU CUNG CUA CUA HANG" << endl;
	cout << left << setw(10) << "STT" << left << setw(15) << "Ma" << left << setw(31) << "Ten" << left << setw(20) << "Can nang (kg)" << left << setw(15) << "Tuoi" << left << setw(15) << "Mau" << endl;
	Node* node = petList.head;
	int i = 0;
	while (node != NULL)
	{
		print({ i,node });
		node = node->next;
		i++;
	}
}

information searchPetNode(linkedList petList, string feature, int _case)
{
	if (_case == 1)//Truong hop tim kiem theo ma thu cung
	{
		int i = 0;
		Node* node = petList.head;
		while (node != NULL)
		{
			if (node->data.petCode == feature)
				return { i,node };
			node = node->next;
			i++;
		}
		return { i,NULL };
	}
	else//Truong hop tim kiem theo vi tri thu cung trong danh sach
	{
		int i = 0;
		Node* node = petList.head;
		while (node != NULL)
		{
			if (i == stoi(feature))
				return { i,node };
			node = node->next;
			i++;
		}
		return { i,NULL };
	}
}

void deleteHead(linkedList& petList)
{
	if (petList.head == NULL)//Truong hop danh sach rong
		return;
	Node* nodeDel = petList.head;
	petList.head = petList.head->next;
	delete nodeDel;
	if (petList.head == NULL)
		petList.head = petList.tail = NULL;
}

void deleteTail(linkedList& petList)
{
	if (petList.tail == NULL)//Truong hop danh sach rong
		return;
	Node* nodeDel = petList.tail;
	Node* node = petList.head;
	if (node->next == NULL)//Truong hop danh sach chi co mot phan tu
	{
		petList.head = petList.tail = NULL;
		delete nodeDel;
		return;
	}
	while (node->next != petList.tail)
		node = node->next;
	petList.tail = node;
	node->next = NULL;
	delete nodeDel;
}

void deletePetNode(linkedList& petList, information info)
{
	if (info.index == 0)
	{
		deleteHead(petList);
		return;
	}
	if (info.petNode == petList.tail)//Neu node can xoa la node head
	{
		deleteTail(petList);
		return;
	}
	Node* node = petList.head;
	Node* nodeDel = info.petNode;
	while (node->next != nodeDel)
		node = node->next;
	node->next = nodeDel->next;
	delete nodeDel;
}

void sellPets(linkedList& petList)
{
	string codeSell;
	do
	{
		cout << "Nhap ma cua thu cung can ban: ";
		getline(cin, codeSell);
		if (!searchPetNode(petList, codeSell, 1).petNode)
		{
			cout << "Ma thu cung ban nhap khong ton tai trong danh sach!" << endl;
			continue;
		}
	} while (!checkForEnterNumber(codeSell, "integer") || codeSell.length() != 7 || !searchPetNode(petList, codeSell, 1).petNode);
	//In thong tin thu cung can ban
	information info = searchPetNode(petList, codeSell, 1);
	cout << "THONG TIN THU CUNG CAN BAN:" << endl;
	cout << left << setw(10) << "STT" << left << setw(15) << "Ma" << left << setw(31) << "Ten" << left << setw(20) << "Can nang (kg)" << left << setw(15) << "Tuoi" << left << setw(15) << "Mau" << endl;
	print(info);
	float price = 100 + (info.petNode->data.petWeight) * 2 - info.petNode->data.petAge;
	cout << "Gia ban: " << price << " USD" << endl;
	int select = runSelectCommandOption(selectCommandOption(3));
	while (select == 0)
		select = runSelectCommandOption(selectCommandOption(3));
	//Xoa thu cung co ma la codeSell ra khoi sanh sach
	if (select == 1)
	{
		deletePetNode(petList, info);
		cout << "Cam on ban da mua thu cung tai cua hang chung toi!" << endl;
	}
	else
		cout << "Ban da KHONG chon mua thu cung nay!" << endl;
}

void addHead(linkedList& petList, Node* newNode)
{
	if (petList.head == NULL)
	{
		petList.head = petList.tail = newNode;
		return;
	}
	newNode->next = petList.head;
	petList.head = newNode;
}

void addPets(linkedList& petList, information info)
{
	pet* newPet = enterPetInformation(petList, info.index);
	Node* newNode = createANewNode(*newPet);
	if (info.index == 0)//Truong hop vi tri can them la vi tri head
	{
		addHead(petList, newNode);
		return;
	}
	else if (info.petNode == petList.tail)//Truong hop vi tri can them la vi tri cuoi danh sach
	{
		Node* node = petList.head;
		while (node->next != petList.tail)
			node = node->next;
		newNode->next = info.petNode;
		node->next = newNode;
		return;
	}
	else//Truong hop vi tri can them nam giua danh sach
	{
		int i = 0;
		Node* node = petList.head;
		while (i + 1 != info.index)
		{
			node = node->next;
			i++;
		}
		newNode->next = node->next;
		node->next = newNode;
	}
}

void update_petColor(information info)
{
	cout << "CAP NHAT MAU LONG CHO THU CUNG THU " << info.index << ":" << endl;
	cout << "Mau long ban dau cua thu cung nay la: " << info.petNode->data.petColor << endl;
	string _petColor;
	do
	{
		cout << "Cap nhat mau long cho thu cung (vang, nau, trang, den, xam): ";
		getline(cin, _petColor);
	} while (!check_petColor(_petColor));
	info.petNode->data.petColor = _petColor;
}

void deletePetWithWeightGreaterThan_k(linkedList& petList)
{
	string weight;
	do
	{
		cout << "Nhap nguong can nang k: ";
		getline(cin, weight);
	} while (!checkForEnterNumber(weight, "real") || 0 > stof(weight));
	float k = stof(weight);
	//Xoa cac node thoa man
	int count = 0;
	Node* node = petList.head;
	//Buoc 1: Neu node head thoa man thi xoa node dau, xoa den khi nao node head khong thoa man thi qua Buoc 2
	while (node != NULL && node->data.petWeight > k)
	{
		deleteHead(petList);
		count++;
		node = petList.head;
	}
	//Buoc 2: Neu truong hop ca danh sach thoa man => sau Buoc 1 ca danh sach da xoa => chuyen den Buoc 3
	while (node != NULL)
	{
		if (node == petList.tail && node->data.petWeight > k)
		{
			deleteTail(petList);
			node = petList.tail;//Sau khi xoa node tail thi node luc nay cung da bi xoa, can gan tro lai
			count++;			//node tail de thuc hien tiep cau lenh node->next
		}
		else if (node != petList.tail)
			while (node->next != petList.tail && node->next->data.petWeight > k)
			{//Xoa lien tuc cac phan tu thoa man khac node tail cho den khi gap phan tu khong thoa man
				Node* nodeDel = node->next;
				node->next = nodeDel->next;
				delete nodeDel;
				count++;
			}
		node = node->next;
	}
	//Buoc 3: Xuat ket qua
	if (count != 0)
		cout << "Da XOA tat ca cac thu cung co can nang lon hon nguong " << k << " ra khoi danh sach!" << endl;
	else
		cout << "Danh sach KHONG co thu cung nao co can nang vuot nguong " << k << "!" << endl;
}

int menu()
{
	system("cls");
	cout << "====== MENU ======" << endl;
	cout << "1. Khoi tao mot danh sach thu cung" << endl;
	cout << "2. Nhap thong tin thu cung va them vao danh sach" << endl;
	cout << "3. In danh sach thu cung vua nhap" << endl;
	cout << "4. Ban thu cung bang cach nhap ma" << endl;
	cout << "5. Them thu cung vao mot vi tri xac dinh trong danh sach" << endl;
	cout << "6. Cap nhat mau sac cho thu cung thong qua ma so" << endl;
	cout << "7. Xoa tat ca thong tin nhung thu cung co can nang lon hon nguong k (nguoi dung nhap)" << endl;
	cout << "8. Thoat" << endl;
	return 8;
}

int yourSelectFunction(int numberOfOptions)
{
	int select;
	cout << "Lua chon cua ban: ";
	cin >> select;
	while (cin.fail() || (select < 1 && select > numberOfOptions))
		cin.clear(); cin.ignore();
	return select;
}

string selectCommandOption(int _case)
{
	string select;
	if (_case == 1)
		cout << "Ban co muon THOAT [y/N] ? ";
	else if (_case == 2)
		cout << "Ban co muon THUC HIEN LAI lua chon nay [y/N] ? ";
	else
		cout << "Ban co dong y MUA [y/N] ? ";
	getline(cin, select);
	return select;
}

int runSelectCommandOption(string select)
{
	if (select == "y" || select == "Y")
		return 1;
	else if (select == "n" || select == "N")
		return -1;
	else
		return 0;
}

bool checkForEnterNumber(string inputNumber, string dataType)
{
	if (inputNumber == "")
		return false;
	int countPoint = 0;//Bien dem so dau "."
	for (size_t i = 0; i < inputNumber.length(); i++)
	{
		if (dataType == "integer")//Truong hop kiem tra so nguyen
		{
			if (isdigit(inputNumber[i]) == 0)
				return false;
		}
		else//Truong hop kiem tra so thuc
		{
			if (inputNumber[i] == '.')
				countPoint++;
			if (isdigit(inputNumber[i]) == 0)
				if (inputNumber[i] != '.' || (inputNumber[i] == '.' && countPoint > 1))
					return false;
		}
	}
	return true;
}

int childMenu()
{
	system("cls");
	cout << "====== Nhap thong tin thu cung va them vao danh sach ======" << endl;
	cout << "Danh sach DA CHUA thong tin!" << endl;
	cout << "Nhan phim 1 de khoi tao lai danh sach moi" << endl;
	cout << "Nhan phim 2 de them thong tin thu cung vao danh sach" << endl;
	cout << "Nhan phim 3 de thoat" << endl;
	return 3;
}

int runChildMenu(int& select)
{
	if (select == 1)
	{
		select = 3;
		return 1;
	}
	else if (select == 2)
	{
		select = 3;
		return 5;
	}
	else
	{
		int command = runSelectCommandOption(selectCommandOption(1));
		while (command == 0)
			command = runSelectCommandOption(selectCommandOption(1));
		if (command == 1)
			select = 3;
		else
			select = 0;
		return 0;
	}
}

void runMenu(int& yourSelect, linkedList& petList)
{
KHOITAO: if (yourSelect == 1)
{
	int select = -2;
	while (select != -1)
	{
		system("cls");
		cout << "====== Khoi tao mot danh sach thu cung ======" << endl;
		createANewLinkedList(petList);
		cout << "Mot danh sach thu cung RONG da duoc khoi tao!" << endl;
		select = runSelectCommandOption(selectCommandOption(2));
		while (select == 0)
			select = runSelectCommandOption(selectCommandOption(2));
	}
	check = 1;
}
if (yourSelect == 2)
{
	if (check == 0)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Nhap thong tin thu cung va them vao danh sach ======" << endl;
			cout << "Ban CHUA khoi tao danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 2)
	{
		int select = -1;
		while (select != 3)
		{
			select = yourSelectFunction(childMenu());
			yourSelect = runChildMenu(select);
		}
		if (yourSelect == 1)
			goto KHOITAO;
	}
	else
	{
		int select = -2;
		while (select != -1)
		{
			system("cls");
			cout << "====== Nhap thong tin thu cung va them vao danh sach ======" << endl;
			if (check == 2)
				deleteAll_petList(petList);
			enter_petList(petList);
			select = runSelectCommandOption(selectCommandOption(2));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(2));
			if (petList.head != NULL)
				check = 2;
			else
				check = 1;
		}
	}
}
if (yourSelect == 3)
{
	if (check == 0)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== In danh sach thu cung vua nhap ======" << endl;
			cout << "Ban CHUA khoi tao danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 1)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== In danh sach thu cung vua nhap ======" << endl;
			cout << "Ban CHUA nhap du lieu cho danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 3)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== In danh sach thu cung vua nhap ======" << endl;
			cout << "Danh sach da bi XOA het!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 4)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== In danh sach thu cung vua nhap ======" << endl;
			cout << "Da ban HET thu cung trong danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else
	{
		int select = -2;
		while (select != -1)
		{
			system("cls");
			cout << "====== In danh sach thu cung vua nhap ======" << endl;
			print_petList(petList);
			select = runSelectCommandOption(selectCommandOption(2));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(2));
		}
	}
}
if (yourSelect == 4)
{
	if (check == 0)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Ban thu cung bang cach nhap ma ======" << endl;
			cout << "Ban CHUA khoi tao danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 1)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Ban thu cung bang cach nhap ma ======" << endl;
			cout << "Ban CHUA nhap du lieu cho danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 3)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Ban thu cung bang cach nhap ma ======" << endl;
			cout << "Danh sach da bi XOA het!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 4)
	{
		int select = -2;
		while (select != -1)
		{
			system("cls");
			cout << "====== Ban thu cung bang cach nhap ma ======" << endl;
			cout << "Da ban HET thu cung trong danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else
	{
		int select = -2;
		while (select != -1)
		{
		BACK1:system("cls");
			cout << "====== Ban thu cung bang cach nhap ma ======" << endl;
			if (check == 4)
			{
				cout << "Da ban HET thu cung trong danh sach!" << endl;
				select = runSelectCommandOption(selectCommandOption(1));
				while (select == 0)
					select = runSelectCommandOption(selectCommandOption(1));
				if (select == 1)
					break;
				else
					goto BACK1;
			}
			sellPets(petList);
			if (petList.head == NULL)
				check = 4;//check == 4 => Da ban het thu cung
			select = runSelectCommandOption(selectCommandOption(2));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(2));
		}
	}
}
if (yourSelect == 5)
{
	if (check == 0)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Them thu cung vao mot vi tri xac dinh trong danh sach ======" << endl;
			cout << "Ban CHUA khoi tao danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 1)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Them thu cung vao mot vi tri xac dinh trong danh sach ======" << endl;
			cout << "Ban CHUA nhap du lieu cho danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 3)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Them thu cung vao mot vi tri xac dinh trong danh sach ======" << endl;
			cout << "Danh sach da bi XOA het!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 4)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Them thu cung vao mot vi tri xac dinh trong danh sach ======" << endl;
			cout << "Da ban HET thu cung trong danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else
	{
		int select = -2;
		while (select != -1)
		{
			system("cls");
			cout << "====== Them thu cung vao mot vi tri xac dinh trong danh sach ======" << endl;
			string index;
			do
			{
				cout << "Nhap vi tri can them thu cung: ";
				getline(cin, index);
				if (!checkForEnterNumber(index, "integer") || !searchPetNode(petList, index, 2).petNode)
				{
					cout << "Vi tri ban nhap khong co trong danh sach!" << endl;
					continue;
				}
			} while (!checkForEnterNumber(index, "integer") || stoi(index) < 0 || !searchPetNode(petList, index, 2).petNode);
			information info = searchPetNode(petList, index, 2);
			addPets(petList, info);
			cout << "Thong tin thu cung vua duoc them vao vi tri " << info.index << " trong danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(2));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(2));
		}
	}
}
if (yourSelect == 6)
{
	if (check == 0)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Cap nhat mau sac cho thu cung thong qua ma so ======" << endl;
			cout << "Ban CHUA khoi tao danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 1)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Cap nhat mau sac cho thu cung thong qua ma so ======" << endl;
			cout << "Ban CHUA nhap du lieu cho danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 3)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Cap nhat mau sac cho thu cung thong qua ma so ======" << endl;
			cout << "Danh sach da bi XOA het!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 4)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Cap nhat mau sac cho thu cung thong qua ma so ======" << endl;
			cout << "Da ban HET thu cung trong danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else
	{
		int select = -2;
		while (select != -1)
		{
			system("cls");
			cout << "====== Cap nhat mau sac cho thu cung thong qua ma so ======" << endl;
			string code;
			do
			{
				cout << "Nhap ma thu cung can cap nhat mau sac: ";
				getline(cin, code);
				if (!searchPetNode(petList, code, 1).petNode)
				{
					cout << "Ma ban vua nhap khong ton tai trong danh sach!" << endl;
					continue;
				}
			} while (!checkForEnterNumber(code, "integer") || code.length() != 7 || !searchPetNode(petList, code, 1).petNode);
			information info = searchPetNode(petList, code, 1);
			update_petColor(info);
			cout << "Da cap nhat THANH CONG mau sac cho thu cung co ma " << code << endl;
			select = runSelectCommandOption(selectCommandOption(2));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(2));
		}
	}
}
if (yourSelect == 7)
{
	if (check == 0)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Xoa tat ca thong tin nhung thu cung co can nang lon hon nguong k (nguoi dung nhap) ======" << endl;
			cout << "Ban CHUA khoi tao danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 1)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Xoa tat ca thong tin nhung thu cung co can nang lon hon nguong k (nguoi dung nhap) ======" << endl;
			cout << "Ban CHUA nhap du lieu cho danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 3)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Xoa tat ca thong tin nhung thu cung co can nang lon hon nguong k (nguoi dung nhap) ======" << endl;
			cout << "Danh sach da bi XOA het!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else if (check == 4)
	{
		int select = -2;
		while (select != 1)
		{
			system("cls");
			cout << "====== Xoa tat ca thong tin nhung thu cung co can nang lon hon nguong k (nguoi dung nhap) ======" << endl;
			cout << "Da ban HET thu cung trong danh sach!" << endl;
			select = runSelectCommandOption(selectCommandOption(1));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(1));
		}
	}
	else
	{
		int select = -2;
		while (select != -1)
		{
		BACK2: system("cls");
			cout << "====== Xoa tat ca thong tin nhung thu cung co can nang lon hon nguong k (nguoi dung nhap) ======" << endl;
			if (check == 3)
			{
				cout << "Danh sach da bi XOA het!" << endl;
				select = runSelectCommandOption(selectCommandOption(1));
				while (select == 0)
					select = runSelectCommandOption(selectCommandOption(1));
				if (select == 1)
					break;
				else
					goto BACK2;
			}
			deletePetWithWeightGreaterThan_k(petList);
			if (petList.head == NULL)
				check = 3;
			select = runSelectCommandOption(selectCommandOption(2));
			while (select == 0)
				select = runSelectCommandOption(selectCommandOption(2));
		}
	}
}
if (yourSelect == 8)
{
	int select = runSelectCommandOption(selectCommandOption(1));
	while (select == 0)
		select = runSelectCommandOption(selectCommandOption(1));
	if (select == 1)
		yourSelect = 8;
	else
		yourSelect = 0;
}
}