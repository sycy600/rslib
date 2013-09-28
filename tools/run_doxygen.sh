#!/usr/bin/env bash
if [ $# -ne 2 ]
then
  echo "Usage: bash run_doxygen.sh <source_dir_path> <Doxyfile_path>"
  exit 1
fi

(cat $2; echo INPUT=$1) | doxygen -
cat doxygen_warnings.txt
# If this file is not empty then there are some documentation errors.
if [ -s doxygen_warnings.txt ]
then
  exit 1
fi

exit 0
