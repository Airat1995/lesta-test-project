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
	_color.w = ((float)rand()) / RAND_MAX;

	_position.x = x;
	_position.y = y;
	_initialMoveVector.x = rand() % 9 - 5;
	_initialMoveVector.y = rand() % 9 - 5;
}

void particle::update(void)
{
	if (!_isVisible)
	{
		return;
	}

	_position.x += _initialMoveVector.x + _movingVector.x;
	_position.y += _initialMoveVector.y + _movingVector.y;
	_movingVector.x = 0;
	_movingVector.y = 0;

	_isVisible = !test::is_outside_screen(_position.x, _position.y);
}

void particle::render(void)
{
	if (!_isVisible)
	{
		return;
	}

	platform::drawPoint(_position.x, _position.y, _color.x, _color.y, _color.z, _color.w);
}

void particle::move(vec2& delta)
{
	_movingVector.x += delta.x;
	_movingVector.y += delta.y;
}

void particle::hide(void)
{
	_isVisible = false;
}
