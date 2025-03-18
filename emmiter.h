#pragma once

#include "particle.h"

class emmiter
{
	static const int PARTICLES_PER_EMMITER = 64;
public:
	void init(int x, int y);
	void update(void);
	void render(void);

	void move(vec2& delta);

	inline void setEnabled(bool enabled)
	{
		_enabled = enabled;
	}

private:
	particle particles[PARTICLES_PER_EMMITER];
	bool _enabled;
};

