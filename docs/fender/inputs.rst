Handling inputs
===============

Hum... You're right. It's all nice and well to render to the screen. But handling user input is just as important.

.. rst-class:: fa fa-exclamation fa-2x

   Check out the futils/inputKeys.hpp to know what events you can get.

The basics
----------

This code right here shows how to react to basic user inputs.

.. code-block:: cpp
   :emphasize-lines: 3             

   addReaction<futils::Keys>([this](){
     auto &key = futils::Mediator::rebuild<futils::Keys>(pkg);
     if (key == futils::Keys::Escape)
       events->send<fender::events::Shutdown>();
   });

**It's that simple**.

InputSequences (WIP)
--------------------

You can also require events in a more advanced way.

.. code-block:: cpp
   :emphasize-lines: 4, 12, 15

   input = &entityManager->create<fender::entities::Input>();
   auto &component = input->get<fender::components::Input>();
   component.name = "WindowTest";
   component.activated = true;
   futils::InputSequence escape;
   futils::InputAction action(futils::Keys::Escape, futils::InputState::Down);
   escape.actions.push_back(action);
   
   futils::InputSequence generate;
   futils::InputAction gen_action(futils::Keys::Space, futils::InputState::Down);
   generate.actions.push_back(gen_action);

   component.map[escape] = [this](){
                events->send<fender::events::Shutdown>();
   };
   component.map[generate] = [this](){
                createGo(*entityManager);
   };

You can create Input (an Entity) and get its (Input) to set bind together InputSequence (a collection of InputAction) and a lambda.
If you need more advanced input control, prefer this solution.
You may want to swap between different configurations of inputs, so all you'd have to do is ``send<InputSwitch>("WindowTest")``. # Not Implemented yet.
