//
// Created by arroganz on 2018-07-31
//

#include "events.hpp"
#include "Fysix.hpp"

extern "C" futils::ISystem *build()
{
    return new Fysix();
}

Fysix::Fysix()
{
    name = "Fysix";
}

void Fysix::init() {
    phase++;
    addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
        entityManager->removeSystem(name);
    });
    entityManager->addSystem<FysicsSystems::RigidBody>();
    entityManager->addSystem<FysicsSystems::Collision>();
    state = Run;
}

void Fysix::run(float)
{
    switch (state)
    {
        case Init : return init();
        case Run : return ;
    }
}