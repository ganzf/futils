//
// Created by clara on 1/11/18.
//

#pragma once

# include <SFML/Graphics.hpp>
# include "System.hpp"
# include "Components/Text.hpp"

namespace fender::systems::SFMLSystems
{
    class Text : public System {
        enum States
        {
            Init = 0,
            Run
        };
        //void renderBorder(components::Border const &, sf::RenderWindow &);
        void renderText(components::Text const &, sf::RenderWindow &);
        void init();
        //bool shouldPrint; // debug only
    public:
        Text(): System("Text") {}
        void run(float) override;
    };
}
