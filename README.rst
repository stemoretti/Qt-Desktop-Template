.. .. image:: https://travis-ci.com/stemoretti/qt-desktop-template.svg?branch=master
  :target: https://travis-ci.com/stemoretti/qt-desktop-template

.. image:: https://github.com/stemoretti/qt-desktop-template/actions/workflows/appimage.yml/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3AAppImage

.. image:: https://github.com/stemoretti/qt-desktop-template/actions/workflows/flatpak.yml/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3AFlatpak

.. image:: https://github.com/stemoretti/qt-desktop-template/actions/workflows/snap.yml/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3ASnap

.. image:: https://github.com/stemoretti/qt-desktop-template/actions/workflows/windows.yml/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3AWindows

.. image:: https://github.com/stemoretti/qt-desktop-template/actions/workflows/macos.yml/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3AMacOS

Qt Desktop Template
===================

Template for creating applications for Linux, Windows and macOS with
the Qt Widgets framework.

How to build
------------

Requirements
^^^^^^^^^^^^

The following software is required to compile this application:

* A compiler that supports C++17
* CMake >= 3.19
* Qt >= 6.2

Compiling and installing under Linux
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code:: console

  git clone https://github.com/stemoretti/qt-desktop-template.git
  cd qt-desktop-template
  mkdir build
  cd build
  cmake ..
  make
  make install

The default CMake installation prefix is ``/usr/local``. You can change it by
redefining the option CMAKE_INSTALL_PREFIX in the configuration stage.
(e.g. ``cmake -DCMAKE_INSTALL_PREFIX=/usr ..``)

Compiling and running under Windows
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Clone the repository with git software like `Github Desktop <https://desktop.github.com/>`__.

It's easier to compile the program using an IDE such as Qt Creator.
Instructions on how to download and install it can be found
`here <https://doc.qt.io/qt-6/qt-intro.html>`__.
Information on how to use it to build and run programs can be found
`here <https://doc.qt.io/qtcreator/index.html>`__.

Compiling and creating a bundle under macOS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code:: console

  git clone https://github.com/stemoretti/qt-desktop-template.git
  cd qt-desktop-template
  cmake -B build -G "Ninja"
  cmake --build build

The bundle directory is automatically created inside the build directory.
However, it doesn't contain the libraries that the program needs to run.
To deploy the required Qt libraries into the bundle, run the following command.

.. code:: console

  macdeployqt "Qt Desktop Template.app" [-dmg]

The optional `-dmg` option is for creating a dmg disk image file.

Translations
------------

Translations are stored in ``.ts`` files inside the ``translations`` folder.
Their name contains the language code of the translation they provide.

To add languages, follow the steps below.

* Add the translation's file path of the language you wish to support to the
  variable ``TS_FILES`` inside the file
  `CMakeLists.txt <https://github.com/stemoretti/qt-desktop-template/blob/master/CMakeLists.txt#L107>`__.

* Configure the project by running CMake.

* Run the following command to generate the ``.ts`` file of each language:

  .. code:: console

    make update_translations

* Open the newly created file with the Qt tool ``linguist``.
  Translate the program's texts and save the file.

The binary translation files will be created automatically during the compilation.

Credits
-------

Software used for CI deployment:

* `aqtinstall <https://github.com/miurahr/aqtinstall>`__

* `linuxdeployqt <https://github.com/probonopd/linuxdeployqt>`__

See also
--------

Other similar templates:

* `QtApp-Template <https://github.com/alex-spataru/QtApp-Template>`__

* `mini-cmake-qt <https://github.com/euler0/mini-cmake-qt>`__

* `cmake-init <https://github.com/cginternals/cmake-init>`__

* `cpp_starter_project <https://github.com/cpp-best-practices/cpp_starter_project>`__
