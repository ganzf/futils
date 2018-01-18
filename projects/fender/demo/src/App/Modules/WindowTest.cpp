//
// Created by arroganz on 1/1/18.
//

#include <Components/rigidBody.hpp>
#include "WindowTest.hpp"
#include "Components/Color.hpp"
#include "Components/World.hpp"
#include "Entities/Image.hpp"
#include "Entities/Text.hpp"
#include "Entities/Button.hpp"
#include "inputKeys.hpp"
#include "Entities/ListView.hpp"
#include "Entities/InputField.hpp"
#include "Entities/TextBox.hpp"

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
        win.size.h = 768;
        win.position.x = 0;
        win.position.y = 0;
        win.visible = true;
        win.style = futils::WStyle::Default;
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
        cam.debugMode = false;

        auto text = &entityManager->create<fender::entities::Text>(world.name);

        auto &gui = camera->get<fender::components::Children>();
        gui.add(*text);

        auto list = &entityManager->create<fender::entities::ListView>();

        auto &myMenu = list->get<fender::components::ListView>();
        myMenu.name = "MainMenu";
        gui.add(*list);
        myMenu.order = futils::Ordering::Vertical;

//        auto &listHover = list->attach<fender::components::Hoverable>();
//        listHover.onEnter = [list](){
//            auto &listBorder = list->get<fender::components::Border>();
//            listBorder.visible = true;
//            listBorder.color = futils::White;
//        };
//        listHover.onLeave = [list](){
//            auto &listBorder = list->get<fender::components::Border>();
//            listBorder.visible = false;
//            listBorder.color = futils::White;
//        };

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
        addReaction<futils::Keys>([this, someText1](futils::IMediatorPacket &pkg){
            auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
            if (key == futils::Keys::Q) {
                auto &txt = someText1->get<fender::components::Text>();
                auto &_camPos = camera->get<fender::components::Transform>();
                txt.str = "Cam (" + std::to_string(_camPos.position.x) + ", "
                        + std::to_string(_camPos.position.y) + ", "
                        + std::to_string(_camPos.position.z) + ")";
            }
        });
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
        buttText.str = "SendText";
        buttClick.waitForRelease = true;

        auto &listClick = list->attach<fender::components::Clickable>();
        auto rigid = &entityManager->create<fender::entities::GameObject>();
        auto &rigidBorder = rigid->get<fender::components::Border>();
        rigidBorder.visible = true;
        rigidBorder.color = futils::Sandybrown;
        rigidBorder.thickness = 3;
        auto &rigidPos = rigid->get<fender::components::Transform>();
        rigidPos.position.x = 0;
        rigidPos.position.y = 0;
        rigidPos.size.w = 1;
        rigidPos.size.h = 1;

        rigid->attach<fender::components::rigidBody>();
        listClick.func = [this, rigid](){
            auto &body = rigid->get<fender::components::rigidBody>();
            body.force.y = -1;
            body.force.x = 0;
            body.weight = 1;
        };

        auto in = &entityManager->create<fender::entities::InputField>("placeholder");
        auto &inT = in->get<fender::components::Transform>();
        inT.size.w = 3;
        inT.size.h = 0.55;
        auto &editable = in->get<fender::components::Editable>();

        auto &editableText = in->get<fender::components::Text>();
        editableText.style.size = 22;
        editableText.style.color = futils::Palevioletred;
        editableText.style.font = "ressources/arial.ttf";

        auto &inBorder = in->get<fender::components::Border>();
        inBorder.thickness = 3;
        inBorder.color = futils::Lightskyblue;
        inBorder.visible = false;
        inBorder.up = false;
        inBorder.left = false;
        inBorder.right = false;
        myMenu.content.push_back(in);

        editable.onFocus = [this, &inBorder](){
            inBorder.visible = true;
        };
        editable.onFocusLost = [this, &inBorder](){
            inBorder.visible = false;
        };

        auto *txtBox = &entityManager->create<fender::entities::TextBox>(2, false);
        // gui.add(*txtBox);
        auto &txtBox_transform = txtBox->get<fender::components::Transform>();
        txtBox_transform.size.w = 4;
        txtBox_transform.size.h = 4;
//        auto &txtBox_childInfo = txtBox->get<fender::components::ChildInfo>();
//        txtBox_childInfo.offset.x = 2;
//        txtBox_childInfo.offset.y = 2;
        auto &txtBox_border = txtBox->get<fender::components::Border>();
        txtBox_border.visible = false;
        txtBox_border.up = true;
        txtBox_border.down = true;
        txtBox_border.left = true;
        txtBox_border.right = true;
        txtBox_border.thickness = 1;
        txtBox_border.color = futils::Cobaltgreen;

        auto *txtBoxScroll = &entityManager->create<fender::entities::TextBox>(4, true);
        // gui.add(*txtBoxScroll);
        auto &txtBoxScroll_transform = txtBoxScroll->get<fender::components::Transform>();
        txtBoxScroll_transform.size.w = 4;
        txtBoxScroll_transform.size.h = 2;
//        auto &txtBoxScroll_childInfo = txtBoxScroll->get<fender::components::ChildInfo>();
//        txtBoxScroll_childInfo.offset.x = 2;
//        txtBoxScroll_childInfo.offset.y = 30;
        auto &txtBoxScroll_border = txtBoxScroll->get<fender::components::Border>();
        txtBoxScroll_border.visible = false;
        txtBoxScroll_border.up = true;
        txtBoxScroll_border.down = true;
        txtBoxScroll_border.left = true;
        txtBoxScroll_border.right = true;
        txtBoxScroll_border.thickness = 1;
        txtBoxScroll_border.color = futils::Cobaltgreen;

        buttClick.func = [this, in, txtBox, txtBoxScroll, &editableText]() {
            *txtBox << 12 << "Debug : " << editableText.str << futils::endl;
            *txtBoxScroll << 10 << "Debug Scroll : " << editableText.str << futils::endl;
        };

        auto debug = &entityManager->create<fender::entities::ListView>();
        auto &debugTr = debug->get<fender::components::Transform>();
        debugTr.size.w = 5;
        debugTr.size.h = 2;
        auto &debugContent = debug->get<fender::components::ListView>();
        debugContent.order = futils::Ordering::Vertical;
        debugContent.name = "Debug";
        debugContent.content.push_back(txtBox);
        debugContent.content.push_back(txtBoxScroll);
        debugContent.fit = true;
        gui.add(*debug);
        auto &debugPos = debug->get<fender::components::ChildInfo>();
        debugPos.offset.x = 5;
        debugPos.offset.y = 10;
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
        std::cout << "Cam found" << std::endl;
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
        futils::IntegralRange<int> zrng(1, 3);
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
