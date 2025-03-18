#pragma once
#include "emmiter.h"
#include "physics.h"

namespace test
{
	const float SCREEN_WIDTH = 1024;
	const float SCREEN_HEIGHT = 768;
	const int16_t MAX_EMMITERS_COUNT = 2048;

	void render(void); // Only platform::drawPoint should be used
	void update(int dt); // dt in milliseconds
	void on_click(int x, int y); // x, y - in pixels

	bool is_outside_screen(int x, int y);

	void init(void);
	void term(void);
	static emmiter emmiters[2048];
	static physics physic;
};