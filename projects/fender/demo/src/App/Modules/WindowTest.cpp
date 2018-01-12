//
// Created by arroganz on 1/1/18.
//

#include "WindowTest.hpp"
#include "Components/Color.hpp"
#include "Components/World.hpp"
#include "Entities/Image.hpp"
#include "Entities/Text.hpp"
#include "Entities/Button.hpp"
#include "inputKeys.hpp"

void WindowTest::initWindow()
{
    addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
        auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
        if (key == futils::Keys::F)
        {
            auto worlds = entityManager->get<fender::components::World>();
            if (worlds.empty())
                return ;
            auto &world = worlds.front();
            world->unit += 16;
        }
        else if (key == futils::Keys::G)
        {
            auto worlds = entityManager->get<fender::components::World>();
            if (worlds.empty())
                return ;
            auto &world = worlds.front();
            world->unit -= 16;
        }
        else if (key == futils::Keys::D)
        {
            auto cameras = entityManager->get<fender::components::Camera>();
            for (auto &cam: cameras)
            {
                cam->debugMode = !cam->debugMode;
            }
        }
    });
    window = &entityManager->create<fender::entities::Window>();
    auto &win = window->get<fender::components::Window>();
    if (win.isOpen)
    {

    } else {
        win.size.w = 1024;
        win.size.h = 780;
        win.position.x = 0;
        win.position.y = 0;
        win.visible = true;
        win.style = futils::WStyle::None;
        auto &world = window->attach<fender::components::World>();
        world.unit = 64;
        world.name = "Project Elixia";
        win.title = world.name;
        world.size = fender::vec3f(100, 100, 100);
        auto &color = window->attach<fender::components::Color>();

        color.color = futils::Granite;
//        addReaction<futils::Keys>([this](futils::IMediatorPacket &pkg){
//           auto &key =  futils::Mediator::rebuild<futils::Keys>(pkg);
//            if (key == futils::Keys::Escape || key == futils::Keys::K)
//                events->send<fender::events::Shutdown>();
//        });
        addReaction<fender::events::Shutdown>([this](futils::IMediatorPacket &){
            entityManager->removeSystem(name);
        });

        camera = &entityManager->create<fender::entities::Camera>();
        auto &cam = camera->get<fender::components::Camera>();
        cam.window = window;
        cam.activated = true;
        cam.debugMode = true;

        auto text = &entityManager->create<fender::entities::Text>("Salut");
        auto &txtTransform = text->get<fender::components::Transform>();

        txtTransform.position.x = 3;
        txtTransform.position.y = 3;


        auto image = &entityManager->create<fender::entities::Image>();

        auto &imgTransform = image->get<fender::components::Transform>();
        auto &imgBorder = image->get<fender::components::Border>();
        auto &img = image->get<fender::components::Image>();

        imgBorder.visible = false;
        imgTransform.position.x = 0;
        imgTransform.position.y = 0;
        imgTransform.size.x = 1;
        imgTransform.size.y = 1;
        img.file = "ressources/poulpi.png";

        auto button = &entityManager->create<fender::entities::Button>();
        auto &buttTransform = button->get<fender::components::Transform>();
        auto &buttBorder = button->get<fender::components::Border>();
        auto &buttImage = button->get<fender::components::Image>();
        auto &buttText = button->get<fender::components::Text>();
        auto &buttClick = button->get<fender::components::Clickable>();

        buttBorder.visible = false;
        buttTransform.position.x = -2;
        buttTransform.position.y = -2;
        buttTransform.size.x = 1;
        buttTransform.size.y = 1;
        buttImage.file = "ressources/poulpi.png";

        buttText.style.size = 24;
        buttText.style.color = futils::White;
        buttText.style.font = "ressources/arial.ttf";
        buttText.str = "OUI";

        buttClick.func = [this]() {
            events->send<fender::events::Shutdown>();
        };
    }
}


void testGO(futils::EntityManager &em, int x, int y, int w, int h, int z, bool cam)
{
    auto &go = em.create<fender::entities::GameObject>();
    auto &border = go.get<fender::components::Border>();
    futils::IntegralRange<int> rng(0, futils::allColors.size());
    border.color = futils::allColors[rng.getRandom()];
    auto &pos = go.get<fender::components::Transform>();
    pos.position.x = x;
    pos.position.y = y;
    pos.position.z = z;
    pos.size.w = w;
    pos.size.h = h;
    if (cam)
    {
        auto camera = em.get<fender::components::Camera>();
        if (camera.empty())
            return ;
        std::cout << "Cam found"<< std::endl;
        auto &myCam = camera.front()->getEntity();
        auto &gui = myCam.get<fender::components::Children>();
        gui.add(go);
    }
}

void createGo(futils::EntityManager &em, bool cam = false)
{
    static int count = 0;
    for(auto i = 0; i<10; i++) {
        futils::IntegralRange<int> rng(-50, 50);
        futils::IntegralRange<int> zrng(1, 10);
        testGO(em, rng.getRandom(), rng.getRandom(), 1, 1,
               zrng.getRandom(), cam);
        count++;
        std::cout << count << std::endl;
    }
}


void WindowTest::initInputs()
{
    input = &entityManager->create<fender::entities::Input>();
    auto &component = input->get<fender::components::Input>();
    component.name = "WindowTest";
    component.activated = true;
    futils::InputSequence escape;
    futils::InputAction action(futils::Keys::Escape, futils::InputState::Down);
    escape.actions.push_back(action);

    futils::InputSequence generate;
    futils::InputAction gen_action(futils::Keys::Space, futils::InputState::Down);
    generate.actions.push_back(gen_action);
    component.map[escape] = [this](){
        events->send<fender::events::Shutdown>();
    };
    component.map[generate] = [this](){
        createGo(*entityManager);
    };
}
void WindowTest::run(float) {
    if (window == nullptr) {
        initWindow();
        initInputs();
    } else
    {
        static int i = 1;
        if (i == 0)
        {
            while (i < 10) {
                i++;
                createGo(*entityManager, true);
            }
        }
    }
}
