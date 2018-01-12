//
// Created by clara on 1/8/18.
//

#include "Image.hpp"
#include "Camera.hpp"
#include "AssetLoader.hpp"

namespace fender::systems::SFMLSystems
{
    void Image::renderImage(components::Image const &image, sf::RenderWindow &window){
        auto &absolute = image.getEntity().get<components::AbsoluteTransform>();

        sf::Texture texture = (*_textures)[image.file];
        sf::RectangleShape sprite;
        sprite.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
        sprite.setTexture(&texture);
        sprite.setPosition(absolute.position.x, absolute.position.y);
        window.draw(sprite);
    }

    void Image::init() {
        __init();

        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            //std::cout << "Combien de texture ? = " << _textures->size() << std::endl;
            if (_textures == nullptr)
                return;
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                if (!obj->has<components::Image>())
                    continue ;
                auto &image = obj->get<components::Image>();
                renderImage(image, *packet.window);
            }
        });

        addReaction<SendAssets>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<SendAssets>(pkg);
                _textures = packet.textures;
        });

        events->send<RequestAssets>(RequestAssets());
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
