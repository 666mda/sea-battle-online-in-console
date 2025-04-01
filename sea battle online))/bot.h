#pragma once
#include"mainInclude.h"
class Bot
{
	int complicationBot;

	point Easy(std::unordered_map<unsigned long int, move> History) {
		std::rand() % 10;
		point tempMove;
		bool temp = true;
		if (History.size() == 0)
		{
			tempMove.x = std::rand() % 10;
			tempMove.y = std::rand() % 10;
			return tempMove;
		}
		while (temp)
		{
			temp = false;
			tempMove.x = std::rand() % 10;
			tempMove.y = std::rand() % 10;
			for (auto pair : History) {
		
				if (pair.second.hope.x == tempMove.x && pair.second.hope.y == tempMove.y)
				{
					temp = true;
					break;
				}

			}


		}
		return tempMove;

	}
	point Medium(std::unordered_map<unsigned long int, move> History) {
	
		point tempMove;
		bool temp = true;
		unsigned long int max = 0;
		if (History.size() == 0)
		{
			tempMove.x = std::rand() % 10;
			tempMove.y = std::rand() % 10;
			return tempMove;
		}
	
		for (auto pair : History)
		{
			if (pair.first > max)
			{
				max = pair.first;
			}

		}
		move lastMove = History.find(max)->second;
		unsigned long int hope = 0;
		for (auto pair : History)
		{
			if (pair.second.IsHit && pair.first > hope)
			{
				hope = pair.first;
			}
		}

		if (hope == 0)
		{
			tempMove.x = std::rand() % 10;
			tempMove.y = std::rand() % 10;
			return tempMove;
		}

		auto lastShot = History.find(hope);
		bool temp1[4] = {0,0,0,0};
	
		auto tryShot = lastShot;
		++tryShot; // ѕропускаем первый элемент
		for (; tryShot != History.end(); ++tryShot)
		{
			//короче надо доделать,, перебрать направление попаданий 

			if (lastShot->second.hope.x == tryShot->second.hope.x +1    &&    lastShot->second.hope.y == tryShot->second.hope.y)
			{
				temp1[0] = 1;
			}




			if (lastShot->second.hope.x == tryShot->second.hope.x - 1     &&      lastShot->second.hope.y == tryShot->second.hope.y)
			{
				temp1[1] = 1;
			}





			if (lastShot->second.hope.y == tryShot->second.hope.y + 1    &&    lastShot->second.hope.x == tryShot->second.hope.x)
			{
				temp1[2] = 1;
			}




			if (lastShot->second.hope.y == tryShot->second.hope.y - 1     &&     lastShot->second.hope.x == tryShot->second.hope.x)
			{
				temp1[3] = 1;
			}

		
		}

		if (!temp1[0])
		{
			point pt;
			pt.x = lastShot->second.hope.x + 1;
			pt.y = lastShot->second.hope.y;
			return pt;
		}

		if (!temp1[1])
		{
			point pt;
			pt.x = lastShot->second.hope.x - 1;
			pt.y = lastShot->second.hope.y;
			return pt;
		}

		if (!temp1[2])
		{
			point pt;
			pt.x = lastShot->second.hope.x;
			pt.y = lastShot->second.hope.y + 1;
			return pt;
		} 
		
		if (!temp1[3])
		{
			point pt;
			pt.x = lastShot->second.hope.x;
			pt.y = lastShot->second.hope.y - 1;
			return pt;
		}
		tempMove.x = std::rand() % 10;
		tempMove.y = std::rand() % 10;
		return tempMove;

	}

	


	/*point Hard(std::unordered_map<unsigned long int, move> History) {}*/
public:

	Bot(int complicationBot) {
		this->complicationBot = complicationBot;
	

	}

	point MakeMove(std::unordered_map<unsigned long int, move> History) {
		switch (complicationBot)
		{
		case 1: return Easy(History); break;
		case 2: return Medium(History); break;
		//case 3: return Hard(History); break;
		default:
			break;
		}
	}

};

