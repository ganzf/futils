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
