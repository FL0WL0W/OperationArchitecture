#include "Interpolation.h"

#ifdef INTERPOLATION_H
namespace Interpolation
{
	InterpolationResponse Interpolate(const float value, const float * const axis, const uint8_t resolution)
	{
		InterpolationResponse response = { 0, 0, 0 };
		if (resolution > 1)
		{
			//value is below minimum
			if(value <= axis[0])
				return response;

			while(++response.IndexH < resolution && axis[response.IndexH] < value);

			//this means value is above maximum
			if(response.IndexH == resolution)
			{
				response.IndexL = response.IndexH = response.IndexH - 1;
				return response;
			}

			response.IndexL = response.IndexH - 1;

			response.Multiplier = (value - axis[response.IndexL]) / (axis[response.IndexH] - axis[response.IndexL]);
		}

		return response;
	}
}
#endif
