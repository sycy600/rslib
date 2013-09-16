.. image:: https://secure.travis-ci.org/sycy600/rslib.png

Reed-Solomon code library. Project page is reachable at http://sycy600.github.io/rslib.

How to build
============

Create build directory::

    mkdir build
    cd build

Run ``cmake``::

    cmake ..

Build project::

    make

Install project - that will install static library and headers on your system::

    sudo make install

Include headers in your program and link against ``librslib``.

Testing
=======

To run memcheck tests you need Valgrind.

Unit tests are placed in directory ``tests``.

The pattern for test filename is ``*_tests.cc``.

Run unit tests::

    cd build
    make test

Run ``cpplint.py``::

    cd build
    make lint

Check for memory leaks with Valgrind (run Valgrind on unit
test runner process)::

    cd build
    make memcheck

Build project and do all checks (all-in-one)::

    ./check.sh

Documentation
=============

To build documentation you need Doxygen.

Generate documentation and check if there is some not
documented code::

    ./run_doxygen.sh
