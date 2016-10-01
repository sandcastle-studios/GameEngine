#pragma once

namespace ENGINE_NAMESPACE
{
	class Time
	{
	public:
		Time()
		{
			myTimeInSeconds = 0.f;
		}

		friend bool operator==(const Time& aLhs, const Time& aRhs)
		{
			return aLhs.myTimeInSeconds == aRhs.myTimeInSeconds;
		}

		friend bool operator!=(const Time& aLhs, const Time& aRhs)
		{
			return !(aLhs == aRhs);
		}

		friend bool operator<(const Time& aLhs, const Time& aRhs)
		{
			return aLhs.myTimeInSeconds < aRhs.myTimeInSeconds;
		}

		friend bool operator<=(const Time& aLhs, const Time& aRhs)
		{
			return !(aRhs < aLhs);
		}

		friend bool operator>(const Time& aLhs, const Time& aRhs)
		{
			return aRhs < aLhs;
		}

		friend bool operator>=(const Time& aLhs, const Time& aRhs)
		{
			return !(aLhs < aRhs);
		}

		Time &operator +=(const Time &aRhs)
		{
			myTimeInSeconds += aRhs.myTimeInSeconds;
			return *this;
		}

		Time &operator -=(const Time &aRhs)
		{
			myTimeInSeconds -= aRhs.myTimeInSeconds;
			return *this;
		}

		friend Time operator +(const Time &aLhs, const Time &aRhs)
		{
			return Time(aLhs.myTimeInSeconds + aRhs.myTimeInSeconds);
		}

		friend Time operator -(const Time &aLhs, const Time &aRhs)
		{
			return Time(aLhs.myTimeInSeconds - aRhs.myTimeInSeconds);
		}

		float InSeconds() const
		{
			return myTimeInSeconds;
		}

		float InMinutes() const
		{
			return myTimeInSeconds / 60.f;
		}

		float InMilliseconds() const
		{
			return myTimeInSeconds * 1000.f;
		}

		static Time FromMinutes(float aMinuteAmount)
		{
			return Time(aMinuteAmount * 60.f);
		}

		static Time FromSeconds(float aSecondAmount)
		{
			return Time(aSecondAmount);
		}
		Time(float aSecondAmount)
		{
			myTimeInSeconds = aSecondAmount;
		}

	private:
		float myTimeInSeconds;
	};
}
