.. image:: https://secure.travis-ci.org/sycy600/rslib.png

Reed-Solomon code library. Project page is reachable at http://sycy600.github.io/rslib.

Features
========

* polynomial evaluation, addition, subtraction, multiplication, division and modulo operation

How to build
============

Clone repository::

    git clone https://github.com/sycy600/rslib.git

Create build directory::

    mkdir build
    cd build

Run ``cmake``::

    cmake ../rslib

Build project::

    make

Install project - that will install static library and headers on your system::

    sudo make install

Include headers in your program and link against ``librslib``. To compile the project
use C++11 standard.

Testing
=======

Unit tests are placed in directory ``tests``.

The pattern for test filename is ``*_tests.cc``.

Run unit tests::

    cd build
    make test

Run ``cpplint.py``::

    cd build
    make lint

To run memory check tests you need Valgrind.

Check for memory leaks with Valgrind (it runs Valgrind on unit
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

    cd build
    make doc
