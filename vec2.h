#pragma once
struct vec2
{
	float x;
	float y;

	void add(vec2& otherVec) 
	{
		x += otherVec.x;
		y += otherVec.y;
	}
};
