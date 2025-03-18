
#include <thread>
#include <mutex>
#include <atomic>

#include "./nvToolsExt.h"

#include "test.h"


// Just some hints on implementation
// You could remove all of them

static std::atomic_int globalTime;
static std::atomic_bool workerMustExit = false;


// some code

void WorkerThread(void)
{
	while (!workerMustExit)
	{
		nvtxRangePush(__FUNCTION__);

		static int lastTime = 0;
		const int time = globalTime.load();
		const int delta = time - lastTime;
		lastTime = time;

		printf("delta %d\n", delta);
		if (delta > 0)
		{
			for (uint16_t emmiterIndex = 0; emmiterIndex < test::MAX_EMMITERS_COUNT; emmiterIndex++)
			{
				test::emmiters[emmiterIndex].update();
			}

			vec2& gravity = test::physic.getGravity();

			for (uint16_t emmiterIndex = 0; emmiterIndex < test::MAX_EMMITERS_COUNT; emmiterIndex++)
			{
				test::emmiters[emmiterIndex].move(gravity);
			}
			// some code
		}

		static const int MIN_UPDATE_PERIOD_MS = 1;
		if (delta < MIN_UPDATE_PERIOD_MS)
			std::this_thread::sleep_for(std::chrono::milliseconds(MIN_UPDATE_PERIOD_MS - delta));

		nvtxRangePop();
	}
}


void test::init(void)
{
	// some code

	std::thread workerThread(WorkerThread);
	workerThread.detach(); // Glut + MSVC = join hangs in atexit()
	for (size_t emmiterIndex = 0; emmiterIndex < MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].init(0, 0);
	}
	physic.init(-.9f);

	// some code
}

void test::term(void)
{
	// some code

	workerMustExit = true;

	// some code
}

void test::render(void)
{
	// some code

	for (uint16_t emmiterIndex = 0; emmiterIndex < MAX_EMMITERS_COUNT; emmiterIndex++)
	{
		emmiters[emmiterIndex].render();
	}
	// some code
}

void test::update(int dt)
{
	// some code

	globalTime.fetch_add(dt);


	// some code
}

void test::on_click(int x, int y)
{
	// some code

	static int _currentemmiterIndex = -1;
	_currentemmiterIndex++;
	emmiters[_currentemmiterIndex].setEnabled(true);
	emmiters[_currentemmiterIndex].init(x, SCREEN_HEIGHT - y);
}

bool test::is_outside_screen(int x, int y)
{
	if (x > SCREEN_WIDTH / 2)
	{
		return true;
	}

	if (y > SCREEN_HEIGHT / 2)
	{
		return true;
	}

	if (x < (-SCREEN_WIDTH) / 2)
	{
		return true;
	}

	if (y > (-SCREEN_HEIGHT) / 2)
	{
		return true;
	}
}
