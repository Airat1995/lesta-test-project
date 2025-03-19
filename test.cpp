
#include <thread>
#include <mutex>
#include <atomic>

#include "./nvToolsExt.h"

#include "test.h"


// Just some hints on implementation
// You could remove all of them

static std::atomic_int globalTime;
static std::atomic_int _currentemmiterIndex;
static std::atomic_bool workerMustExit = false;

emmiter* emmiters;
physics physic;

void test::init(void)
{
	emmiters = new emmiter[test::MAX_EMMITERS_COUNT];
	_currentemmiterIndex.store(-1);
	physic.init(GRAVITY_FORCE);
}

void test::term(void)
{
	workerMustExit = true;
	for (uint16_t emmiterIndex = 0; emmiterIndex < MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].stop();
	}
	delete[] emmiters;
}

void test::render(void)
{
	for (uint16_t emmiterIndex = 0; emmiterIndex < MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].render();
	}
}

void test::update(int dt)
{
	globalTime.fetch_add(dt);

	for (uint16_t emmiterIndex = 0; emmiterIndex < MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].update(dt);
		if (emmiters[emmiterIndex].get_state() == emmiter_state::finished && emmiters[emmiterIndex].can_spawn_new())
		{
			bool shouldSpawn = rand_bool();
			if (shouldSpawn)
			{
				vec2 point = emmiters[emmiterIndex].get_active_rand_position();
				emmit(point.x, point.y);
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
	emmiters[_currentemmiterIndex].init(x, SCREEN_HEIGHT - y, PARTICLE_LIFE_TIME);
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

bool test::rand_bool(void)
{
	return rand() % 100 < CHANCE_TO_SPAWN;
}
