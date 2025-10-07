#pragma once

#include "Factory.h"
#include <queue>
#include "core/BinaryFile.h"

struct SpawnEntry
{
	SpawnEntry(int id = 0, float x = 0.f, float y = 0.f, float delay = 0.f);

	int _ID;
	float _Delay;
	float _X;
	float _Y;
};

class SpawnQueue
{
public:

	SpawnQueue(std::string filename = "");

	SpawnEntry PeekFront();
	SpawnEntry PopFront();
	void AddBack(SpawnEntry entry);

	void Load(std::string filename);
	void Save(std::string filename);

	float GetTime();
	void AddTime(float dt);

	int CountEntries();

private:

	float _Timer;
	std::queue<SpawnEntry> _SpawnSequence;
};


void GenSpawnQueue(SpawnQueue* sq);