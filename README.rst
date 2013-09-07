.. image:: https://secure.travis-ci.org/sycy600/rslib.png

Reed-Solomon code library.

How to build
============

Get dependencies (script tailored for Ubuntu)::

    ./get_deps_ubuntu.sh

Create build directory::

    mkdir build
    cd build

Run ``cmake``::

    cmake ..

Testing
=======

Run unit tests::

    cd build
    make test

Run ``cpplint.py``::

    cd build
    make lint

Build project and do all checks (all-in-one)::

    ./check.sh

Documentation
=============

Generate documentation and check if there is some not
documented code::

    ./run_doxygen.sh
