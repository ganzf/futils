class futils::EntityManager
===========================

.. code-block:: cpp

     class   EntityManager
    {
    public:
        EntityManager();

        template    <typename T, typename ...Args>
        T           &create(Args ...args);

        template    <typename System, typename ...Args>
        void        addSystem(Args ...args);

        void removeSystem(std::string const &systemName);

        template <typename T>
        std::vector<T *> get();

        bool        isFine();

        int getNumberOfSystems() const;

        int run();
    };

create<T>
---------

This function allows you to create a futils::IEntity with variable argument list and returns a reference to the newly created entity.

.. code-block:: cpp

   auto &thing = entityManager->create<Thing>(12, "lol", nullptr);

addSystem<T>
------------

This function allows you to create a futils::ISystem with variable argument list.

.. code-block:: cpp

   entityManager->addSystem<MySystem>(12, 13, 15);

get<T>
------

This function builds a vector of pointers to components of type T.

.. code-block:: cpp

   auto clickables = entityManager->get<Clickable>();
   for (auto &clickable: clickables)
   (...)


.. rst-class:: fa fa-warning fa-2x

   > You should always use ``create`` and ``addSystem`` to add entities or systems. Anything else results in **undefined behavior**
