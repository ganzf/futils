//
// Created by arroganz on 12/17/17.
//

#include "SFMLRenderer.hpp"
#include "Window.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Grid.hpp"
#include "Children.hpp"
#include "Border.hpp"
#include "Image.hpp"
#include "Clickable.hpp"
#include "Text.hpp"
<<<<<<< HEAD
#include "AssetLoader.hpp"
=======
#include "ListView.hpp"
>>>>>>> ListView Ok

fender::systems::SFMLRenderer::SFMLRenderer()
{
    name = "SFML";
}

void fender::systems::SFMLRenderer::init() {
    state = NONE;
    entityManager->addSystem<SFMLSystems::Window>();
    entityManager->addSystem<SFMLSystems::Input>();
    entityManager->addSystem<SFMLSystems::Camera>();
    entityManager->addSystem<SFMLSystems::Grid>();
    entityManager->addSystem<SFMLSystems::Children>();
    entityManager->addSystem<SFMLSystems::AssetLoader>();
    entityManager->addSystem<SFMLSystems::ListView>();
    entityManager->addSystem<SFMLSystems::Border>();
    entityManager->addSystem<SFMLSystems::Text>();
    entityManager->addSystem<SFMLSystems::Image>();
    entityManager->addSystem<SFMLSystems::Clickable>();
    addReaction<events::Shutdown>([this](futils::IMediatorPacket &){
        entityManager->removeSystem(name);
    });
}

void fender::systems::SFMLRenderer::run(float)
{
    switch (state) {
        case NONE: return ;
        case INIT : return init();
        case RENDER : return ;
    }
}