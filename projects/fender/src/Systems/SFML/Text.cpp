//
// Created by clara on 1/11/18.
//

#include "Text.hpp"
#include "Components/AbsoluteTransform.hpp"
#include "Camera.hpp"
#include "AssetLoader.hpp"

namespace fender::systems::SFMLSystems
{
    void Text::renderText(components::Text const &txt, sf::RenderWindow &window)
    {
        auto &absolute = txt.getEntity().get<components::AbsoluteTransform>();
        if (absolute.size.w == 0 || absolute.size.h == 0)
            return ;
        sf::Text text;
        sf::Color color;

        color << txt.style.color;
        text.setFont((*_fonts)[txt.style.font]);
        text.setString(txt.str);
        //std::cout << 0.25 *absolute.size.h << "compare to " << txt.style.size << std::endl;
        text.setCharacterSize(txt.style.size);

        if (text.getGlobalBounds().width > absolute.size.x)
            text.setCharacterSize((absolute.size.h / absolute.size.w) / absolute.size.w);

        text.setFillColor(color);
        text.setPosition(sf::Vector2f(absolute.position.x, absolute.position.y));

        window.draw(text);
    }

    void Text::init() {
        __init();
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            if (_fonts == nullptr)
                return;
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                if (!obj->has<components::Text>())
                    continue ;
                auto &text = obj->get<components::Text>();
                renderText(text, *packet.window);
            }
        });

        addReaction<AssetsLoaded>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<AssetsLoaded>(pkg);
            _fonts = packet.fonts;
        });

        events->send<RequestAssets>(RequestAssets());

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
