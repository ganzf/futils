class futils::ISystem
=====================

.. code-block:: c

   class   ISystem
   {
    protected:
        std::string name{"Undefined"};
        EntityManager *entityManager{nullptr};
        Mediator *events{nullptr};
        std::function<void(EntityManager *)> afterDeath{[](EntityManager *){}};

        template <typename T>
        void addReaction(std::function<void(IMediatorPacket &pkg)> fun);
    public:
        virtual ~ISystem() {}
        virtual void run(float elapsed = 0) = 0;

        // You should not use these functions (they'll be friend of EntityManager soon)
        // {
        void provideManager(EntityManager &manager) { entityManager = &manager; }
        void provideMediator(Mediator &mediator) { events = &mediator; }
        std::string const &getName() const { return name; }
        std::function<void(EntityManager *)> getAfterDeath();
        // }
    };

protected: void addReaction<T>
------------------------------

**Protected** addReaction binds the `fun` lambda to the event T.
Be careful not to call this function in your system constructor, as ``events`` will be nullptr.

.. code-block:: cpp

   addReaction<SomeEvent>([this](futils::IMediatorPacket &pkg){
                auto &packet = futils::Mediator::rebuild<SomeEvent>(pkg);
                (...)
   });

protected: name
---------------

Systems all have a name, and should be **unique**.

protected: entityManager
------------------------

The entityManager pointer will be set by the entityManager itself when calling ``entityManager->addSystem<T>()``

protected: events
-----------------

The events pointer will be set by the entityManager itself when calling ``entityManager->addSystem<T>()``

protected: afterDeath
---------------------

This lambda allows you to specify a behavior after you've deleted your system.

.. rst-class:: fa fa-warning fa-2x

   > Do not capture **this** in your afterDeath function. It will be a dangling pointer.

virtual void run(float elapsed)
-------------------------------

This pure method is the basic function of any system. You can implement whatever you like.
The `elapsed` parameter describes in milliseconds the time elapsed from previous run. It highly depends on the number of systems in the engine and you **must** use it. Otherwise your system may run too fast or too slow.
If you have question see FluidTimestep_

.. _FluidTimestep: http://gameprogrammingpatterns.com/game-loop.html
