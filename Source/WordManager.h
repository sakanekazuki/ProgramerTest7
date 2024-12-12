#pragma once

#include <memory>
#include <vector>

class CCharacter;

class WordManager
{
public:
	static bool Initialize(int width, int height);
	static void Finalize();
	static WordManager& Instance();

	void ResetCharacters();

	void SetCharacter(int width, int height, std::shared_ptr<CCharacter> character);

	std::shared_ptr<CCharacter> GetCharacter(int width, int hegiht);
	int GetMaxWidth()const;
	int GetMaxHeight()const;

private:
	WordManager(int width, int height);
	~WordManager() = default;

	WordManager(const WordManager&) = delete;
	WordManager& operator=(const WordManager&) = delete;

	std::vector<std::vector<std::shared_ptr<CCharacter>>> characters;

	int width = 0;
	int height = 0;

};