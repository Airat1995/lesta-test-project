#pragma once
#include <vec2.h>
class physics
{
public:
	void init(float gravity);

	inline vec2& getGravity()
	{
		return _gravity;
	}

private:
	vec2 _gravity;
};

