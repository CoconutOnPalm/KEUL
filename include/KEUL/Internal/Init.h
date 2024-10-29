#pragma once

#include "../Error/ErrorDef.h"
#include "../String/Format.h"
#include "../Time/Benchmark.h"

namespace ke
{
	// pre-calculate all static data inside the library
	static void Init()
	{
		_internal::errorToString(Error::Error);
		_impl::interpret_ansi_codes("");
	}
}
