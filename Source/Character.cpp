#include "Character.h"

CCharacter::CCharacter(char c)
	:c(c){}

char CCharacter::GetChar()const
{
	return c;
}

bool CCharacter::IsSet()const
{
	return c != '\0';
}