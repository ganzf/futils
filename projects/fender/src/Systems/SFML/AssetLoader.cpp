//
// Created by clara on 1/12/18.
//

#include "AssetLoader.hpp"

namespace fender::systems::SFMLSystems
{
    void AssetLoader::init() {
        __init();
        //TODO: Dans image et text system-> send ce packet et attendre la réponse avant de se run
        addReaction<RequestAssets>([this](futils::IMediatorPacket &){
            if (_textures.size() == Texture.size() && _fonts.size() == Font.size()) {
                AssetsLoaded assets;
                assets.fonts = &_fonts;
                assets.textures = &_textures;
                events->send<AssetsLoaded>(assets);
            }
        });

        for (auto file : Texture) {
            sf::Texture texture;
            if (!texture.loadFromFile(file)) {
                events->send<std::string>("\e[31m ☒ \e[00m Font \"" + file + "\" not found.");
                continue ;
            }
            events->send<std::string>("\e[32m ☑ \e[00m Texture \"" + file + "\" loaded.");
            _textures[file] = texture;
        }
        
        for (auto file : Font) {
            sf::Font font;
            if (!font.loadFromFile(file)) {
                events->send<std::string>("\e[31m ☒ \e[00m Font \"" + file + "\" not found.");
                continue ;
            }
            events->send<std::string>("\e[32m ☑ \e[00m Font \"" + file + "\" loaded.");
            _fonts[file] = font;
        }

        phase = Run;
    }

    void AssetLoader::run(float) {
        switch (phase)
        {
            case Init: return init();
            case Run: return ;
        }
    }
}
