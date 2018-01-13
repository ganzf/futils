//
// Created by arroganz on 1/13/18.
//

#include "Fysics.hpp"
#include "RigidBody.hpp"

namespace fender::systems
{
    void Fysics::init()
    {
        addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
            entityManager->removeSystem(name);
        });
        entityManager->addSystem<FysicsSystems::RigidBody>();
        state = Run;
    }

    void Fysics::run(float) {
        switch (state)
        {
            case Init : return init();
            case Run : return ;
        }
    }
}