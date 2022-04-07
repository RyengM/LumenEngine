#pragma once

#include "Core/Math/Public/MathUtil.h"

using namespace Lumen::Core;

namespace Lumen::Game
{
    // Helper struct deal with device IO status
    struct DeviceStatus
    {
		float mouseSensitivity = 0.2f;

		Vec2 cursorLastPos = Vec2(0.f, 0.f);
		Vec2 delta = Vec2(0.f, 0.f);

		bool leftAltActive = false;
		bool leftShiftActive = false;
		bool leftMouseActive = false;
		bool rightMouseActive = false;

		bool wPressed = false;
		bool sPressed = false;
		bool aPressed = false;
		bool dPressed = false;

		bool bSceneWindow = false;

		void ProcessMouseMovement(float x, float y)
		{
			Vec2 pos{ x, y };
			delta = (pos - cursorLastPos) * mouseSensitivity;

			cursorLastPos = pos;
		}
    };
}