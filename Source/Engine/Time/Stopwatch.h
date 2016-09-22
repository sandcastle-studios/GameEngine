#pragma once

class Stopwatch
{
public:
	Stopwatch();
	~Stopwatch();

	void Restart();

	Time GetElapsedTime() const;

private:
	LONGLONG myStartTime;
	float myFrequency;
};

