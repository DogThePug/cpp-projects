#include "stdafx.h"
#include "PrioritySetter.h"
#include <Windows.h>

PrioritySetter::PrioritySetter()
{

}


PrioritySetter::~PrioritySetter()
{
}

void PrioritySetter::SetPriority()
{
	SetPriorityClass(GetCurrentProcess(), NORMAL_PRIORITY_CLASS);
}
