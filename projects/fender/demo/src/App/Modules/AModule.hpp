//
// Created by arroganz on 1/23/18.
//

#ifndef DEMO_AMODULE_HPP
#define DEMO_AMODULE_HPP

# include "rendering.hpp"
# include "events.hpp"
# include "ecs.hpp"

# include "Entities/Window.hpp"
# include "Entities/Camera.hpp"
# include "Entities/World.hpp"
# include "Entities/Image.hpp"
# include "Entities/Input.hpp"
# include "Entities/ListView.hpp"
# include "Entities/TextBox.hpp"
# include "Entities/InputField.hpp"
# include "Components/rigidBody.hpp"

namespace demo
{
    using Window = fender::entities::Window;
    using Camera = fender::entities::Camera;
    using World = fender::entities::World;
    using Input = fender::entities::Input;
    using ListView = fender::entities::ListView;
    using TextBox = fender::entities::TextBox;
    using Text = fender::entities::Text;
}

namespace demo::systems
{
    /*
     * AModule is a abstract intermediate class between concrete demo::Modules
     * and futils::ISystem
     *
     * It implements a common _init() function and sets a default afterBuild lambda
     * for initialization. If a system overrides this lambda, it must call _init().
     *
     * It also encapsulates States, for any system can run in different states.
     * Transitions are not handled here. But they could.
     */
    class AModule : public futils::ISystem
    {
    protected:
        int state{0};

        void _init()
        {
            addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
                entityManager->removeSystem(name);
            });
        }
    public:
        AModule(std::string const &name)
        {
            this->name = name;
            afterBuild = [this](){
                _init();
            };
        }
        void run(float) override = 0;
    };
}

#endif //DEMO_AMODULE_HPP
