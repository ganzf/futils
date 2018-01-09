//
// Created by arroganz on 1/3/18.
//

#include "Entities/GameObject.hpp"
#include "Children.hpp"

namespace fender::systems::SFMLSystems
{
    void Children::rec_updateChildInfo(components::ChildInfo &info)
    {
        if (info.parent != nullptr)
        {
            try {
//                auto &parentIsChild = info.getEntity().get<components::ChildInfo>();
//                if (parentIsChild.parent != nullptr) {
//                    rec_updateChildInfo(parentIsChild);
//                }
            } catch (std::runtime_error const &)
            {
                events->send<std::string>("Reached final parent in ChildSystem rec.");
                return ;
            } // TODO: create your own exception type
            auto &parent = info.parent->get<components::Transform>();
            auto &self = info.getEntity().get<components::Transform>();
            self.position.x = info.offset.x / 100 * parent.size.w + parent.position.x;
            self.position.y = info.offset.y / 100 * parent.size.h + parent.position.y;
            // TODO : Use info.isGridRelative !
        }
    }

    void Children::updateAllChildren()
    {
        auto children = entityManager->get<components::ChildInfo>();
        for (auto child: children)
            rec_updateChildInfo(*child);
    }

    void Children::run(float) {
        switch (phase)
        {
            case Init : return init();
            case Run : return updateAllChildren();
        }
    }

    void Children::init() {
        __init();
        phase = Run;
    }
}