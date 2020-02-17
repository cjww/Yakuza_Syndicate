#include "GangMembers.h"

GangMembers::GangMembers()
{
}

void GangMembers::fight(GangMembers &other)
{
	int strThis = this->amount;
	int strOther = other.amount;
	if (this->inFriendlyTerr)
	{
		strThis *= 1.5;
	}
	else if (other.inFriendlyTerr)
	{
		strOther *= 1.5;
	}

	if (strThis < strOther)
	{
		other.amount -= strThis;
		this->amount = 0;
			
	}
	else if (strThis > strOther)
	{
		this->amount -= strOther;
		other.amount = 0;
	}
	else
	{
		this->amount = 0;
		other.amount = 0;
	}
	
}
