//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Rendering/Color.h"

void Color::display (std::ostream& out, const Color& point_rgb)
{
	static const Range intensity (0.0, 0.999);

    int r_byte = int (256 * intensity.clamp(point_rgb.x));
    int g_byte = int (256 * intensity.clamp(point_rgb.y));
    int b_byte = int (256 * intensity.clamp(point_rgb.z));

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}
