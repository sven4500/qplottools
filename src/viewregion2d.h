#pragma once
#ifndef QPLOTTOOLS_VIEWREGION_H_
#define QPLOTTOOLS_VIEWREGION_H_

#include <cmath> // abs, ...

struct ViewRegion2D
{
    double spanX()const
    {
        return std::abs(maxX - minX);
    }

    double spanY()const
    {
        return std::abs(maxY - minY);
    }

    double minX = 0.0;
    double maxX = 1.0;

    double minY = 0.0;
    double maxY = 1.0;

};

#endif
