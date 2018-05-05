#include "stdafx.h"
#include "Engines.h"

using namespace std;

const bool DEBUG_OUTPUT = true;
const u32 THRD_CNT = 2;

Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::SearchThreaded(GameState & gameState, mutex beforeWork, atomic<u8>* depth, atomic<u8>* update)
{
}

void Engine::Killer(bool * killer, double time, atomic<bool> *change)
{
	double start = clock();
	while (((double)clock() - start) < time * CLOCKS_PER_SEC && *change)
	{
		this_thread::sleep_for(chrono::milliseconds(5));
	}
	if (*change)
		*killer = false;
}

vector<u32> Engine::search(GameState &gameState)
{
	//Standard search
	gameState.UpdateGeneration();
	u8 generation = gameState.fetchGeneration();

	//Variables used for debugging
	clock_t start = clock();

	ABAI search;
	search.resetNodes();
	int score = search.search(gameState.maxDepth, generation, gameState.tt, gameState.board, gameState.color);

	u32 pV[100];

	vector<u32> PV;

	cout << endl;

	clock_t end = clock();

	cout << "info depth " << to_string(gameState.maxDepth) << " score cp " << to_string(score) << " pv ";
	//Extract PV
	int maxDepth = 0;
	for (size_t i = 0; i < gameState.maxDepth; i++)
	{
		UnpackedHashEntry potEntry(0, 0, 0, 0, 0, 0);
		if (!gameState.tt->getFromTT(gameState.board->zoobristKey, &potEntry))
		{
			cout << "ERROR! Non-PV Node: " << endl;
		}
		maxDepth++;
		pV[i] = potEntry.bestMove;
		PV.push_back(pV[i]);
		cout << IO::convertMoveToAlg(pV[i]) << " ";
		gameState.board->MakeMove(pV[i]);
	}
	//Unmake pV
	for (size_t i = 1; i < maxDepth + 1; i++)
	{
		gameState.board->UnMakeMove(pV[gameState.maxDepth - i]);
	}
	cout << endl;


	if (DEBUG_OUTPUT)
	{
		cout << endl << "Score: " << to_string(score) << " at depth " << to_string(gameState.maxDepth) << endl;
		cout << to_string(search.nodes[0]) << " nodes in " << to_string((((end - start) / double CLOCKS_PER_SEC))) << " s [" <<
			to_string(search.nodes[0] / (((end - start) / double CLOCKS_PER_SEC) * 1000000)) << " Mpos/sec]" << endl;
		cout << "Branching factor: " << pow(search.nodes[0], (float)1 / (float)gameState.maxDepth) << endl;

		cout << "Branching factors: ";
		for (size_t i = 0; i < gameState.maxDepth - 1; i++)
		{
			cout << endl << to_string(search.nodes[i]) << " / " << to_string(search.nodes[i + 1]) << " = ";
			cout << to_string(gameState.maxDepth - i) << "/" << to_string(gameState.maxDepth - i - 1) << ": " << to_string((float)search.nodes[i] / (float)search.nodes[i + 1])
				<< ", ";
		}
		cout << endl;
	}

	//Memory cleanup

	return PV;
}

vector<u32> Engine::searchID(GameState &gameState)
{
	//Standard search
	gameState.UpdateGeneration();
	u8 generation = gameState.fetchGeneration();

	vector<u32> PV;

	ABAI search;
	search.resetNodes();

	//Variables used for debugging
	clock_t start = clock();

	int score;

	u32 pV[100];

	cout << endl;
	int alpha = -8192;
	int beta = 8192;
	for (int i = 1; i < gameState.maxDepth + 1; i++)
	{
		//Do search
		int highestFound = 0;
		score = search.search(i, generation, gameState.tt, gameState.board, gameState.color);
		cout << "info depth " << to_string(i) << " score cp " << to_string(score) << " pv ";
		for (size_t i2 = 0; i2 < i; i2++)
		{
			UnpackedHashEntry potEntry(0, 0, 0, 0, 0, 0);
			if (!gameState.tt->getFromTT(gameState.board->zoobristKey, &potEntry))
			{
				cout << "ERROR! Non-PV Node: " << endl;
				break;
			}
			highestFound = i2;
			pV[i2] = potEntry.bestMove;
			if (i == gameState.maxDepth)
			{
				PV.push_back(pV[i2]);
			}
			cout << IO::convertMoveToAlg(pV[i2]) << " ";
			gameState.board->MakeMove(pV[i2]);
		}
		//Unmake pV
		for (int i2 = highestFound; i2 >= 0; i2 -= 1)
		{
			gameState.board->UnMakeMove(pV[i2]);
		}
		cout << endl;
	}
	clock_t end = clock();

	if (DEBUG_OUTPUT)
	{
		cout << endl << "Score: " << to_string(score) << " at depth " << to_string(gameState.maxDepth) << endl;
		cout << to_string(search.nodes[0]) << " nodes in " << to_string((((end - start) / double CLOCKS_PER_SEC))) << " s [" <<
			to_string(search.nodes[0] / (((end - start) / double CLOCKS_PER_SEC) * 1000000)) << " Mpos/sec]" << endl;
		cout << "Branching factor: " << pow(search.nodes[0], (float)1 / (float)gameState.maxDepth) << endl;

		cout << "Branching factors: ";
		for (size_t i = 0; i < gameState.maxDepth - 1; i++)
		{
			cout << endl << to_string(search.nodes[i]) << " / " << to_string(search.nodes[i + 1]) << " = ";
			cout << to_string(gameState.maxDepth - i) << "/" << to_string(gameState.maxDepth - i - 1) << ": " << to_string((float)search.nodes[i] / (float)search.nodes[i + 1])
				<< ", ";
		}
	}

	cout << endl;

	return PV;
}

vector<u32> Engine::searchIDSimpleTime(GameState &gameState)
{
	//Standard search
	//gameState.tt->resetTT();

	gameState.UpdateGeneration();
	u8 generation = gameState.fetchGeneration();
	atomic<bool> *change = new atomic<bool>;
	*change = true;
	//Create the static array used for storing legal moves
	vector<u32> PV;

	ABAI search;
	bool *killer = search.cont;
	thread thrd(Engine::Killer, killer, gameState.maxTime, change);
	//Reset the debug node counter
	search.resetNodes();

	//Variables used for debugging
	clock_t start = clock();

	int score;

	u32 pV[100];

	cout << endl;

	double totalTime;
	double branchingFactor;
	const int maxTime = 20;
	bool runSearch = true;
	cout << endl;
	int i = 1;
	int highestDepth;
	while (runSearch && *killer)
	{
		//Do search
		search.resetNodes();
		PV.clear();
		clock_t bSearch = clock();
		score = search.search(i, generation, gameState.tt, gameState.board, gameState.color);
		clock_t timerEnd = clock();
		totalTime = (timerEnd - start) / double CLOCKS_PER_SEC;
		clock_t thisSearch = timerEnd - bSearch;
		branchingFactor = pow(search.nodes[0], 1 / (double)i);
		if (search.nodes[2] != 0)
		{
			if (thisSearch * 2 + totalTime * CLOCKS_PER_SEC > gameState.maxTime * CLOCKS_PER_SEC)
			{
				runSearch = false;
				cout << "Time data: Taken Time " << to_string(thisSearch) << " Ratio searched " << to_string((double)search.nodes[1] / (double)search.nodes[2]) << " expected next time " << to_string(totalTime * search.nodes[1] / (double)search.nodes[2]) << endl;
			}
		
		}
		//Information generation
		cout << "info depth " << to_string(i) << " score cp " << to_string(score) << " pv ";
		//Find pV
		int highestDepth = 0;
		if (*killer)
		{
			for (size_t i2 = 0; i2 < i; i2++)
			{
				UnpackedHashEntry potEntry(0, 0, 0, 0, 0, 0);
				if (!gameState.tt->getFromTT(gameState.board->zoobristKey, &potEntry))
				{
					cout << "ERROR! Non-PV Node: " << endl;
					break;
				}
				highestDepth = i2;
				pV[i2] = potEntry.bestMove;
				PV.push_back(pV[i2]);
				cout << IO::convertMoveToAlg(pV[i2]) << " ";
				gameState.board->MakeMove(pV[i2]);
			}
			//Unmake pV
			for (int i2 = highestDepth; i2 >= 0; i2 -= 1)
			{
				gameState.board->UnMakeMove(pV[i2]);
			}
		}
		cout << endl;
		i++;
	}
	*change = false;
	if (!*killer)
		i--;
	i--;
	thrd.join();
	highestDepth = 0;
	for (size_t i2 = 0; i2 < i; i2++)
	{
		UnpackedHashEntry potEntry(0, 0, 0, 0, 0, 0);
		if (!gameState.tt->getFromTT(gameState.board->zoobristKey, &potEntry))
		{
			cout << "ERROR! Non-PV Node: " << endl;
			break;
		}
		highestDepth = i2;
		pV[i2] = potEntry.bestMove;
		PV.push_back(pV[i2]);
		gameState.board->MakeMove(pV[i2]);
	}
	//Unmake pV
	for (int i2 = highestDepth; i2 >= 0; i2--)
	{
		gameState.board->UnMakeMove(pV[i2]);
	}
	int maxDepth = i;

	clock_t end = clock();

	if (DEBUG_OUTPUT)
	{
		cout << endl << "Score: " << to_string(score) << " at depth " << to_string(maxDepth) << endl;
		cout << to_string(search.nodes[0]) << " search.nodes in " << to_string((((end - start) / double CLOCKS_PER_SEC))) << " s [" <<
			to_string(search.nodes[0] / (((end - start) / double CLOCKS_PER_SEC) * 1000000)) << " Mpos/sec]" << endl;
		cout << "Branching factor: " << pow(search.nodes[0], (float)1 / (float)maxDepth) << endl;

		cout << "Branching factors: ";
		for (size_t i = 0; i < maxDepth - 1; i++)
		{
			cout << endl << to_string(search.nodes[i]) << " / " << to_string(search.nodes[i + 1]) << " = ";
			cout << to_string(maxDepth - i) << "/" << to_string(maxDepth - i - 1) << ": " << to_string((float)search.nodes[i] / (float)search.nodes[i + 1])
				<< ", ";
		}
	}
	cout << endl;
	return PV;
}

vector<u32> Engine::multiThreadedSearch(GameState & gameState)
{
	return vector<u32>();
}
