//
// Created by clara on 1/8/18.
//

#include "Image.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Image::renderImage(components::Image const &image, sf::RenderWindow &window){
        auto &absolute = image.getEntity().get<components::AbsoluteTransform>();
        //TODO: stock texture in a map with filename as key -> ASSETS LOADER
        sf::Texture texture;
        texture.loadFromFile(image.file);
        texture.setSmooth(true);

        sf::RectangleShape sprite;
        sprite.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
        sprite.setTexture(&texture);
        sprite.setPosition(absolute.position.x, absolute.position.y);

        window.draw(sprite);
    }

    void Image::init() {
        __init();
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                //TODO: test with another game object -> method has in an entity
                auto &image = obj->get<components::Image>();
                renderImage(image, *packet.window);
            }
        });
        phase = Run;
    }

    void Image::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
