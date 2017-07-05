#include "uFunctionStorage.h"

using namespace utl;

uFunctionStorage::uFunctionStorage()
{
}


uFunctionStorage::~uFunctionStorage()
{
}


// calls a function with stored arguments
void uFunctionStorage::Call(uint32_t call_id)
{
	if(_functionCalls.count(call_id) == 1)
		_functionCalls.at(call_id)->execute();
}
