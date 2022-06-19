#include "smoothStep.h"

float clamp(float x, float lowerLimit, float upperLimit)
{
    if(x < lowerLimit)
    {
        x = lowerLimit;
    }
    if(x > upperLimit)
    {
        x = upperLimit;
    }

    return x;
}

float smoothstep(float edge0, float edge1, float x)
{
    x = clamp((x - edge0) / (edge1 - edge0), 0, 1.0);
    return x * x * (3 - 2 * x);
}
