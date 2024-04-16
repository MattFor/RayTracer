//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Rendering/Color.h"

inline double linear_to_gamma (double linear_component)
{
	if (linear_component > 0)
	{
		return std::sqrt(linear_component);
	}

	return 0;
}

void Color::display (std::ostream& out, const Color& point_rgb)
{
	static const Range intensity (0.0, 0.999);

	// Before clamping apply gamma correction so that image viewers correctly recognize the image
	// Now we clamp the result so it stays within the 0, 255 range.
    int r_byte = int (256 * intensity.clamp(linear_to_gamma(point_rgb.x)));
    int g_byte = int (256 * intensity.clamp(linear_to_gamma(point_rgb.y)));
    int b_byte = int (256 * intensity.clamp(linear_to_gamma(point_rgb.z)));

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}
