#pragma once
#include"mainInclude.h"
#include "bot.h"
#include "network.h"
class MainLogics
{
	std::string GetLocalTime()
	{
		//для генерации рандомных весов
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// Получаем текущее время
		auto now = std::chrono::system_clock::now();

		// Преобразуем время в локальное время
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		// Используем localtime_s для безопасного форматирования времени
		std::tm tm_time;
		localtime_s(&tm_time, &now_time);

		// Форматируем время в строку
		char buffer[80];
		strftime(buffer, sizeof(buffer), "%Y-%m-%d %H-%M-%S", &tm_time);
		std::string LocalTime = buffer;
		return LocalTime;
	}
	struct RecMove {

		move temp;
		bool whoseMove;

	};
	Bot* bot;
	network net;
	bool IsServ = false;

	struct Ships
	{

		size_t size;
		int x1,x2,y1,y2;
		move* arr;


		Ships(int x1, int x2, int y1, int y2, int size = 1) {
			this->size = size;
			arr = new move[size];
			this->x1 = x1;
			this->x2 = x2;
			this->y1 = y1;
			this->y2 = y2;
			if (x2 == x1)
			{

				for (size_t i = 0, y = y1; i < size; i++, y++)
				{
					arr[i].hope.y = y;
					arr[i].hope.x = x1;
					arr[i].IsHit = true;
				}
			}
			else if(y2 == y1){

				for (size_t i = 0, x = x1; i < size; i++, x++)
				{
					arr[i].hope.x = x;
					arr[i].hope.y = y1;
					arr[i].IsHit = true;
				}
			}	
		
	
		}

		~Ships() {
			delete[]arr;
		}

	};
	bool checkAttack(int x, int y, Ships*ship) {
		for (size_t i = 0; i < ship->size; i++)
		{
			if (ship->arr[i].IsHit && ship->arr[i].hope.x == x && ship->arr[i].hope.y == y)
			{
				ship->arr[i].IsHit = false;
				std::cout << "Попадание\n";
				return true;
			}
		}
		std::cout << "Промах\n";
		return false;

	}

	unsigned long int counterMoves = 0;

	unsigned long int ourMoves = 0;
	
	std::unordered_map<unsigned long int, move> History;

	std::unordered_map<unsigned long int, move> OurHistory;

	std::vector<RecMove> HistoryBattle;

	void SetCursorPosition(int x, int y) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
		SetConsoleCursorPosition(hConsole, position);
	}
	char map[10][10] = {
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' } };
	Ships* ship;
	std::list<Ships*> listOfShip;
	std::list<Ships*> listOfShipEnemy;
	char enemyMap[10][10] = {
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' } };
	bool WhoMove = true;
	bool makeEnemyMove(point ishit){
		for (auto pair : listOfShip)
		{
			if (checkAttack(ishit.x, ishit.y, pair))
			{
				map[ishit.x][ishit.y] = HIT;
				RecMove glorp;
				glorp.temp.hope = ishit;
				glorp.whoseMove = false;
				HistoryBattle.push_back(glorp);
				return true;
			}

		}
		map[ishit.x][ishit.y] = MISS;
		RecMove glorp;
		glorp.temp.hope = ishit;
		glorp.whoseMove = false;
		HistoryBattle.push_back(glorp);
		return false;
	}
	

	int amountShip = 0;
	int amountShipEnemy = 0 ;

public:
	~MainLogics() {
		RecordingHistoryBattle();
	}
	MainLogics() {
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t a = 0; a < 10; a++)
			{
				map[i][a] = SEA;
				
			}
		}
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t a = 0; a < 10; a++)
			{
				enemyMap[i][a] = SEA;

			}
		}
	}
	 
	bool IsCardFull() {
		if (listOfShip.size() < 10)
		{
			return false;
		}
		return true;
	}

	void SetColor(int textColor, int backgroundColor) {
		// Получаем дескриптор стандартного вывода (консоли)
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		// Устанавливаем цвет текста и фона
		SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | textColor);
	}




	void destroyShip(Ships * ship, bool isEnemy) {
		
			int fx1, fy1, fx2, fy2;
			fx1 = ship->x1 - 1;
			fy1 = ship->y1 - 1;
			fx2 = ship->x2 + 1;
			fy2 = ship->y2 + 1;


			if (fx1 < 0) fx1 = 0;
			if (fy1 < 0) fy1 = 0;

			if (fx2 > 9) fx2 = 9;
			if (fy2 > 9) fy2 = 9;

			for (int i = fy1; i <= fy2; i++)
			{
				for (int a = fx1; a <= fx2; a++)
				{
				
					if (isEnemy)
					{
						enemyMap[a][i] = MISS;
				
					}
					else
					{
						map[a][i] = MISS;
					}
				}
			}
			for (size_t i = 0; i < ship->size; i++)
			{
				if (isEnemy)
				{
					
					enemyMap[ship->arr[i].hope.x][ship->arr[i].hope.y] = '%';
				
				}
				else
				{
					
					map[ship->arr[i].hope.x][ship->arr[i].hope.y] = '%';
				}
			}
	
	}

	bool IsGameRunning() {

		
		for (auto it = listOfShip.begin(); it != listOfShip.end();) {
			bool hope = false;

			for (size_t i = 0; i < (*it)->size; i++) {
				if ((*it)->arr[i].IsHit == true) {
					hope = true;
					break;
				}
			}
			
		
			if (!hope) {
				auto temp = it;
				destroyShip(*temp, false);
				amountShip--;
				delete* temp; 
				it = listOfShip.erase(temp);
			}
			else
			{
				it++;
			}
				

		}
		
		for (auto it = listOfShipEnemy.begin(); it != listOfShipEnemy.end();) {
			bool hope = false;

			for (size_t i = 0; i < (*it)->size; i++) {
				if ((*it)->arr[i].IsHit == true) {
					hope = true;
					break; // Выход из внутреннего цикла, если найдено попадание
				}
			}

			if (!hope) {
				auto temp = it;
				destroyShip(*temp, true);
				delete* temp; // Удаляем объект, на который указывает указатель
				amountShipEnemy--;
				it = listOfShipEnemy.erase(temp); // Удаляем сам указатель из списка и обновляем итератор
			}
			else
			{
				it++;
			}

		}


		if (amountShipEnemy < 1 || amountShip < 1 )
		{
			delete bot;
			return false;
		}
		return true;
	}

	void showMap() {
		system("cls");
		std::cout << " " << " ";
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << i << " ";
		}
		for (size_t x = 0, m = 0; x < 10; x++, m++)
		{
			SetCursorPosition(30 + (x + m), 0);
			std::cout << x << " ";
		}
		std::cout << "\n";
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << i << " ";
			for (size_t x = 0; x < 10; x++)
			{
				if (map[i][x] == '%')
				{
					std::cout << "\033[31m";
				}
				std::cout << map[i][x] << ' ';
				SetColor(7, 0);
			}
			for (size_t x = 0, m = 0; x < 10; x++,m ++)
			{

					SetCursorPosition(30 + (x + m), i + 1);
					if (enemyMap[i][x] == '%')
					{
						std::cout << "\033[31m";
					}
				std::cout << enemyMap[i][x] << " ";
				SetColor(7, 0);
			}
			std::cout << i <<"\n";
		}
		if (WhoMove)
		{
			std::cout << "Ваш ход\nзаписывать y | x: ";
			
		}
		else {
			std::cout << "Ход противника: ";
		}
	}

	bool whoseStep() {
		return WhoMove;

	}

	bool MakeMove(int x, int y) {
		//передача ходу противнику 
		if (x < 0 || y < 0)
		{
			std::cout << "Неверный ввод\n";
			return false;
		}

		if (x > 9 || y > 9 || x < 0 || y < 0)
		{
			std::cout << "Выход за карту\n";
			return false;
		}
		
		move hope;

		hope.hope.x = x;
		hope.hope.y = y;
		for (auto pair : listOfShipEnemy)
		{
			if (checkAttack(x,y, pair))
			{
				enemyMap[x][y] = HIT;
				hope.IsHit = false;
				OurHistory[ourMoves] = hope;
				if (bot == nullptr)
				{
					std::string temp;
					temp = std::to_string(x);
					temp += std::to_string(y);
					temp += std::to_string(!WhoMove);
					if (IsServ)
					{

						net.sendClient(temp);
					}
					else
					{
						net.sendToServer(temp);
					}

				}
				RecMove glorp;
				glorp.temp = hope;
				glorp.whoseMove = true;
				HistoryBattle.push_back(glorp);
				return true;
			}

		}

		enemyMap[x][y] = MISS;
		hope.IsHit = true;
		OurHistory[ourMoves] = hope;
		WhoMove = !WhoMove;
		if (bot == nullptr)
		{
			std::string temp;
			temp = std::to_string(x);
			temp += std::to_string(y);
			temp += std::to_string(!WhoMove);
			if (IsServ)
			{

				net.sendClient(temp);
			}
			else
			{
				net.sendToServer(temp);
			}

		}
		RecMove glorp;
		glorp.temp = hope;
		glorp.whoseMove = true;
		HistoryBattle.push_back(glorp);
		return false;
	}

	void arr() {
		/*SetColor(2, 0);*/
		std::cout << " " << " ";
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << i << " ";
		}
		std::cout << "\n";
		for (size_t i = 0; i < 10; i++)
		{
			std::cout << i << " ";
			for (size_t x = 0; x < 10; x++)
			{
				
			std::cout << map[i][x] << ' ';
					
			}

			std::cout << "\t"<< listOfShip.size()<<" / 10 \n";
		}
	
	
	}

	void EnemyMove() {
		//передача ходов противника 
		
		if (bot == nullptr)
		{
			std::string temp;

			if (IsServ)
			{
				
				 temp = net.sendClient(" ");
			}
			else
			{

				 temp = net.sendToServer(" ");
					
			}
			point miss;

			miss.x = temp[0]-48;
			miss.y = temp[1]-48;

			makeEnemyMove(miss);
			WhoMove = temp[2]-48;

		}
		else {
			point temp = bot->MakeMove(History);
			move hope;	
			hope.hope.x = temp.x;
			hope.hope.y = temp.y;
			hope.IsHit = makeEnemyMove(temp);
			History[counterMoves] = hope;
			counterMoves++;
			WhoMove = !WhoMove;
		}

	}
	
	bool CreateGameWBot(int complicationBot) {
		if (complicationBot < 1 || complicationBot > 3)
		{
			return false;
		}
		test();
		bot = new Bot(complicationBot);
	}
	//	!!!!!!!!!! opasno ne zaxodit ato ybiet
	void randomDispersal(bool IsOurDispersal) {



		//реализация вертикального расположения корбалей на оооочень долгий ящик 
		for (size_t i = 0; i < 4; i++)
		{
			int x1 = std::rand() % 10;
			int y1 = std::rand() % 10;
			
			
			while (!checkRules(x1, y1, x1, y1)) {
			
				x1 = std::rand() % 10;
				y1 = std::rand() % 10;

			}
			dispersalOfShips(x1, y1, x1, y1, IsOurDispersal);

		}





		for (size_t i = 0; i < 3; i++)
		{
			int x1 = std::rand() % 10;
			int y1 = std::rand() % 10;
			while (!checkRules(x1, y1, x1, y1 + 1)) {

				x1 = std::rand() % 10;
				y1 = std::rand() % 10;
			}

			dispersalOfShips(x1, y1, x1, y1 + 1, IsOurDispersal);
		/*	bool vertical = std::rand() % 2;
			if (vertical)
			{

			while (!checkRules(x1, y1, x1, y1 + 1)) {

				x1 = std::rand() % 10;
				y1 = std::rand() % 10;

			}
			dispersalOfShips(x1, y1, x1, y1 + 1, IsOurDispersal);
			}
			else
			{
				while (!checkRules(x1, y1, x1 + 1, y1)) {

					x1 = std::rand() % 10;
					y1 = std::rand() % 10;
				}

				dispersalOfShips(x1, y1, x1 + 1, y1, IsOurDispersal);

			}*/
		}
	







		for (size_t i = 0; i < 2; i++)
		{
			int x1 = std::rand() % 10;
			int y1 = std::rand() % 10;
			while (!checkRules(x1, y1, x1, y1 + 2)) {

				x1 = std::rand() % 10;
				y1 = std::rand() % 10;
			}

			dispersalOfShips(x1, y1, x1, y1 + 2, IsOurDispersal);
	/*		bool vertical = std::rand() % 2;
			if (vertical) {
			
				while (!checkRules(x1, y1, x1, y1 + 2)) {
					x1 = std::rand() % 10;
					y1 = std::rand() % 10;
				}
				dispersalOfShips(x1, y1, x1, y1 + 2, IsOurDispersal);
			}
			else
			{
			while (!checkRules(x1, y1, x1 + 2, y1)) {

				x1 = std::rand() % 10;
				y1 = std::rand() % 10;

			}
			dispersalOfShips(x1, y1, x1 + 2, y1, IsOurDispersal);
			}*/
		

		}
	
		
		





		for (size_t i = 0; i < 1; i++)
		{
			int x1 = std::rand() % 10;
			int y1 = std::rand() % 10;
			while (!checkRules(x1, y1, x1, y1 + 3)) {

				x1 = std::rand() % 10;
				y1 = std::rand() % 10;
			}

			dispersalOfShips(x1, y1, x1, y1 + 3, IsOurDispersal);
	/*		bool vertical = std::rand() % 2;
			if (vertical)
			{

			while (!checkRules(x1, y1, x1 + 3, y1)) {

				x1 = std::rand() % 10;
				y1 = std::rand() % 10;

			}
			dispersalOfShips(x1, y1, x1 + 3, y1, IsOurDispersal);
			}
			else
			{
				while (!checkRules(x1, y1, x1, y1 + 3)) {

					x1 = std::rand() % 10;
					y1 = std::rand() % 10;

				}
			dispersalOfShips(x1, y1, x1, y1 + 3, IsOurDispersal);
			}*/
		
			
		}

	
	}

	void test() {
			dispersalOfShips(0, 0, 0, 0, false);
			dispersalOfShips(9, 0, 9, 0, false);
			dispersalOfShips(0, 9, 0, 9, false);
			dispersalOfShips(9, 9, 9, 9, false);
			dispersalOfShips(4, 4, 4, 7, false);
			dispersalOfShips(6, 6, 6, 8, false);
			dispersalOfShips(8, 3, 8, 4, false);
			dispersalOfShips(0, 5, 0, 7, false);
			dispersalOfShips(0, 2, 0, 3, false);
			dispersalOfShips(2, 3, 2, 4, false);
	}

	std::string RecordingHistoryBattle() {
		std::string name = GetLocalTime()+".txt";
		std::ofstream hope(name, std::ios::out);

		for (auto pair : HistoryBattle)
		{
			hope << pair.whoseMove << " " << pair.temp.IsHit << " " << pair.temp.hope.y << " " << pair.temp.hope.x << " \n";
		}
		std::ofstream glorp("Data.txt", std::ios::out | std::ios::app);
		glorp << name << "\n";
		return name;
	}

	void play() {
	}

	char** GetMap() {
	
		return reinterpret_cast<char**>(map);
		
	}

	char** GetMapEnemy() {

		return reinterpret_cast<char**>(enemyMap);

	}
	//глянуть че там ниже ( не на часі ) 
	bool checkRules(int x1, int y1, int x2, int y2) {
		if (x1 > 9 || y1 > 9 || x2 > 9 || y2 > 9)
		{
			std::cout << "Выход за карту\n";
			return false;
		}
		int size;
		if (x1 != x2)
		{
			size = x1 - x2;
			if (size < 0)
			{
				size *= -1;
			}
			size++;

	
		}
		if (y1 != y2)
		{
			size = y1 - y2;
			if (size < 0)
			{
				size *= -1;
			}
			size++;
			
		}
		if (y1 == y2 && x1 == x2)
			{
				size = 1;
			}
		if (size > 4)
		{
			std::cout << "Неверные размеры корабля\n";
			return false;
		}
		if (listOfShip.size() == 0)
		{
			return true;
		}
		int calculation = 0;
		for (auto Ship : listOfShip)
		{
			if (Ship->size == size)
			{
				calculation++;
			}
		}
		
			switch (size)
			{
			case 1: if (calculation >= 4) { std::cout << "Неправильное количество кораблей " << size << " " << calculation << "\n"; return false; }		break;	
			case 2: if (calculation >= 3) { std::cout << "Неправильное количество кораблей " << size << " " << calculation << "\n"; return false; }		break;
			case 3: if (calculation >= 2) { std::cout << "Неправильное количество кораблей " << size << " " << calculation << "\n"; return false; }		break;
			case 4: if (calculation >= 1) { std::cout << "Неправильное количество кораблей " << size << " " << calculation << "\n"; return false; } 	break;
				
			default:
				break;
			}

			for (auto Ship : listOfShip)
			{
				int fx1, fy1, fx2, fy2;
				fx1 = Ship->x1 - 1;
				fy1 = Ship->y1 - 1;
				fx2 = Ship->x2 + 1;
				fy2 = Ship->y2 + 1;

				if (fx1 < 0) fx1 = 0;
				if (fy1 < 0) fy1 = 0;

				if (fx2 > 9) fx2 = 9;
				if (fy2 > 9) fy2 = 9;

				for (int i = fy1; i <= fy2; i++)
				{
					for (int a = fx1; a <= fx2; a++)
					{
						if ((a == x1 && i == y1) || (a == x2 && i == y2))
						{
							std::cout << "Колизия при раставлении кораблей по координате \n X:  "  << i << " Y:  " << a << "\n x1: " << x1 << " y1: " << y1 << "\n x2: "  << x2 << " y2: "  << y2 << "\n";
							return false;
						}
					}
				}
			}
			return true;
	}



	void acceptSendShips() {
		
		if (IsServ)
		{
			while ("finish" == net.sendClient("finish")){}

			for (auto pair: listOfShip)
			{
				std::string temp;
				std::to_string(pair->x1);
				temp = std::to_string(pair->x1);
				temp += std::to_string(pair->y1);
				temp += std::to_string(pair->x2);
				temp += std::to_string(pair->y2);
				

				net.sendClient(temp);
			}

			net.sendClient("end");

			std::string temp = net.sendClient(" ");
			while (temp != "end")
			{
				dispersalOfShips(temp[0] - 48, temp[1] - 48, temp[2] - 48, temp[3] - 48, false);
				temp = net.sendClient(" ");

			}
			std::cout << "SERVER END\n";

		
			temp = net.sendClient(" ");
		

		}
		else 
		{
			while ("finish" != net.sendToServer("finish")){}
			 
			std::string temp = net.sendToServer(" ");
			while (temp != "end")
			{

				dispersalOfShips(temp[0]-48, temp[1]-48, temp[2]-48, temp[3]-48, false);
				temp = net.sendToServer(" ");
			}

				for (auto pair : listOfShip)
				{
					std::string temp;
					std::to_string(pair->x1);
					temp = std::to_string(pair->x1);
					temp += std::to_string(pair->y1);
					temp += std::to_string(pair->x2);
					temp += std::to_string(pair->y2);


					net.sendToServer(temp);
				}
				std::cout << "CLIENT END\n";

			

				net.sendToServer("end");
		}


	}

	void dispersalOfShips(int x1, int y1, int x2, int y2, bool temp = true) {
		
		if (x1 == x2)	
		{
			for (size_t i = y1; i <= y2; i++)
			{
				if (temp)
				{
					map[x1][i] = SHIP;
				}
			/*	else {
					enemyMap[x1][i] = '#';
				}*/

			}

		}
		else if (y1 == y2) {
			for (size_t i = x1; i <= x2; i++)
			{
			
				if (temp)
				{
					map[x1][i] = SHIP;
				}
				/*else {
					enemyMap[x1][i] = '#';
				}*/
			}
		}
		else
		{

			std::cout << "Неверные координаты\n";
			return;
		}
		int size = 1;
		if (x1 != x2)
		{
			size = x1 - x2;
			if (size < 0)
			{
				size *= -1;
			}
			size++;


		}
		if (y1 != y2)
		{
			size = y1 - y2;
			if (size < 0)
			{
				size *= -1;
			}
			size++;

		}
		if (temp)
		{
			ship = new Ships(x1, x2, y1, y2, size);
			amountShip++;
			listOfShip.push_back(ship);
		}
		else {
			ship = new Ships(x1, x2, y1, y2, size);
			amountShipEnemy++;
			listOfShipEnemy.push_back(ship);
		}

	}

	bool StartGameOline(bool selectMode) {
		

		std::string ip;
		if (selectMode)
		{
			IsServ = true;
			net.createServer();
			net.listenSocket();
			WhoMove = true;
		}
		else {
			IsServ = false;
			std::cout << "введите порт сервера\n";
			int port;
			std::cin >> port >> ip;
			net.connectServer(port,ip);
			WhoMove = false;
		}

		return false;
	}

	std::list< std::string > getHistoryBattle(const std::string& filename) {

		std::ifstream file(filename);
		std::string line;
		std::list<std::string> myList;
		if (file.is_open()) {
			while (std::getline(file, line)) {
				myList.push_back(line);
			}
			file.close();
		}
		return myList;
	}

	
};



