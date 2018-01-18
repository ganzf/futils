//
// Created by clara on 1/12/18.
//

#include <regex>
#include <dirent.h>
#include "AssetLoader.hpp"

namespace fender::systems::SFMLSystems
{
    void AssetLoader::init() {
        __init();
        //TODO: Dans image et text system-> send ce packet et attendre la réponse avant de se run
        addReaction<RequestAssets>([this](futils::IMediatorPacket &){
                AssetsLoaded assets;
                assets.fonts = &_fonts;
                assets.textures = &_textures;
                events->send<AssetsLoaded>(assets);
        });

        std::regex patternTexture { ".*.[png|jpg|jpeg]" };
        std::regex patternFont { ".*.ttf" };

        DIR *dir = opendir("ressources/");
        struct dirent *file;
        std::string pathFile;

        while ((file = readdir(dir))) {
            pathFile = "ressources/";
            pathFile += file->d_name;

            if (std::regex_match(file->d_name, patternTexture)) {
                sf::Texture texture;
                if (!texture.loadFromFile(pathFile)) {
                    //events->send<std::string>("Texture " + file->d_name + " not found.");
                    continue;
                }
                std::cout << "Texture " << file->d_name << " loaded." << std::endl;
                _textures[file->d_name] = texture;
            }
            else if (std::regex_match(file->d_name, patternFont))
            {
                sf::Font font;
                if (!font.loadFromFile(pathFile)) {
                    //events->send<std::string>("\e[31m ☒ \e[00m Font \"" + file->d_name + "\" not found.");
                    continue;
                }
                std::cout << "Font " << file->d_name << " loaded." << std::endl;
                _fonts[file->d_name] = font;
            }

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
