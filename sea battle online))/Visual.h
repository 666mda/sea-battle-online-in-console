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
		std::cout << "Выбор режима:\n";
		std::cout << "1. Игра онлайн" << " "<< " " << "2. Игра офлайн\n";

	
		
		std::cout << "Назад\n";
	
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
		
		std::cout << "1.Присойдениться к лобби\n";
		std::cout << "2.Создать лобби\n";
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
		std::cout << "Игра офлайн\n";
		std::cout << "Выбор сложности бота\n";
		std::cout << "лайт\n";
		std::cout << "нормально\n";
		std::cout << "сложно\n";
	
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
	//поредачить визуал 
	void gameMenu() {
	//БЕСПОЛЕЗНАЯ,,НИЧЕГО НЕ ДЕЛАЕТ ))
		system("cls");
		std::cout << "История боев:\n";
		std::cout << "Введите '3' чтобы вернуться \n";
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


			std::cout << "Главное меню:\n";
			std::cout << "Играть\n";
			std::cout << "История боев\n";

	

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
		
					//надо чтобы мейн.логик имел в себе настройки какая битва(с ботом или игроком)
			

			while (logic.IsGameRunning())
			{
				char temp;
				 short int x = -1;
				 short int y = -1;
		
					logic.showMap();
				if (logic.whoseStep())
				{
					std::cin.ignore();
					//баг с записью символов и чисел (потом исправить) 
					std::cin >> x >> y;
					if (std::cin.fail()) {
						// Обнаружен ввод неправильного типа
						std::cin.clear(); // Сбрасываем флаг ошибки
						std::cin.ignore(); // Очищаем буфер
						std::cout << "Ошибка: вы ввели не число. Попробуйте снова.\n";
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
			
			//for (size_t i = 0; i < 10; i++)		// количество кораблей 

			//{
			//	
			//
			//

			//	system("cls");
			//	std::cout << "Раставьте корабли\n";
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

		//менюшка в которой надо выбрать онлан игра или офлайн (входные данные)
		//ввод имя при игре онлайн 
		//координаты кораблей и их расположение 
		//координаты стрельбы 
		//запрос ввода айпи и порт при игре онлайн 
		//просмотр истории боев и последовательностью ходов
		//сложности ботов для офлайн игры
		//написать чат в онлайн игре чтобы общаться ( материть)) )

		//(выходные данные)
		//реализовать чат для получения ответов 
		//реализовать две карты, карта игрока и соперинка 
		//вывод истории боев и повтор игр 
		//при создании хоста вывод айпишника и порта хоста 
	};

