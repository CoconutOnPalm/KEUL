#pragma once

#include "../Error/ErrorDef.h"
#include "../String/Format.h"
#include "../Time/Benchmark.h"

namespace ke
{
	// Pre-calculate all static data inside the library. Optional.
	static void Init()
	{
		_internal::errorToString(Error::Error);
		_impl::interpret_ansi_codes("");
	}
}
