#!/bin/sh

find . -name "*.cpp" -exec indent -npro -nip -nlp -npsl -i2 -ts2 -sob -ss -l0 -bl -bli 0 `pwd`/{} \;
find . -name "*.c" -exec indent -npro -nip -nlp -npsl -i2 -ts2 -sob -ss -l0 -bl -bli 0 `pwd`/{} \;
find . -name "*.h" -exec indent -npro -nip -nlp -npsl -i2 -ts2 -sob -ss -l0 -bl -bli 0 `pwd`/{} \;
find . -name "*.hpp" -exec indent -npro -nip -nlp -npsl -i2 -ts2 -sob -ss -l0 -bl -bli 0 `pwd`/{} \;

