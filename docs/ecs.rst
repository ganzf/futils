EntiyComponentSystem explained
==============================

Disclaimer : This is not actual working code, this is only intended to help you understand the underlying design of the engine.

-----

The ECS is a design pattern used to favor **composition** over inheritance. You create entities, that are composed of components (most often Plain Old Data) and meaningful output is done through the systems in a regular (systemic) way.

For example, here is a Window :

.. code-block:: cpp
   :linenos:
   :emphasize-lines: 1, 4

   class Window : public Entity
   {
                Window(string name, string icon = "defaultIcon.ico") {
                     attach<WindowComponent>(name, icon);
                }
   };

As you can see it is an entity (```public Entity```) composed of a WindowComponent component (```attach<WindowComponent>```) that holds the name of our Window, and a path to an icon.

Using the EntityManager (the glue that makes everything work in a magical way) we create a window:

.. code-block:: c

   entityManager->create<Window>("Demo");


And thus a Window is born with the name ```Demo```, and the engine is notified.

.. rst-class:: fa fa-question fa-2x

   > But wait... what happened ?

Well, Fender actually already loaded a system to handle ```WindowComponents``` named... ```Window```.

When the EntityManager creates a ```Window```, it knows its going to be composed of a ```Window```. It will emit an event ```ComponentAttached<Window>``` and the ```Window System``` will catch that event and create an actual Window. (An SFML Window for example).

Now you should keep the return value of the ```create<T>``` function. Say we want to change the name of our window.

.. code-block:: c

   auto &win = entityManager->create<Window>("Demo")
   auto &window = win.get<Window>();
   window.name = "Awesome";

Since ```window``` 's name is now "Awesome", the ```Window System``` will now display "Awesome".

What if you want to add a background color to your Window ?

.. code-block:: c

   auto &bg = win.attach<Color>();
   bg = Granite;

or

.. code-block:: c

   auto &bg = win.attach<Color>(Granite);


Now the ```Window System``` will know the window has a ```Color Component``` and will update the window with a Granite like background.

You want to remove the background ?

.. code-block:: c

   win.detach<Color>();

And we're back to a normal window with a black background color;

For now, there is no error checking.

.. rst-class:: fa fa-question fa-2x

   > What errors ?


By error, I mean what if you attached a component to an entity but it made no sense ? 

.. code-block:: c

   win.attach<onFire>();


Well, it will work. But it won't have any impact. If you want to know more about how components affect your program, you can read either the documentation or the source code of the systems. Beware what components you put together though, some combinations might not work as you'd expect, or work at all.

If you want to know what the actual fender-ecs classes look like, follow these links :

.. toctree::
   :maxdepth: 2

   ecs/entitymanager
   ecs/entity
   ecs/component
   ecs/system

