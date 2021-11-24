.. .. image:: https://travis-ci.com/stemoretti/qt-desktop-template.svg?branch=master
  :target: https://travis-ci.com/stemoretti/qt-desktop-template

.. image:: https://github.com/stemoretti/qt-desktop-template/workflows/AppImage/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3AAppImage

.. image:: https://github.com/stemoretti/qt-desktop-template/workflows/Windows/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3AWindows

.. image:: https://github.com/stemoretti/qt-desktop-template/workflows/MacOS/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3AMacOS

.. image:: https://github.com/stemoretti/qt-desktop-template/workflows/Tests/badge.svg
  :target: https://github.com/stemoretti/qt-desktop-template/actions?query=workflow%3ATests

Qt Desktop Template
===================

Template for creating applications for Linux, Windows and MacOS with
the Qt Widgets framework.

How to build
------------

Requirements
^^^^^^^^^^^^

The following software is required to compile this application:

* A compiler that supports C++11
* CMake >= 3.10
* Qt >= 5.12

Compiling and installing under Linux or MacOS
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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

It's easier to compile the program using an IDE such as the Qt Creator.
Instructions on how to download and install it can be found
`here <https://doc.qt.io/qt-5/gettingstarted.html>`__.
Information on how to use it to build and run programs can be found
`here <https://doc.qt.io/qtcreator/index.html>`__.

Translations
------------

Translations are stored in ``.ts`` files inside the ``translation`` folder.
Their name contains the language code of the translation they provide.

To add languages, follow the steps below.

* Append the language codes you wish to support to the variable ``LANGUAGES``
  inside the file ``src/CMakeLists.txt``.

* Configure the project by running CMake.

* If you are using Qt5, you can either generate the ``.ts`` file of a specific
  language with the command:

  .. code:: console

    make ts_qt-desktop-template_[your language code]

  or generate all of them with the command:

  .. code:: console

    make ts_files_update

  If, instead, you are using Qt6, run the following command to generate the
  ``.ts`` file of each language:

  .. code:: console

    make update_translations

* Open the newly created file with the Qt tool ``linguist``.
  Translate the program's texts and save the file.

The binary translation files will be created automatically during the compilation.

Credits
-------

Software used for CI deployment:

* `aqtinstall <https://github.com/miurahr/aqtinstall>`__

* `install-qt-action <https://github.com/jurplel/install-qt-action>`__

* `linuxdeployqt <https://github.com/probonopd/linuxdeployqt>`__

See also
--------

Other similar templates:

* `QtApp-Template <https://github.com/alex-spataru/QtApp-Template>`__

* `mini-cmake-qt <https://github.com/euler0/mini-cmake-qt>`__

* `cmake-init <https://github.com/cginternals/cmake-init>`__

* `cpp_starter_project <https://github.com/cpp-best-practices/cpp_starter_project>`__
