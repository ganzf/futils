//
// Created by arroganz on 1/25/18.
//

#include "Debug.hpp"

extern "C" futils::ISystem *build()
{
    return new Debug;
}

void Debug::init()
{
    addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
        entityManager->removeSystem(name);
    });
    state = 1;
}

void Debug::run(float) {
    switch (state) {
        case 0:
            return init();
        case 1:
            return ;
    }
}