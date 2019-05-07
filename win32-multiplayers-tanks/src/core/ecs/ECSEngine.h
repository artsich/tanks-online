#pragma once 

#include <vector>

#include "GameObject.h"
#include "IComponent.h"
#include "ISystem.h"
#include "managers/ComponentManager.h"

#include "../../core/memory/IAllocator.h"

namespace core { namespace ecs {
    class ECSEngine
    {
    private:
        std::vector<ISystem*> Systems;
        ComponentManager* CManager;
		
    public:
		ECSEngine(ComponentManager* CManager) :
			CManager(CManager)
		{
		}

        void addSystem(ISystem* system)
        {
            if(system != nullptr)
            {
                Systems.push_back(system);
            }
        }

        void update(f32 delta)
        {
            for(u32 i = 0; i < Systems.size(); ++i)
            {
                Systems[i]->Update(delta);
            }
        }

		ComponentManager* GetComponentManager() { return CManager; }
    };
} }