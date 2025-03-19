#include "emmiter.h"
#include <stdlib.h>

void emmiter::init(int x, int y, int lifeTime, float minInitialSpeed, float maxInitialSpeed)
{
	for (uint16_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		_particles[particleIndex].init(x, y);
		vec2 velocity;
		velocity.x = randomFloat(minInitialSpeed, maxInitialSpeed);
		velocity.y = randomFloat(minInitialSpeed, maxInitialSpeed);
		_particles[particleIndex].add_velocity(velocity);
	}
	_lifeTime = lifeTime;
	_state = emmiter_state::running;
}

void emmiter::stop(void)
{
	_state = emmiter_state::finished;
	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		_particles[particleIndex].hide();
	}
}

void emmiter::update(int dt)
{
	if (_state == emmiter_state::idle)
	{
		return;
	}

	if (_state == emmiter_state::finished)
	{
		_state = emmiter_state::idle;
		return;
	}
	_lifeTime -= dt;
	if (_lifeTime <= 0)
	{
		_state = emmiter_state::finished;
	}
}

void emmiter::fixed_update(int time, int dt)
{
	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		_particles[particleIndex].fixed_update(time, dt);
	}
}

void emmiter::render(double alpha)
{
	if (_state == emmiter_state::idle || _state == emmiter_state::finished)
	{
		return;
	}

	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		_particles[particleIndex].render(alpha);
	}
}

void emmiter::add_velocity(vec2& delta)
{
	if (_state == emmiter_state::idle || _state == emmiter_state::finished)
	{
		return;
	}

	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		_particles[particleIndex].add_velocity(delta);
	}
}

bool emmiter::can_spawn_new(void)
{
	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		if (_particles[particleIndex].get_is_visible())
		{
			return true;
		}
	}

	return false;
}

vec2 emmiter::get_active_rand_position(void)
{
	int visibleParticles[PARTICLES_PER_EMMITER];
	int currentVisibleIndex = 0;
	for (uint8_t particleIndex = 0; particleIndex < PARTICLES_PER_EMMITER; particleIndex++)
	{
		if (_particles[particleIndex].get_is_visible())
		{
			visibleParticles[currentVisibleIndex] = particleIndex;
			currentVisibleIndex++;
		}
	}
	int index = rand() % currentVisibleIndex;
	return _particles[visibleParticles[index]].get_position();
}
