#pragma once
#include <atomic>
#include <vector>
#include "BitBoard.h"

using namespace std;

class GameState
{
public:
	atomic<bool> run;
	atomic<bool> idle;
	atomic<bool> completedSearch;
	BitBoard * board;
	vector<u32> principalVariation;
	bool color = true;
	int maxDepth = 9;
	double maxTime;
	GameState();
	~GameState();
};
