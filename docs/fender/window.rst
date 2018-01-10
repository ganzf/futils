Opening a Window
================

Now that you know the basics (**creating and adding a system**, **sending and receiving events**), let's see what you can do with the engine.
Since this engine is targeted at developers, it requires you to create everything, starting with the window.

First step
----------

Remember, we want to create a simple snake game. We're gonna create a Snake system.

.. code-block:: cpp

   # include "Entities/Window.hpp"

   class Snake : public futils::ISystem
   {
                fender::entities::Window *myWindow{nullptr};
                void init();
   public:
                Snake() = default;
                void run(float) final;
   }

   void Snake::run(float)
   {
     static int phase = 0;
     switch(phase) {
       case 0:
                phase = 1;
                return init();
       case 1:
                return ;
     }
   }

   void Snake::init()
   {
     myWindow = &entityManager->create<fender::entities::Window>();
     auto &winComponent = myWindow.get<fender::components::Window>();
     if (!winComponent.isOpen) {
       win.visible = true;
       win.title = "Snake";
       win.size.w = 800; // in px
       win.size.h = 600; // in px
     }
     addReaction<Shutdown>([this](futils::IMediatorPacket &)
     {
       this->entityManager->removeSystem(this->name);
     });
   }

Let's take some time to understand this bit of code. First, you should know that if you compile and run, it will only open a window and display a black background.
But it's a start !

.. code-block:: cpp

   fender::entities::Window *myWindow{nullptr};

I'm holding a **pointer** to entity because I need to **create** the entity with the **entityManager**.

.. code-block:: cpp
   :emphasize-lines: 3,4

   void Snake::run(float)
   {
     static int phase = 0;
     switch(phase) {
       case 0:
                phase = 1;
                return init();
       case 1:
                return ;
     }
   }

I'm using a static int to switch **states** : i'll initialize once and then forever just return.
