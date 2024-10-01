/** \file Utility
 * 
 * This is a file that includes all Utility Module files.
 * This is, however not a c++ module, but an old c-style include-all file.
 * To get c++20 module functionality, see [TODO: make modules :) ]
 * 
 * StringLib.h: provides string operations like splitting, trimming, pattern matching etc.
 * Clock.h:		provides simple Clock class for measuring time
 * Benchmark.h: based on Clock.h, provides even simpler Benchmarking class for fast program performance measuring
 * Random.h:	provides class that handles pseudo-number generator, a wrapper around c++ std <random>
 * Range.h:		simple range structure, mainly to check if a val is within range (a, b) or [a, b]
 * FileSystem:	provides I/O and IO classes that handle specific text file structuring (similar but worse than JSON)
 * 
 */

#pragma once

#include "Error/ErrorDef.h"
#include "FileSystem/FileReader.h"
#include "Internal/EngineLogging.h"
#include "Internal/Init.h"
#include "Logging/Logger.h"
#include "Logging/Print.h"
#include "Logging/SimpleLogger.h"
#include "Misc/Assert.h"
#include "Misc/Random.h"
#include "String/Format.h"
#include "String/StringLib.h"
#include "Time/LoopBenchmark.h"

