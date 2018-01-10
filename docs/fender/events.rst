Fender events
=============

One thing that's quite cool about fender is that it makes sharing information between different systems easy.
You can **send** events to notify others and **require** events to bind an anoymous lambda function to any type.

This is done through the use of the ``events`` variable that any system will have.
Note that you must create your system through a call to ``addSystem<T>(...)`` for the ``events`` variable to be set.

For now, only synchronous events are supported.
Soon however, asynchronous tasks may be scheduled.

.. code-block:: cpp

   class Mediator
   {
   public:
        template <typename T>
        static inline const T &rebuild(IMediatorPacket &pkg);

        template <typename T>
        void send(T &&data = T());

        template <typename T>
        void send (T const &data);

        template <typename T>
        void require(void *callee, std::function<void(futils::IMediatorPacket &)> onReceive);

        template <typename T>
        void forget(void *callee);

        void erase(void *callee);
    };

T &rebuild<T>(IMediatorPacket &)
--------------------------------

This function will extract the data of type T hidden inside the IMediatorPacket.
If there is a type mismatch (requested a type A in a packet that holds a type B) an **std::logic_error** will be thrown.

send<T const &>()
-----------------

This function sends an event of type T constructed from an lvalue.

.. code-block:: cpp

   TextMessage message;

   message.text = "Hello World !";
   events->send<TextMessage>(message);

Here, message is an lvalue.

send<T &&>()
-----------------

This function sends an event of type T constructed from an rvalue.

.. code-block:: cpp

   events->send<std::string>("Hello World!");

Here, the type is std::string and we're giving an rvalue to the send function.

require<T>()
------------

This function binds a lambda function to a type in the event system.

.. code-block:: cpp

   events->require<std::string>(this, [this](futils::IMediatorPacket &pkg){
                auto &str = futils::Mediator::rebuild<std::string>(pkg);
                std::cout << "Received a string : " << str << std::endl;
   });

This is **the only way** you should get events, rebuild their concrete type and use them.

forget<T>()
-----------

If you want to stop reacting to some events, or you want to change the binded function you need to call forget<T>.

.. code-block:: cpp

   events->forget<std::string>(this);

erase()
-------

If you want to forget all events, simply call ``erase(this)``.
