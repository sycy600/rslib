.. image:: https://secure.travis-ci.org/sycy600/rslib.png

Reed-Solomon code library. Documentation is reachable at [http://sycy600.github.io/rslib](http://sycy600.github.io/rslib/).

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

Generate documentation and check if there is some not
documented code::

    ./run_doxygen.sh
