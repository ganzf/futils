//
// Created by clara on 1/11/18.
//

#include "Text.hpp"
#include "Components/AbsoluteTransform.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Text::renderText(components::Text const &txt, sf::RenderWindow &window)
    {
        auto &absolute = txt.getEntity().get<components::AbsoluteTransform>();
        sf::Text text;

        //TODO: stock font dans une map d'assets au démarrage?
        //TODO: avoir ces données
        sf::Font font;
        sf::Color color;

        color << txt.style.color;
        font.loadFromFile(txt.style.font);
        text.setFont(font);
        text.setString(txt.str);
        text.setCharacterSize(txt.style.size);
        text.setFillColor(color);
        text.setPosition(sf::Vector2f(absolute.position.x, absolute.position.y));

        window.draw(text);
    }

    void Text::init() {
        __init();
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                //TODO: test with another game object -> method has in an entity
                try {
                    auto &text = obj->get<components::Text>();
                    renderText(text, *packet.window);
                }
                catch (...) {}
            }
        });
        phase = Run;
    }

    void Text::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
