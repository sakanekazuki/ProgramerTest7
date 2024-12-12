#include "WordManager.h"

#include <iostream>

#include "Character.h"

namespace
{
WordManager* wordManager = nullptr;
}

WordManager::WordManager(int width, int height)
	:width(width)
	, height(height)
{
	if (width <= 0 || height <= 0)
	{
		std::cerr << "–³Œø‚È”\n";
		return;
	}

	characters.resize(height);
	for (int i = 0; i < width; ++i)
	{
		characters[i].resize(4);
	}

	ResetCharacters();
}

bool WordManager::Initialize(int width, int height)
{
	if (!wordManager)
	{
		wordManager = new WordManager(width, height);
		if (!wordManager)
		{
			return false;
		}
	}

	return true;
}

void WordManager::Finalize()
{
	if (wordManager)
	{
		delete wordManager;
		wordManager = nullptr;
	}
}

WordManager& WordManager::Instance()
{
	return *wordManager;
}

void WordManager::ResetCharacters()
{
	//std::shared_ptr<CCharacter> character(new CCharacter('0'));
	for (int h = 0; h < height; ++h)
	{
		for (int w = 0; w < width; ++w)
		{
			characters[h][w] = nullptr;
		}
	}

	//characters[3][3] = nullptr;
	//characters[3][2] = nullptr;
}

void WordManager::SetCharacter(int width, int height, std::shared_ptr<CCharacter> character)
{
	characters[height][width] = character;
}

std::shared_ptr<CCharacter> WordManager::GetCharacter(int width, int height)
{
	if (height >= characters.size() || height < 0)
	{
		return nullptr;
	}
	if (width < 0 || width >= characters[height].size())
	{
		return nullptr;
	}
	return characters[height][width];
}

int WordManager::GetMaxWidth()const
{
	return width;
}

int WordManager::GetMaxHeight()const
{
	return height;
}