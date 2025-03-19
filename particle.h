#pragma once
#include <cstdint>
#include "vec2.h"
#include "vec4.h"
#include "state.h"

class particle
{
public:
	void init(int x, int y);
	void fixed_update(int time, int dt);
	void render(double alpha);
	void add_velocity(vec2& delta);
	void hide(void);

	inline vec2 get_position(void)
	{
		return _transform.current;
	}

	inline bool get_is_visible(void)
	{
		return _isVisible;
	}

private:
	state _transform;
	vec2 _velocityVector;
	vec2 _initialMoveVector;
	vec4 _color;
	bool _isVisible = false;
};