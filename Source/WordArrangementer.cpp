#include "WordArrangementer.h"

#include <stdlib.h>
#include <iostream>

#include "WordManager.h"
#include "Character.h"
#include "Vector2.h"

WordArrangementer::WordArrangementer(int value1, int value2, int value3)
	:value1(value1)
	, value2(value2)
	, value3(value3)
{
	srand(1752);

	charValues.push_back(value1);
	charValues.push_back(value2);
	charValues.push_back(value3);

	Arrangement();
}

WordArrangementer::~WordArrangementer()
{}

/**
* 配置
*/
void WordArrangementer::Arrangement()
{
	WordManager& wordManager = WordManager::Instance();

	int startX = rand() % wordManager.GetMaxWidth();
	int startY = rand() % wordManager.GetMaxHeight();

	int charValueNum = (rand() % charValues.size());
	// 文字数
	int charValue = charValues[charValueNum];

	// nullptrの場合配置されていないので配置できる
	if (!wordManager.GetCharacter(startX, startY))
	{
		std::vector<Vector2> canSettingPoint;

		while (charValues.size())
		{
			std::vector<Direction> dirs = AdjacentCheck(startX, startY);
			if (dirs.size() < charValue)
			{
				wordManager.ResetCharacters();
				charValues.clear();
				charValues.push_back(value1);
				charValues.push_back(value2);
				charValues.push_back(value3);
				charValueNum = (rand() % charValues.size());
				charValue = charValues[charValueNum];
			}
			for (int i = 0; i < charValue; ++i)
			{
				// 設置できる方向取得
				std::vector<Direction> directions = AdjacentCheck(startX, startY);
				for (Direction dir : directions)
				{
					switch (dir)
					{
					case Direction::up:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(startX, startY - 1);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(startX, startY - 1));
						}
						break;
					case Direction::down:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(startX, startY + 1);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(startX, startY + 1));
						}
						break;
					case Direction::right:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(startX + 1, startY);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(startX + 1, startY));
						}
						break;
					case Direction::left:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(startX - 1, startY);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(startX - 1, startY));
						}
						break;
					}
				}

				if (!canSettingPoint.size())
				{
					break;
				}

				int pointNum = rand() % canSettingPoint.size();
				Vector2 point = canSettingPoint[pointNum];
				std::shared_ptr<CCharacter> character(new CCharacter('0' + charValue));
				wordManager.SetCharacter(point.x, point.y, character);

				std::vector<Direction> addDirection = AdjacentCheck(point.x, point.y);

				for (Direction dir : addDirection)
				{
					switch (dir)
					{
					case Direction::up:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(point.x, point.y - 1);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(point.x, point.y - 1));
						}
						break;
					case Direction::down:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(point.x, point.y + 1);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(point.x, point.y + 1));
						}
						break;
					case Direction::right:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(point.x + 1, point.y);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(point.x + 1, point.y));
						}
						break;
					case Direction::left:
						if (std::find_if(canSettingPoint.begin(), canSettingPoint.end(),
							[&](Vector2 vec)
							{
								return vec == Vector2(point.x - 1, point.y);
							}) == canSettingPoint.end())
						{
							canSettingPoint.push_back(Vector2(point.x - 1, point.y));
						}
						break;
					}
				}

				canSettingPoint.erase(canSettingPoint.begin() + pointNum);

				if (!canSettingPoint.size())
				{
					break;
				}
			}
			canSettingPoint.clear();
			charValues.erase(charValues.begin() + charValueNum);
			if (!charValues.size())
			{
				break;
			}
			charValueNum = (rand() % charValues.size());
			charValue = charValues[charValueNum];

			startX = rand() % wordManager.GetMaxWidth();
			startY = rand() % wordManager.GetMaxHeight();
		}
	}
}

/**
* 設定されていない隣接された場所取得
*/
std::vector<Direction> WordArrangementer::AdjacentCheck(int width, int height)
{
	WordManager& wordManager = WordManager::Instance();

	std::vector<Direction> openDirections;

	if (width >= 1)
	{
		if (!wordManager.GetCharacter(width - 1, height))
		{
			openDirections.push_back(Direction::left);
		}
	}
	if (height >= 1)
	{
		if (!wordManager.GetCharacter(width, height - 1))
		{
			openDirections.push_back(Direction::up);
		}
	}
	if (width + 1 < wordManager.GetMaxWidth())
	{
		if (!wordManager.GetCharacter(width + 1, height))
		{
			openDirections.push_back(Direction::right);
		}
	}
	if (height + 1 < wordManager.GetMaxHeight())
	{
		if (!wordManager.GetCharacter(width, height + 1))
		{
			openDirections.push_back(Direction::down);
		}
	}

	return openDirections;
}

std::vector<Vector2> WordArrangementer::CheckSpace(int width, int height)
{
	// 設定されていない位置
	std::vector<Vector2> points;

	WordManager& wordManager = WordManager::Instance();
	if (wordManager.GetCharacter(width, height))
	{
		return points;
	}
	points.push_back(Vector2(width, height));

	// 調べる位置
	Vector2 checkPoint(width, height);

	// 空いている場所取得
	std::vector<Direction> directions = AdjacentCheck(checkPoint.x, checkPoint.y);

	for (Direction dir : directions)
	{
		switch (dir)
		{
		case Direction::up:
			points.push_back(Vector2(width, height) + Vector2(0, -1));
			break;
		case Direction::down:
			points.push_back(Vector2(width, height) + Vector2(0, 1));
			break;
		case Direction::right:
			points.push_back(Vector2(width, height) + Vector2(1, 0));
			break;
		case Direction::left:
			points.push_back(Vector2(width, height) + Vector2(-1, 0));
			break;
		}
		std::vector<Vector2> addPoints = CheckSpace(points.back().x, points.back().y);

		for (auto addPoint : addPoints)
		{
			points.push_back(addPoint);
		}
	}

	return points;
}