#include "particle.h"
#include "platform.h"
#include "test.h"
#include <stdlib.h>

void particle::init(int x, int y)
{
	_isVisible = true;
	_color.x = ((float)rand()) / RAND_MAX;
	_color.y = ((float)rand()) / RAND_MAX;
	_color.z = ((float)rand()) / RAND_MAX;
	_color.w = 1.0f;

	_velocityVector.x = 0;
	_velocityVector.y = 0;
	_transform.current.x = x;
	_transform.current.y = y;

	_transform.previous.x = x;
	_transform.previous.y = y;
}

void particle::fixed_update(int globalTime, int dt)
{
	if (!_isVisible)
	{
		return;
	}

	_transform.previous.x = _transform.current.x;
	_transform.previous.y = _transform.current.y;
	
	_transform.current.x = _transform.current.x + _velocityVector.x * dt;
	_transform.current.y = _transform.current.y + _velocityVector.y * dt;
	
	_isVisible = !test::is_outside_screen(_transform.current.x, _transform.current.y);
}

void particle::render(double alpha)
{
	if (!_isVisible)
	{
		return;
	}

	int drawPosX = _transform.previous.x + (_transform.current.x - _transform.previous.x) * alpha;
	int drawPosY = _transform.previous.y + (_transform.current.y - _transform.previous.y) * alpha;

	platform::drawPoint(drawPosX, test::SCREEN_HEIGHT - drawPosY, _color.x, _color.y, _color.z, _color.w);
}

void particle::add_velocity(vec2& delta)
{
	_velocityVector.x += delta.x;
	_velocityVector.y += delta.y;
}

void particle::hide(void)
{
	_isVisible = false;
}
