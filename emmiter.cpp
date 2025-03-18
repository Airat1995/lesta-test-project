#include "emmiter.h"

void emmiter::init(int x, int y)
{
	for (uint16_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		particles[particleIndex].init(x, y);
	}
}

void emmiter::update(void)
{
	if (!_enabled)
	{
		return;
	}

	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		particles[particleIndex].update();
	}
}

void emmiter::render(void)
{
	if (!_enabled)
	{
		return;
	}

	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		particles[particleIndex].render();
	}
}

void emmiter::move(vec2& delta)
{
	if (!_enabled)
	{
		return;
	}

	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		particles[particleIndex].move(delta);
	}
}
