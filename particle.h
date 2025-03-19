#pragma once
#include <cstdint>
#include <vec2.h>
#include <vec4.h>
class particle
{
public:
	void init(int x, int y);
	void update(void);
	void render(void);
	void move(vec2& delta);
	void hide(void);

	inline vec2 get_position(void)
	{
		return _position;
	}

	inline bool get_is_visible(void)
	{
		return _isVisible;
	}

private:
	vec2 _position;
	vec2 _movingVector;
	vec2 _initialMoveVector;
	vec4 _color;
	bool _isVisible;
};