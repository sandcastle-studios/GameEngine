#include "stdafx.h"
#include "Engine\Time\Stopwatch.h"

namespace ENGINE_NAMESPACE
{
	Stopwatch::Stopwatch()
	{
		LARGE_INTEGER freq, pc;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&pc);

		myFrequency = static_cast<float>(freq.QuadPart);
		myStartTime = pc.QuadPart;
	}

	Stopwatch::~Stopwatch()
	{
	}

	Time Stopwatch::GetElapsedTime() const
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);
		return Time::FromSeconds(static_cast<float>(pc.QuadPart - myStartTime) / myFrequency);
	}

	void Stopwatch::Restart()
	{
		LARGE_INTEGER pc;
		QueryPerformanceCounter(&pc);
		myStartTime = pc.QuadPart;
	}
}
