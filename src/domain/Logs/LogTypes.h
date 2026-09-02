
#pragma once

enum class ELogLevel : int
{
	Info = 1,
	Warning = 1 << 1,
	Error = 1 << 2,
	Fatal = 1 << 3
};