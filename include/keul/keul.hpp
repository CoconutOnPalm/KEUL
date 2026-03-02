/** \file Utility
 * 
 * This is a file that includes all Utility Module files.
 * This is, however not a c++ module, but an old c-style include-all file.
 * To get c++20 module functionality, see [TODO: make modules :) ]
 * 
 * StringLib.hpp: 	provides string operations like splitting, trimming, pattern matching etc.
 * Clock.hpp:		provides simple Clock class for measuring time
 * Benchmark.hpp: 	based on Clock.h, provides even simpler Benchmarking class for fast program performance measuring
 * Random.hpp:		provides class that handles pseudo-number generator, a wrapper around c++ std <random>
 * Range.hpp:		simple range structure, mainly to check if a val is within range (a, b) or [a, b]
 * FileSystem:		provides I/O and IO classes that handle specific text file structuring (similar but worse than JSON)
 * 
 */

#pragma once

#include "error/error-def.hpp"
#include "file-system/file-reader.hpp"
#include "internal/engine-logging.hpp"
#include "logging/logger.hpp"
#include "logging/print.hpp"
#include "logging/simple-logger.hpp"
#include "misc/assert.hpp"
#include "misc/random.hpp"
#include "misc/from-iota.hpp"
#include "string/format.hpp"
#include "string/string-lib.hpp"
#include "time/loop-benchmark.hpp"
#include "time/timer.hpp"

