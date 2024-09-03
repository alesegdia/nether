#pragma once

namespace nether
{
    struct Color
    {
        static const Color White;

        float r, g, b, a;
    };

    inline constexpr Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);
}
