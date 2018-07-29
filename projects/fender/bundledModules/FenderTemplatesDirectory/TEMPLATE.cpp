//
// Created by TEMPLATE_MODULE_CREATOR on TEMPLATE_MODULE_CREATION_DATE
//

#include "events.hpp"
#include "TEMPLATE_MODULE_NAME.hpp"

extern "C" futils::ISystem *build()
{
    return new TEMPLATE_MODULE_NAME();
}

TEMPLATE_MODULE_NAME::TEMPLATE_MODULE_NAME()
{
    name = "TEMPLATE_MODULE_NAME";
}

void TEMPLATE_MODULE_NAME::init() {
    phase++;
    addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
        entityManager->removeSystem(name);
    });
}

void TEMPLATE_MODULE_NAME::run(float)
{
    switch (phase) {
        case 0: return init();
    }
}