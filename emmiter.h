#pragma once

#include "particle.h"
#include <cstdlib>

enum class emmiter_state : uint8_t 
{
	idle,
	running,
	finished
};

class emmiter
{
	static const int PARTICLES_PER_EMMITER = 64;
public:

	void init(int x, int y, int lifeTime, float minInitialSpeed, float maxInitialSpeed);
	void stop(void);
	void update(int dt);
	void fixed_update(int time, int dt);
	void render(double alpha);

	void add_velocity(vec2& delta);
	bool can_spawn_new(void);

	inline emmiter_state get_state(void)
	{
		return _state;
	}

	vec2 get_active_rand_position(void);
private:
	particle _particles[PARTICLES_PER_EMMITER];
	emmiter_state _state = emmiter_state::idle;
	int _lifeTime;

	float randomFloat(float min, float max) {
		return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	}
};

