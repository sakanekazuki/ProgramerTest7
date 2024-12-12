#include <iostream>

#include "WordManager.h"
#include "WordArrangementer.h"
#include "Character.h"

int main()
{
	WordManager::Initialize(4, 4);

	WordArrangementer arrangementer(3, 4, 5);

	WordManager& wordManager = WordManager::Instance();

	for (int i = 0; i < 16; ++i)
	{
		if ((i % 4 == 0) && i)
		{
			std::cout << "\n";
		}
		auto c = wordManager.GetCharacter(i % 4, i / 4);
		if (c)
		{
			std::cout << c->GetChar() << ", ";
		}
		else
		{
			std::cout << " , ";
		}
	}

	WordManager::Finalize();

	return 0;
}