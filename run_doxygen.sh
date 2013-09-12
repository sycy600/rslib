#!/usr/bin/env bash
doxygen Doxyfile
cat doxygen_warnings.txt
# If this file is not empty then there are some documentation errors.
if [ -s doxygen_warnings.txt ]
then
  exit 1
fi

exit 0
