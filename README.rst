.. image:: https://secure.travis-ci.org/sycy600/rslib.png

Reed-Solomon code library. Project page is reachable at http://sycy600.github.io/rslib.

Features
========

* polynomial evaluation, addition, subtraction, multiplication, division and modulo operation
* simple Galois field elements addition, subtraction, multiplication, division, additive and multiplicative inverse computation
* extended Galois field elements addition, subtraction, multiplication, division, additive and multiplicative inverse computation
* Reed-Solomon code encoder
* Reed-Solomon code decoder (BMA algorithm)
* support for Galois fields with different characteristic than 2

Overview
========

::
   
    #include <rslib/polynomial.h>
    #include <rslib/simplefield.h>
    #include <rslib/simplefieldelement.h>
    #include <rslib/extendedfield.h>
    #include <rslib/extendedfieldelement.h>
    #include <rslib/encoder.h>
    #include <rslib/bmadecoder.h>
    
    ...
    
    using namespace rslib;
    // create field GF(3)
    SimpleField GF3 = SimpleField(3);
  
    // create generator polynomial for field GF(9)
    // generator(x) = x^2 + x + 2
    Polynomial<SimpleFieldElement>
        generator = Polynomial<SimpleFieldElement>({
                      SimpleFieldElement(2, GF3),
                      SimpleFieldElement(1, GF3),
                      SimpleFieldElement(1, GF3)});
  
    // create field GF(9)
    ExtendedField GF9 = ExtendedField(generator);
  
    // create encoder for code RS(8, 4) - this code can repair 2 errors,
    // length of codeword is 8 and there are 4 information elements
    // and 4 redundant elements
    Encoder encoder(2, GF9);
  
    // create some information polynomial
    Polynomial<ExtendedFieldElement> information =
        Polynomial<ExtendedFieldElement>({
                     ExtendedFieldElement(4, GF9),
                     ExtendedFieldElement(3, GF9),
                     ExtendedFieldElement(6, GF9),
                     ExtendedFieldElement(2, GF9)});
  
    // information polynomial
    // [A^3,A^2,A^5,A,]
    std::cout << information << '\n';
  
    // encode information polynomial
    Polynomial<ExtendedFieldElement> codeword = encoder.encode(information);
  
    // codeword
    // [0,A,A^6,A,A^3,A^2,A^5,A,]
    std::cout << codeword << '\n';
  
    // change two positions in codeword so there are 2 errors added
    Polynomial<ExtendedFieldElement> receivedWord(codeword);
    receivedWord.setValue(5, ExtendedFieldElement(5, GF9));
    receivedWord.setValue(7, ExtendedFieldElement(1, GF9));
  
    // received word (notice elements at two positions are different than in codeword)
    // [0,A,A^6,A,A^3,A^4,A^5,1,]
    std::cout << receivedWord << '\n';
  
    // create decoder for code RS(8, 4)
    BMADecoder decoder(2, GF9);
  
    // decode code word - 2 errors are corrected and information extracted
    // from received word is the same as the original information
    // [A^3,A^2,A^5,A,]
    std::cout << decoder.decode(receivedWord) << '\n';

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
