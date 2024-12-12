#pragma once

#include <vector>

struct Vector2;

enum class Direction
{
	up,
	down,
	right,
	left,
};

class WordArrangementer
{
public:
	WordArrangementer(int value1 = 3, int value2 = 4, int value3 = 5);
	~WordArrangementer();

private:
	void Arrangement();
	std::vector<Direction> AdjacentCheck(int width, int height);
	std::vector<Vector2> CheckSpace(int width, int height);

	// ï∂éöêî
	std::vector<int> charValues;

	int value1 = 0;
	int value2 = 0;
	int value3 = 0;

};