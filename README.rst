Qt Desktop Template
===================

.. image:: https://travis-ci.com/stemoretti/qt-desktop-template.svg?branch=master
  :target: https://travis-ci.com/stemoretti/qt-desktop-template

A template for creating Qt Widgets desktop applications.

Installation from sources
-------------------------

Requirements
^^^^^^^^^^^^

The following software is required to compile this application:

* A compiler that supports C++11
* CMake >= 3.5
* Qt >= 5.9.0

Compiling and installing under Linux
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block:: console

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

Translations
------------

Translations can be added to the application by following the steps below.

* First, add languages you wish to support to the file ``translations/CMakeLists.txt``

* Configure the project by running CMake.

* Then either generate the specific ts file with

  .. code-block:: console

    make ts_qt-desktop-template_[your language code]

  or generate every translation file with

  .. code-block:: console

    make ts_files_update

* Open the newly created file with Qt5 ``linguist``,
  write the translation of the strings and save the file.

The binary translation files will be created automatically during the compilation.

Credits
-------

* These build scripts are based on
  `cmake-init <https://github.com/cginternals/cmake-init>`__
