Reed-Solomon code library.

Basics
======

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
