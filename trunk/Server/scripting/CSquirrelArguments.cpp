//============== Networked: IV - http://code.networked-iv.com ==============
//
// File: CSquirrelArguments.cpp
// Project: Server
// Author(s): mabako
// License: See LICENSE in root directory
//
//==========================================================================

#include <StdInc.h>

void CSquirrelArguments::push_to_vm(SQVM* pVM)
{
	for(iterator iter = begin(); iter != end(); ++ iter)
	{
		switch((*iter)->GetType())
		{
			case OT_NULL:
				sq_pushnull(pVM);
				break;
			case OT_INTEGER:
				sq_pushinteger(pVM, (*iter)->data.i);
				break;
			case OT_BOOL:
				sq_pushbool(pVM, (*iter)->data.b);
				break;
			case OT_FLOAT:
				sq_pushfloat(pVM, (*iter)->data.f);
				break;
			case OT_STRING:
				sq_pushstring(pVM, (*iter)->data.str->Get(), (*iter)->data.str->GetLength());
				break;
			case OT_FUNCPROTO:
				sq_pushentity(pVM, (*iter)->data.pEntity);
				break;
			default:
				sq_pushnull(pVM); // table, array, whatsoever. do not even care. fix it if you dare.
				assert(0);
		}
	}
}

void CSquirrelArguments::push()
{
	push_back(new CSquirrelArgument());
}

void CSquirrelArguments::push(int i)
{
	push_back(new CSquirrelArgument(i));
}

void CSquirrelArguments::push(bool b)
{
	push_back(new CSquirrelArgument(b));
}

void CSquirrelArguments::push(float f)
{
	push_back(new CSquirrelArgument(f));
}

void CSquirrelArguments::push(const char* c)
{
	push_back(new CSquirrelArgument(new String(c)));
}

void CSquirrelArguments::push(String str)
{
	push_back(new CSquirrelArgument(new String(str)));
}

void CSquirrelArguments::push(CEntity* pEntity)
{
	push_back(new CSquirrelArgument(pEntity));
}

bool CSquirrelArguments::pushFromStack(SQVM* pVM, int idx)
{
	switch(sq_gettype(pVM,idx))
	{
		case OT_NULL:
			push();
			break;
		case OT_INTEGER:
			{
				int i;
				sq_getinteger(pVM, idx, &i);
				push(i);
			}
			break;
		case OT_BOOL:
			{
				SQBool b;
				sq_getbool(pVM, idx, &b);
				push(b!=0);
			}
			break;
		case OT_FLOAT:
			{
				float f;
				sq_getfloat(pVM, idx, &f);
				push(f);
			}
			break;
		case OT_STRING:
			{
				const char* szTemp;
				sq_getstring(pVM, idx, &szTemp);
				push(szTemp);
			}
			break;
		default:
			return false;
	}
	return true;
}
