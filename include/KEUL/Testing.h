#pragma once

#include "UnitTests/TestManager.h"

/**
 * @brief Runs all tests registered with the KE_TEST macro. 
 */
#define KE_RUN_ALL_TESTS() ::ke::test::_internal::TestManager::RunAllTests()
