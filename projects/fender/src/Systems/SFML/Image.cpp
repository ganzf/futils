//
// Created by clara on 1/8/18.
//

#include "Image.hpp"
#include "Camera.hpp"

namespace fender::systems::SFMLSystems
{
    void Image::renderImage(components::Image const &image, sf::RenderWindow &window){
        auto &absolute = image.getEntity().get<components::AbsoluteTransform>();

        /*sf::Texture texture;
        if (!texture.loadFromFile(image.file))
            std::cout << "charge pas :(" << std::endl;

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(absolute.position.x, absolute.position.y);*/

        sf::RectangleShape shape;
        sf::Color color;
        color = sf::Color::Blue;
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineThickness(10);
        shape.setOutlineColor(color);
        shape.setSize(sf::Vector2f(absolute.size.w, absolute.size.h));
        shape.setPosition(absolute.position.x, absolute.position.y);
        window.draw(shape);
    }

    void Image::init() {
        __init();
        addReaction<RenderLayer>([this](futils::IMediatorPacket &pkg){
            auto &packet = futils::Mediator::rebuild<RenderLayer>(pkg);
            for (auto &obj: packet.objects)
            {
                auto &image = obj->get<components::Image>();
                // Faudrait get que les images pour render que les images et pas avoir de pb de sfml load texture mon cul
                // Et du coup file toujours vide alors que je le set dans WindowTest
                std::cout << "l'image : " << image.file << std::endl;
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