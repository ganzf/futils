//
// Created by arroganz on 1/25/18.
//

#include "Debug.hpp"

extern "C" futils::ISystem *build()
{
    return new Debug;
}

void Debug::init()
{
    addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
        entityManager->removeSystem(name);
    });
    fender::events::RequestCamera rc("Default", [this](fender::entities::Camera *cam){
        this->_cam = cam;
        state = this->_cam != nullptr ? 1 : 0;
        std::cout << "Recovered camera " << cam->get<fender::components::Camera>().name << std::endl;
    });
    std::cout << "Requesting camera ..." << std::endl;
    events->send<fender::events::RequestCamera>(rc);
    if (state == 1) {
        _box = &entityManager->smartCreate<fender::entities::TextBox>(1);
        auto &gui = _cam->get<fender::components::Children>();
        gui.add(*_box);
        auto &boxPos = _box->get<fender::components::ChildInfo>();
        boxPos.offset.x = 2.5;
        boxPos.offset.y = 2.5;
        boxPos.relSize.w = 10;
        boxPos.relSize.h = 5;
    }
}

void Debug::run(float) {
    switch (state) {
        case 0:
            return init();
        case 1:
            if (!_box)
                return ;
            std::string msg = "Cam: (" +
                              std::to_string(_cam->getPositionX()) + ", " +
                              std::to_string(_cam->getPositionY()) + ")";
            *_box << 12 << msg << futils::endl;
            return ;
    }
}