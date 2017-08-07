#include "stdafx.h"
#include "Objectx.h"

using namespace SDUI;

CObjectx::CObjectx()
{
}


CObjectx::~CObjectx()
{
}

bool SDUI::CObjectx::equal(CObjectx* obj)
{
	if (!obj || obj->getClassType() == T_Undefined)
	{
		return false;
	}

	if (obj->getClassType() != getClassType())
	{
		return false;
	}

	CObjectx* p = static_cast<CObjectx*>(obj);
	return (p == this);
}
