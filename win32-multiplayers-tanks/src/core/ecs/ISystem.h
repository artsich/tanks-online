#pragma once
#include "../core.h"

namespace core { namespace ecs {

	struct ISystem
    {
        virtual void Update(f32 DeltaTime) = 0;
    };

}}