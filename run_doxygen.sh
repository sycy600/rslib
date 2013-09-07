#!/usr/bin/env bash
doxygen Doxyfile
cat doxygen_warnings.txt
if [ -s doxygen_warnings.txt ]
then
  exit 1
fi

exit 0
