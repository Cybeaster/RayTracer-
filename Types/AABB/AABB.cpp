//
// Created by Cybea on 21/11/2023.
//

#include "AABB.h"


const SInterval& SAABB::Axis(const int32_t N) const
{
	switch (N)
	{
	case 1:
		return Y;
	case 2:
		return Z;
	default:
		return X;
	}
}

bool SAABB::Hit(const SRay& Ray, SInterval Interval) const
{
	for (uint32_t i = 0; i < 3; ++i)
	{
		// Calculate the inverse of the ray's direction for the current axis
		const auto invD = 1 / Ray.GetDirection().a[i];

		// Get the origin component of the ray for the current axis
		const auto origin = Ray.GetOrigin().a[i];

		// Calculate the intersection parameter t0 with the min plane of the axis
		auto t0 = (Axis(i).Min - origin) * invD;

		// Calculate the intersection parameter t1 with the max plane of the axis
		auto t1 = (Axis(i).Max - origin) * invD;

		// If the ray is pointing in the negative direction of the current axis
		if (invD < 0.0f)
		{
			// Swap t0 and t1 to ensure correct ordering (entry and exit points)
			std::swap(t0, t1);
		}

		// If the entry point extends the current interval
		if (t0 > Interval.Min)
		{
			Interval.Min = t0; // Update the minimum value of the interval
		}

		// If the exit point reduces the current interval
		if (t1 < Interval.Max)
		{
			Interval.Max = t1; // Update the maximum value of the interval
		}

		if (Interval.Max <= Interval.Min) // Check if the interval is still valid (Max should be greater than Min)
		{
			return false; // If the interval is invalid, the ray does not intersect within the interval
		}

		/* Not optimized simple implemetation
		 const auto t0 = fmin((Axis(i).Min - Ray.GetOrigin().a[i]) / Ray.GetDirection().a[i],
		                     (Axis(i).Max - Ray.GetOrigin().a[i]) / Ray.GetDirection().a[i]);

		const auto t1 = fmax((Axis(i).Min - Ray.GetOrigin().a[i]) / Ray.GetDirection().a[i],
		                     Axis(i).Max - Ray.GetOrigin().a[i] / Ray.GetDirection().a[i]);

		Interval.Min = fmax(t0, Interval.Min);
		Interval.Max = fmin(t1, Interval.Max);

		if (Interval.Max <= Interval.Min)
		{
			return false;
		}*/
	}
	return true;
}
