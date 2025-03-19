#pragma once

#include "particle.h"

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

	void init(int x, int y, float lifeTime);
	void stop(void);
	void update(float dt);
	void render(void);

	void move(vec2& delta);
	bool can_spawn_new(void);

	inline emmiter_state get_state(void)
	{
		return _state;
	}

	vec2 get_active_rand_position(void);
private:
	particle _particles[PARTICLES_PER_EMMITER];
	emmiter_state _state;
	float _lifeTime;
};

