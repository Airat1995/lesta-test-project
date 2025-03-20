
#include <thread>
#include <mutex>
#include <atomic>

#include "./nvToolsExt.h"

#include "test.h"


// Just some hints on implementation
// You could remove all of them

static std::atomic_int accumulator;
static std::atomic_int globalTime;
static std::atomic_int _currentemmiterIndex;
static std::atomic_bool workerMustExit = false;

emmiter* emmiters;
physics* physic;

void WorkerThread(void)
{
	vec2& gravityValue = physic->getGravity();
	while (!workerMustExit)
	{
		nvtxRangePush(__FUNCTION__);

		static int lastTime = 0;
		const int time = globalTime.load();
		const int delta = time - lastTime;
		lastTime = time;

		while (accumulator >= test::PHYSICS_FRAME_TIME)
		{
			if (workerMustExit)
			{
				return;
			}
			for (uint16_t emmiterIndex = 0; emmiterIndex < test::MAX_EMMITERS_COUNT; emmiterIndex++)
			{
				emmiters[emmiterIndex].add_velocity(gravityValue);
				emmiters[emmiterIndex].fixed_update(time, test::PHYSICS_FRAME_TIME);
			}
			accumulator.fetch_sub(test::PHYSICS_FRAME_TIME);
		}

		nvtxRangePop();
	}
}

void test::init(void)
{
	physic = new physics();
	emmiters = new emmiter[test::MAX_EMMITERS_COUNT];
	_currentemmiterIndex.store(-1);
	accumulator.store(0);
	physic->init(GRAVITY_FORCE);
	std::thread workerThread(WorkerThread);
	workerThread.detach();
}

void test::term(void)
{
	workerMustExit = true;
	for (uint16_t emmiterIndex = 0; emmiterIndex < MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].stop();
	}
	delete[] emmiters;
	delete physic;
}

void test::render(void)
{
	double alpha = accumulator.load() / ((double)PHYSICS_FRAME_TIME);
	for (uint16_t emmiterIndex = 0; emmiterIndex < MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].render(alpha);
	}
}

void test::update(int dt)
{
	accumulator.fetch_add(dt);
	globalTime.fetch_add(dt);

	for (uint16_t emmiterIndex = 0; emmiterIndex < test::MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].update(dt);
		if (emmiters[emmiterIndex].get_state() == emmiter_state::finished)
		{
			bool shouldSpawn = test::rand_chance_to_spawn();
			bool canGetSpawnPoint = emmiters[emmiterIndex].can_spawn_new();

			if (shouldSpawn && canGetSpawnPoint)
			{
				vec2 point = emmiters[emmiterIndex].get_active_rand_position();
				test::emmit(point.x, point.y);
			}
		}
	}
}

void test::on_click(int x, int y)
{
	emmit(x, y);
}

void test::emmit(int x, int y)
{
	_currentemmiterIndex.fetch_add(1);
	if (_currentemmiterIndex >= MAX_EMMITERS_COUNT)
	{
		_currentemmiterIndex = 0;
	}
	int busyEmmitersCount = 0;
	while (emmiters[_currentemmiterIndex].get_state() != emmiter_state::idle)
	{
		//all emmiters are busy just skip emit
		//shouldn't happen in normal situations unless player pause the window by dragging it
		busyEmmitersCount++;
		if (busyEmmitersCount >= MAX_EMMITERS_COUNT)
		{
			return;
		}
		_currentemmiterIndex.fetch_add(1);
		if (_currentemmiterIndex >= MAX_EMMITERS_COUNT)
		{
			_currentemmiterIndex = 0;
		}
	}
	emmiters[_currentemmiterIndex].init(x, y, PARTICLE_LIFE_TIME, PARTICLE_MIN_INITIAL_SPEED, PARTICLE_MAX_INITIAL_SPEED);
}

bool test::is_outside_screen(int x, int y)
{
	if (x > SCREEN_WIDTH)
	{
		return true;
	}

	if (y > SCREEN_HEIGHT)
	{
		return true;
	}

	if (x < 0)
	{
		return true;
	}

	if (y < 0)
	{
		return true;
	}

	return false;
}

bool test::rand_chance_to_spawn(void)
{
	return rand() % 100 < CHANCE_TO_SPAWN;
}
