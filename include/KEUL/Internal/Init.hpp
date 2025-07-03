#pragma once

#include "../Error/ErrorDef.hpp"
#include "../String/Format.hpp"
#include "../Time/Benchmark.hpp"

namespace ke
{
	// Pre-calculate all static data inside the library. Optional.
	inline static void Init()
	{
		_internal::errorToString(Error::Error);
		auto val = _impl::interpret_ansi_codes("");
	}
}
