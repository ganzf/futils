Getting Started with Fender
===========================

Since you cloned the repository, you can use the shell script ``getStarted projectName``.

It will create the following architecture :

.. code-block:: bash

   gettingStarted
   |- all.sh
   |- update.sh
   |- build.sh
   |- compile.sh
   |- CMakeLists.txt
   |- doc/
   |- futils/
   |- include/
   |- lib/
   |- src/
   |- Readme.md

Use ``update.sh`` to fetch the latest Fender build and includes.
Use ``build.sh`` on Unix to build the project
Use ``compile.sh`` to create a binary executable file.
Use ``all.sh`` for all of the above.

.. rst-class:: fa fa-warning

   > The update.sh script will clone futils in a hidden folder.

Creating and adding your systems
--------------------------------

In the newly created directory, you'll find basic main.cpp

.. code-block:: cpp

   # include "fender.hpp"

   int main(int, char **av)
   {
                fender::Fender engine(av[0]);

                if (engine.start() != 0)
                  return 1;
                engine.run();
                return 0;
   }

This is a minimal working usage of the engine. Default systems will be loaded (by default it loads the SFMLSystems).
If you want to add your own systems, here's where you should do it.

.. code-block:: cpp

   # include "fender.hpp"
   # include "mySystem.hpp"

   // mySystem.hpp
   class mySystem : public futils::ISystem
   {
                (...)
   public:
                mySystem(bool someValue);
                void run(float) override;
   };

   int main(int, char **av)
   {
                fender::Fender engine(av[0]);

                if (engine.start() != 0)
                  return 1;
                engine.addSystem<mySystem>(true);
                engine.run();
                return 0;
                
   }

.. rst-class:: fa fa-warning fa-2x

   > Do not add your systems before you call ``engine.start()``

If everything goes well, here's what you could see

.. code-block:: bash

   -->     LOG => [Window] loaded.
   -->     LOG => [Input] loaded.
   -->     LOG => [Camera] loaded.
   -->     LOG => [Grid] loaded.
   -->     LOG => [Children] loaded.
   -->     LOG => [Border] loaded.
   -->     LOG => [mySystem] loaded.
