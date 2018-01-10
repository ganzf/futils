class futils::IComponent
========================

.. code-block:: cpp
   :linenos:

    class   IComponent
    {
    public:
        virtual ~IComponent() {}

        IEntity &getEntity() const
        {
            return *__entity;
        }
    };

IEntity &getEntity()
--------------------

This is the only function you should care about. It returns a reference to the pointer.
