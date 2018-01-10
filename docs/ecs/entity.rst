class futils::IEntity
=====================

.. code-block:: cpp

   class   IEntity
   {
    public:
        IEntity();
        virtual ~IEntity() {}

        template    <typename Compo, typename ...Args>
        Compo       &attach(Args ...args);

        template <typename T>
        T &get() const

        template <typename Compo>
        bool detach()

        int         getId() const
    };

attach<T>
---------

Builds and adds a component to the entity.

.. code-block:: cpp

   entity->attach<components::Color>(futils::Granite);
   entity->attach<gameplay::components::Alive>("The Rock", 50);

get<T>
------

Get a reference to the component T held by the entity.
**Throws std::runtime_error** if not found.

.. code-block:: cpp

   auto &color = entity->get<components::Color>();
   color.color = futils::White;

detach<T>
---------
Remove and destroy component of type T held by the entity.
Returns **true** if detached, **false** otherwise.
