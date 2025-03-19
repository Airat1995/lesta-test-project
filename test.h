#pragma once
#include "emmiter.h"
#include "physics.h"

namespace test
{
	const float SCREEN_WIDTH = 1024;
	const float SCREEN_HEIGHT = 768;
	const int16_t MAX_EMMITERS_COUNT = 2048;
	const uint8_t CHANCE_TO_SPAWN = 100; // from 0 - to never to 100 - always
	const uint16_t PARTICLE_LIFE_TIME = 2000; //in ms
	const float GRAVITY_FORCE = -.9f;

	void render(void); // Only platform::drawPoint should be used
	void update(int dt); // dt in milliseconds
	void on_click(int x, int y); // x, y - in pixels

	void emmit(int x, int y);

	bool is_outside_screen(int x, int y);
	bool rand_bool(void);

	void init(void);
	void term(void);
};