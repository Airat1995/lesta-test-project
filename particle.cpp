#include "particle.h"
#include "platform.h"
#include <stdlib.h>

void particle::init(int x, int y)
{
	_color.x = rand() % 255;
	_color.y = rand() % 255;
	_color.z = rand() % 255;
	_color.w = rand() % 255;

	_position.x = x;
	_position.y = y;
	_initialMoveVector.x = rand() % 19 - 9;
	_initialMoveVector.y = rand() % 19 - 9;
}

void particle::update(void)
{
	_position.add(_initialMoveVector);
	_position.add(_movingVector);
	_movingVector.x = 0;
	_movingVector.y = 0;
}

void particle::render(void)
{
	platform::drawPoint(_position.x, _position.y, _color.x, _color.y, _color.z, _color.w);
}

void particle::move(vec2& delta)
{
	_movingVector.add(delta);
}
