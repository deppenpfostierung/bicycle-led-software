#pragma once

#define RESISTOR_DIVIDER_MULTIPLIER(R1, R2) ((R1 + R2) / R2)

template <typename Tv> constexpr auto map_value(Tv value, Tv in_min, Tv in_max, Tv out_min, Tv out_max) -> Tv
{
    return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}