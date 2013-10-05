.. image:: https://secure.travis-ci.org/sycy600/rslib.png

Reed-Solomon code library. Project page is reachable at http://sycy600.github.io/rslib.

Features
========

* polynomial evaluation, addition, subtraction, multiplication, division and modulo operation
* simple Galois field elements addition, subtraction, multiplication, division, additive and multiplicative inverse computation
* extended Galois field elements addition, subtraction, multiplication, division, additive and multiplicative inverse computation

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

Build project and do all checks (all-in-one)::

    ./check.sh

Run all unit tests::

    make test

Run only tests which name match filter (example filter will make testrunner to run
only ``Polynomial`` class tests)::

    make test ARGS="--gtest_filter=Polynomial.*"

Run ``cpplint.py``::

    make lint

To run memory check tests you need Valgrind.

Check for memory leaks with Valgrind (it runs Valgrind on unit
test runner process)::

    make memcheck

Documentation
=============

To build documentation you need Doxygen.

Generate documentation and check if there is some not
documented code::

    make doc
    
Project page is based on GitHub Pages and it is placed on branch ``gh-pages``.
