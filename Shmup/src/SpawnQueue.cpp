#include "SpawnQueue.h"

SpawnEntry::SpawnEntry(int id, float x, float y, float delay)
{
	_ID = id;
	_X = x;
	_Y = y;
	_Delay = delay;
};

SpawnQueue::SpawnQueue(std::string filename)
{
	if (filename != "")
		Load(filename);
	_Timer = 0.f;
};

SpawnEntry SpawnQueue::PeekFront()
{
	return _SpawnSequence.front();
};
SpawnEntry SpawnQueue::PopFront()
{
	SpawnEntry temp = _SpawnSequence.front();
	_SpawnSequence.pop();
	_Timer = 0.f;
	return temp;
};
void SpawnQueue::AddBack(SpawnEntry entry)
{
	_SpawnSequence.push(entry);
};

float SpawnQueue::GetTime()
{
	return _Timer;
};
void SpawnQueue::AddTime(float dt)
{
	_Timer += dt;
};

void SpawnQueue::Load(std::string filename)
{
	BinaryFile f(filename, IO_IN);

	if (!f.IsOpen())
		return;

	int numEntries = f.Read<int>();

	for (int i = 0; i < numEntries; i++)
	{
		SpawnEntry entry;
		entry._ID = f.Read<int>();
		entry._X = f.Read<float>();
		entry._Y = f.Read<float>();
		entry._Delay = f.Read<float>();

		AddBack(entry);
	}

	f.Close();
};
void SpawnQueue::Save(std::string filename)
{
	BinaryFile f(filename, IO_OUT, true);

	if (!f.IsOpen())
		return;

	int numEntries = CountEntries();
	f.Write<int>(numEntries);

	for (int i = 0; i < numEntries; i++)
	{
		SpawnEntry entry = PopFront();
		f.Write<int>(entry._ID);
		f.Write<float>(entry._X);
		f.Write<float>(entry._Y);
		f.Write<float>(entry._Delay);

		AddBack(entry);
	}
	
	f.Close();
};

int SpawnQueue::CountEntries()
{
	return (int)_SpawnSequence.size();
};


//	Test Function: generate a spawn queue

void GenSpawnQueue(SpawnQueue* sq)
{
	sq->AddBack(SpawnEntry(EntFactory::BombEnemy, 100.f, -100.f, 3.f));
	sq->AddBack(SpawnEntry(EntFactory::BombEnemy, 200.f, -100.f, 0.f));
	sq->AddBack(SpawnEntry(EntFactory::BombEnemy, 300.f, -100.f, 0.f));
	sq->AddBack(SpawnEntry(EntFactory::BombEnemy, 400.f, -100.f, 0.f));
	sq->AddBack(SpawnEntry(EntFactory::BombEnemy, 500.f, -100.f, 0.f));

	sq->AddBack(SpawnEntry(EntFactory::SpreaderEnemy, 300.f, -100.f, 3.f));
	sq->AddBack(SpawnEntry(EntFactory::DroneEnemy, 100.f, -100.f, 0.f));
	sq->AddBack(SpawnEntry(EntFactory::DroneEnemy, 500.f, -100.f, 0.f));

	sq->AddBack(SpawnEntry(EntFactory::SwarmEnemy, 100.f, -100.f, 3.f));
	sq->AddBack(SpawnEntry(EntFactory::TankEnemy, 300.f, -100.f, 0.f));
	sq->AddBack(SpawnEntry(EntFactory::SwarmEnemy, 500.f, -100.f, 0.f));

	sq->AddBack(SpawnEntry(EntFactory::SwarmEnemy, 100.f, -100.f, 3.f));
	sq->AddBack(SpawnEntry(EntFactory::SwarmEnemy, 200.f, -100.f, 0.25f));
	sq->AddBack(SpawnEntry(EntFactory::SwarmEnemy, 300.f, -100.f, 0.25f));
	sq->AddBack(SpawnEntry(EntFactory::SwarmEnemy, 400.f, -100.f, 0.25f));
	sq->AddBack(SpawnEntry(EntFactory::SwarmEnemy, 500.f, -100.f, 0.25f));

	sq->AddBack(SpawnEntry(EntFactory::DroneEnemy, 100.f, -100.f, 2.f));
	sq->AddBack(SpawnEntry(EntFactory::DroneEnemy, 500.f, -100.f, 0.f));

	sq->AddBack(SpawnEntry(EntFactory::DroneEnemy, 200.f, -100.f, 1.f));
	sq->AddBack(SpawnEntry(EntFactory::DroneEnemy, 400.f, -100.f, 0.f));

	sq->AddBack(SpawnEntry(EntFactory::DroneEnemy, 300.f, -100.f, 1.f));

};