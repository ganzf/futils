Fender
======

.. rst-class:: fa fa-file-text-o

    \- Defined in ``fender.hpp``

It all starts with ``fender::Fender``.

Here's what it looks like :

.. code-block:: cpp

   class Fender
   {
   public:
        Fender(std::string const &av_0);

        int start();
        int run();

        template <typename System, typename ...Args>
        void addSystem(Args ...args);

		    template <typename System>
		    void addSystem();
		    
        template <typename System>
        void removeSystem();
    };

Fender(string const &)
----------------------

Fender requires ``std::string const &`` to ``av[0]`` in order to make all relative paths work properly.

int start()
-----------

Starting the engine is the second function call you should make. It will let the engine initialize itself.
Right after starting the engine, you can add your own systems.

addSystem<T>(...)
-----------------

Use this function to add your own systems after starting the engine.

removeSystem<T>
---------------

Use this function to remove a system (it can be one added by default, or your own).

Once you're set, simply run the engine.

int run()
---------

This function returns the engine status. You should call this function only once when you're all set.
