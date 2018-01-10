Installing fender
=================

Fender is a cross-platform (windows, linux, [WIP]osx) static library in c++.

Dependency
----------

Linux
~~~~~

On Linux, you'll need to install the latest version of the SFML (if you intend to use the SFML).

Windows
~~~~~~~

You should not have anything special to do on Windows regarding the SFML.

Download
--------

.. code-block:: bash

   $ git clone git@github.com:/ganzf/futils.git

Creating a project
------------------

Now that you've cloned the repository, you can go to ``futils/projects/fender``

.. code-block:: bash

   $ cd futils/projects/fender

And copy both ``createFenderProject.sh`` and ``fenderGettingStarted`` directory.

Use the script next to the directory to create a new directory.

.. code-block:: bash

   $ ./createFenderProject.sh MyProjectName

This will create a directory named MyProjectName and update the CMakeLists.txt to build an executable of the same name.

Build
-----

.. code-block:: bash

   $ cd MyProjectName
   $ ./all.sh
   $  - Downloading futils...
   $ Cloning into '.dl_futils'...
   $ remote: Counting objects: 536, done.
   $ remote: Compressing objects: 100% (329/329), done.
   $ remote: Total 536 (delta 147), reused 518 (delta 143), pack-reused 0
   $ Receiving objects: 100% (536/536), 15.64 MiB | 496.00 KiB/s, done.
   $ Resolving deltas: 100% (147/147), done.
   $  - Done.
   $ Fetching update...
   $ From github.com:ganzf/futils
   $  * branch            master     -> FETCH_HEAD
   $ Already up to date.
   $ Update complete.
   $ -- The C compiler identification is GNU 7.2.0
   $ -- The CXX compiler identification is GNU 7.2.0
   $ -- Check for working C compiler: /usr/bin/cc
   $ -- Check for working C compiler: /usr/bin/cc -- works
   $ -- Detecting C compiler ABI info
   $ -- Detecting C compiler ABI info - done
   $ -- Detecting C compile features
   $ -- Detecting C compile features - done
   $ -- Check for working CXX compiler: /usr/bin/c++
   $ -- Check for working CXX compiler: /usr/bin/c++ -- works
   $ -- Detecting CXX compiler ABI info
   $ -- Detecting CXX compiler ABI info - done
   $ -- Detecting CXX compile features
   $ -- Detecting CXX compile features - done
   $ -- Configuring done
   $ -- Generating done
   $ -- Build files have been written to: /home/arroganz/cpp/MyProjectName/build
   $ Scanning dependencies of target MyProjectName
   $ [ 50%] Building CXX object CMakeFiles/MyProjectName.dir/src/main.cpp.o
   $ [100%] Linking CXX executable ../MyProjectName
   $ [100%] Built target MyProjectName
   $ [100%] Built target MyProjectName

Update
------

Use the update.sh script to fetch new stable versions of the library.

