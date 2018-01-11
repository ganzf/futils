Creating a world
================

Its nice to have a window... but right now there's just nothing to show.
What you need to do is create a **World** entity.

What's a World ?
----------------

The World Entity specifies two important things

 - How big is it ?
 - How many pixels per square ?

For our Snake game, we'll make the world a 16x16 square world.
And following tilemap conventions, a square will be 32x32 pixels.

Therefore our Game systems will now look like this :

.. code-block:: cpp
   :emphasize-lines: 6

   namespace Snake
   {
      class Game : public futils::ISystem
      {
        fender::entities::Window *myWindow{nullptr};
        fender::entities::World *myWorld{nullptr};
        
        void init();
      public:
        Game() {
          name = "Game";
        }

        virtual ~Game() {}
        virtual void run(float);
      };
   }

And the Init function will now init ``myWorld``

.. code-block:: cpp

   myWorld = &entityManager->create<fender::entities::World>();
   auto &worldComponent = myWorld->get<fender::components::World>();
   worldComponent.name = "SnakeWorld";
   worldComponent.unit = 32;
   worldComponent.size.w = 16;
   worldComponent.size.h = 16;

As you can see, simply created the World entity, and initialized its World component.
