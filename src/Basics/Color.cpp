//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Basics/Color.h"

void Color::display (std::ostream& out, const Color& point_rgb)
{
    int r_byte = int (255.999 * point_rgb.x);
    int g_byte = int (255.999 * point_rgb.y);
    int b_byte = int (255.999 * point_rgb.z);

    out << r_byte << ' ' << g_byte << ' ' << b_byte << '\n';
}
