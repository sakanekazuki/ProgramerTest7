#pragma once

class CCharacter
{
public:
	CCharacter(char c = '\0');
	~CCharacter() = default;

	char GetChar()const;

	bool IsSet()const;

private:
	char c = '\0';

};