//
// Created by clara on 1/11/18.
//

#include <Components/Transform.hpp>
#include <Components/AbsoluteTransform.hpp>
#include "inputKeys.hpp"
#include "Clickable.hpp"

namespace fender::systems::SFMLSystems
{
    void Clickable::init() {
        __init();
        addReaction<futils::MouseClicked>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<futils::MouseClicked>(pkg);
            auto clickables = entityManager->get<components::Clickable>();

            for (auto &click : clickables)
            {
                if (!click->has<components::AbsoluteTransform>())
                    continue ;
                auto absolute = click->getEntity().get<components::AbsoluteTransform>();
                if (packet.pos.x >= absolute.position.x && packet.pos.x <= absolute.position.x + absolute.size.w
                    && packet.pos.y >= absolute.position.y && packet.pos.y <= absolute.position.y + absolute.size.h)
                    click->func();
            }
        });
        phase = Run;
    }

    void Clickable::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
