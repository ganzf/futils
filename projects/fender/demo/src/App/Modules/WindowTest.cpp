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
#include "Entities/ListView.hpp"

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

        auto text = &entityManager->create<fender::entities::Text>(world.name);

        auto &gui = camera->get<fender::components::Children>();
        gui.add(*text);

        auto list = &entityManager->create<fender::entities::ListView>();

        auto &myMenu = list->get<fender::components::ListView>();
        gui.add(*list);
        myMenu.order = futils::Ordering::Vertical;

        auto &listHover = list->attach<fender::components::Hoverable>();
        listHover.onEnter = [list](){
            auto &listBorder = list->get<fender::components::Border>();
            listBorder.visible = true;
            listBorder.color = futils::White;
        };
        listHover.onLeave = [list](){
            auto &listBorder = list->get<fender::components::Border>();
            listBorder.visible = false;
            listBorder.color = futils::White;
        };

        auto &myMenuBorder = list->get<fender::components::Border>();
        myMenuBorder.visible = false;

        auto &myMenuPos = list->get<fender::components::ChildInfo>();
        myMenuPos.offset.x = 33;
        myMenuPos.offset.y = 33;

        auto someText1 = &entityManager->create<fender::entities::Text>("Project Elixia");
        auto &someText1Transform = someText1->get<fender::components::Transform>();
        someText1Transform.size.w = 8;
        someText1Transform.size.h = 1;
        auto &someText1Border = someText1->get<fender::components::Border>();
        someText1Border.visible = false;

        auto someText2 = &entityManager->create<fender::entities::Text>("v0.1 - Alpha");
        auto &someText2Transform = someText2->get<fender::components::Transform>();
        someText2Transform.size.w = 4;
        someText2Transform.size.h = 1;
        auto &someText2Border = someText2->get<fender::components::Border>();
        someText2Border.visible = false;

        myMenu.content.push_back(someText1);
        myMenu.content.push_back(someText2);

        auto &txtTransform = text->get<fender::components::ChildInfo>();
        txtTransform.offset.x = 80;
        txtTransform.offset.y = 90;

//        auto image = &entityManager->create<fender::entities::Image>();
//        myMenu.content.push_back(image);
//        auto &imgTransform = image->get<fender::components::Transform>();
//        auto &imgBorder = image->get<fender::components::Border>();
//        auto &img = image->get<fender::components::Image>();
//
//        imgBorder.visible = false;
//        imgBorder.color = futils::Darkslateblue;
//        imgTransform.position.x = 0;
//        imgTransform.position.y = 0;
//        imgTransform.size.x = 1;
//        imgTransform.size.y = 1;
//        img.file = "ressources/poulpi.png";

        auto button = &entityManager->create<fender::entities::Button>();
        myMenu.content.push_back(button);
        auto &buttTransform = button->get<fender::components::Transform>();
        auto &buttBorder = button->get<fender::components::Border>();
        auto &buttImage = button->get<fender::components::Image>();
        auto &buttText = button->get<fender::components::Text>();
        auto &buttClick = button->get<fender::components::Clickable>();

        auto &buttColor = button->attach<fender::components::Color>();
        buttColor.color = futils::Violetred;

        buttBorder.visible = false;
        buttTransform.position.x = -2;
        buttTransform.position.y = -2;
        buttTransform.size.x = 4;
        buttTransform.size.y = 1;
        buttImage.file = "ressources/button.png";

        buttText.style.size = 24;
        buttText.style.color = futils::Antiquewhite;
        buttText.style.font = "ressources/arial.ttf";
        buttText.str = "           - Quit - ";

        buttClick.waitForRelease = true;
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
