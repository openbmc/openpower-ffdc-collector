#pragma once

#include <cstddef> // for size_t
#include <map>
#include <string>
#include <vector>

namespace watchdog
{
namespace dump
{

constexpr int maxTraceLen = 64; // characters

constexpr auto pathLogging = "/xyz/openbmc_project/logging";
constexpr auto levelPelError = "xyz.openbmc_project.Logging.Entry.Level.Error";

/** @brief Commit watchdog timeout handler failure event to log */
void eventWatchdogTimeout();

} // namespace dump
} // namespace watchdog