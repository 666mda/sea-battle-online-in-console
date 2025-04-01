#pragma once
#include"mainInclude.h"
#include "MainLogics.h"
class UnitTest
{
	//реализовать растанновку для вражеских кораблей

public:

	void FellMap(MainLogics*testUnit) {
		testUnit->dispersalOfShips(0, 0, 0, 0);
		testUnit->dispersalOfShips(9, 0, 9, 0);
		testUnit->dispersalOfShips(0, 9, 0, 9);
		testUnit->dispersalOfShips(9, 9, 9, 9);
		testUnit->dispersalOfShips(4, 4, 4, 7);
		testUnit->dispersalOfShips(6, 6, 6, 8);
		testUnit->dispersalOfShips(8, 3, 8, 4);
		testUnit->dispersalOfShips(0, 5, 0, 7);
		testUnit->dispersalOfShips(0, 2, 0, 3);
		testUnit->dispersalOfShips(2, 3, 2, 4);

		testUnit->test();
	}
	
};

