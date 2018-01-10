Installing fender
=================

Fender is a cross-platform (windows, linux, [WIP]osx) static library in c++.

Abstract
--------

What you have to do is clone the repository, build the library and then you can copy it wherever you need to.

.. code-block:: bash

   $ git clone git@github.com:/ganzf/futils.git
   $ cd futils/projects/fender
   $ mkdir build
   $ cd build
   $ cmake ..
   $ make
   $ cd ..
   $ echo "Build complete - libfender.a is ready" && ls

