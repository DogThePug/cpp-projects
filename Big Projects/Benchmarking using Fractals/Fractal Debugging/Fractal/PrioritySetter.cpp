#include "stdafx.h"
#include "PrioritySetter.h"
#include <Windows.h>

PrioritySetter::PrioritySetter()
{

}


PrioritySetter::~PrioritySetter()
{
}

void PrioritySetter::SetPriority(int Case)
{
	switch (Case)
	{
	case 1:
		SetPriorityClass(GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS);
		break;
	case 2:
		SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
		break;
	default:
		SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
		break;
	}
}
