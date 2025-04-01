#pragma once
#include"mainInclude.h"
#include"MainLogics.h"
#include"UnitTest.h"
class Visual
{
	MainLogics logic;
	bool IsOnline = false;
public:
	int VisualMenu(unsigned int NumberMenu) {}
	void VisualHistoryBattle(std::list<std::string> History) {
		system("cls");
		for (auto pair : History)
		{
			std::cout << pair << std::endl;
		}
		int temp;
		std::cin >> temp;

		if (temp == 3)
		{
			return;
		}
		else if (true) {

		}
	}
	void changeMode() {
		system("cls");
		std::cout << "����� ������:\n";
		std::cout << "1. ���� ������" << " "<< " " << "2. ���� ������\n";

	
		
		std::cout << "�����\n";
	
		int temp;
		std::cin >> temp;


		if (temp == 3)
		{
			return;
		}
		else if(temp == 1)
		{
			gameOnline();
		}
		else if(temp == 2)
		{
			gameOfline();
			
		}
	}

	void gameOnline() {
		system("cls");
		
		std::cout << "1.�������������� � �����\n";
		std::cout << "2.������� �����\n";
		int temp;
		std::cin >> temp;
		if (temp == 3)
		{
			return;
		}
		else if (temp == 1)
		{
			logic.StartGameOline(false);
		}
		else if (temp == 2)
		{
			logic.StartGameOline(true);
		}
		else
		{
			return; 
		}
		IsOnline = true;
		dispersalOfShipsMenu();


	}

	void gameOfline() {
		system("cls");
		std::cout << "���� ������\n";
		std::cout << "����� ��������� ����\n";
		std::cout << "����\n";
		std::cout << "���������\n";
		std::cout << "������\n";
	
		int temp;
		std::cin >> temp;
		if (temp >= 4)
		{
			return;
		}
		else
		{
			logic.CreateGameWBot(temp);
			
			dispersalOfShipsMenu();
		}

	}
	//���������� ������ 
	void gameMenu() {
	//�����������,,������ �� ������ ))
		system("cls");
		std::cout << "������� ����:\n";
		std::cout << "������� '3' ����� ��������� \n";
		int hope;
		std::cin >> hope;

		if (hope == 3)
		{
			return;
		}
		else if (true)
		{	

		}

	}

	void mainMenu() {
		int temp;
		do
		{	
			system("cls");
		/*		UnitTest hope;
			hope.FellMap(&logic);
			gameOfline();*/


			std::cout << "������� ����:\n";
			std::cout << "������\n";
			std::cout << "������� ����\n";

	

			std::cin >> temp;

			if (temp == 1)
			{
				changeMode();
			}
			else if (temp == 2)
			{
				VisualHistoryBattle(logic.getHistoryBattle("Data.txt"));
			}

		} while (temp != 0);

	}

		void battleMenu() {
			system("cls");
		
					//���� ����� ����.����� ���� � ���� ��������� ����� �����(� ����� ��� �������)
			

			while (logic.IsGameRunning())
			{
				char temp;
				 short int x = -1;
				 short int y = -1;
		
					logic.showMap();
				if (logic.whoseStep())
				{
					std::cin.ignore();
					//��� � ������� �������� � ����� (����� ���������) 
					std::cin >> x >> y;
					if (std::cin.fail()) {
						// ��������� ���� ������������� ����
						std::cin.clear(); // ���������� ���� ������
						std::cin.ignore(); // ������� �����
						std::cout << "������: �� ����� �� �����. ���������� �����.\n";
						x = -1;
						y = -1;
					}

					logic.MakeMove(x, y);
				}
				else {
			
					logic.EnemyMove();
				}
				
			}
			logic.RecordingHistoryBattle();
			
		}

		void SetCursorPosition(int x, int y) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
			SetConsoleCursorPosition(hConsole, position);
		}

		void dispersalOfShipsMenu() {
			
			//for (size_t i = 0; i < 10; i++)		// ���������� �������� 

			//{
			//	
			//
			//

			//	system("cls");
			//	std::cout << "��������� �������\n";
			//	logic.arr();
			//	int x1, x2, y1, y2;
			//	do {

			//		std::cin >> x1 >> y1 >> x2 >> y2;
			//	
			//	}while (!logic.checkRules(x1, y1, x2, y2));
			//	logic.dispersalOfShips(x1, y1, x2, y2);
			//	

			//}
			logic.randomDispersal(true);

			
			
		
			
			if (IsOnline)
			{
				logic.acceptSendShips();
			}
				battleMenu();
		}


	std::vector<void (Visual::*)()> vecMenu = { &Visual::mainMenu, &Visual::changeMode, &Visual::gameMenu, &Visual::dispersalOfShipsMenu, &Visual::gameOnline, &Visual::gameOfline };

	

		void ChangeMenu(unsigned int index) {
			if (index < vecMenu.size()) {
				(this->*vecMenu[index])();
			}
		}

		//������� � ������� ���� ������� ����� ���� ��� ������ (������� ������)
		//���� ��� ��� ���� ������ 
		//���������� �������� � �� ������������ 
		//���������� �������� 
		//������ ����� ���� � ���� ��� ���� ������ 
		//�������� ������� ���� � ������������������� �����
		//��������� ����� ��� ������ ����
		//�������� ��� � ������ ���� ����� �������� ( ��������)) )

		//(�������� ������)
		//����������� ��� ��� ��������� ������� 
		//����������� ��� �����, ����� ������ � ��������� 
		//����� ������� ���� � ������ ��� 
		//��� �������� ����� ����� ��������� � ����� ����� 
	};

