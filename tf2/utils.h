#pragma once
#include "structs.h"
#include "Interfaces.h"
#include "structs.h"

namespace utils
{
    static bool ScreenTransform(const Vector& point, Vector& screen) noexcept
    {
        const matrix3x4_t& w2sMatrix = Interfaces::engine->WorldToScreenMatrix();

        screen.x = w2sMatrix[0][0] * point.x + w2sMatrix[0][1] * point.y + w2sMatrix[0][2] * point.z + w2sMatrix[0][3];
        screen.y = w2sMatrix[1][0] * point.x + w2sMatrix[1][1] * point.y + w2sMatrix[1][2] * point.z + w2sMatrix[1][3];
        screen.z = 0.0f;

        float w = w2sMatrix[3][0] * point.x + w2sMatrix[3][1] * point.y + w2sMatrix[3][2] * point.z + w2sMatrix[3][3];

        if (w < 0.001f) {
            screen.x *= 100000;
            screen.y *= 100000;
            return true;
        }

        float invw = 1.0f / w;
        screen.x *= invw;
        screen.y *= invw;

        return false;
    }

    bool WorldToScreen(const Vector& origin, Vector& screen) noexcept
    {
        int h, w;
        Interfaces::engine->GetScreenSize(w, h);

        if (!ScreenTransform(origin, screen)) {
            screen.x = (w / 2.0f) + (screen.x * w) / 2;
            screen.y = (h / 2.0f) - (screen.y * h) / 2;

            return true;
        }
        return false;
    }
}

