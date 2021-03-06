#include "foeanimation.h"

FoeAnimation::FoeAnimation()
{
	type = -1;
	state = -1;
	offset = 0;
	FPS = 20.0f;

	x = y = 0;
	scale = 0;
	width = 0;
	left = right = 0;
}

FoeAnimation::~FoeAnimation()
{
	type = -1;
	state = -1;
	offset = 0;
	if (!lines.empty())
	{
		lines.clear();
		lines.shrink_to_fit();
	}
	FPS = 20.0f;

	x = y = 0;
	scale = 0;
	width = 0;
	left = right = 0;
}

void FoeAnimation::setSpriteType(int newType)
{
	type = newType;
}
/*
void FoeAnimation::setSpriteState(int newState)
{
	state = newState;
}

void FoeAnimation::setSpriteOffset(float newOffset)
{
	offset = newOffset;
}
*/
void FoeAnimation::setSpriteLines(std::vector<int> newLines)
{
	lines = newLines;
}

const int FoeAnimation::getSpriteType() const
{
	return type;
}

const int FoeAnimation::getSpriteState() const
{
	return state;
}

const int FoeAnimation::getSpriteOffset() const
{
	return static_cast<int>(offset);
}
/*
const std::vector<int> FoeAnimation::getSpriteLines() const
{
	return lines;
}
*/


void FoeAnimation::setScale(float newScale)
{
	scale = newScale;
}

void FoeAnimation::setWidth(float newWidth)
{
	width = newWidth;
}

void FoeAnimation::setPosition(float newX, float newY)
{
	x = newX;
	y = newY;
}

void FoeAnimation::setLeft(float newLeft)
{
	left = newLeft;
}

void FoeAnimation::setRight(float newRight)
{
	right = newRight;
}

const float& FoeAnimation::getScaleX() const
{
	return scale;
}

float FoeAnimation::getScaleY() const
{
	return scale < 0 ? -scale : scale;
}
/*
const float FoeAnimation::getWidth() const
{
	return width;
}
*/
const float FoeAnimation::getLeft() const
{
	return left;
}

const float FoeAnimation::getRight() const
{
	return right;
}

const float FoeAnimation::getTop() const
{
	return y;
}

const float FoeAnimation::getBot()
{
	return y + width * 2;
}