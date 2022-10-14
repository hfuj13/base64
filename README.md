hf::base64

* hf::base64 is headers only C++ Base64 encoder and decoder.

## Require

* C++17 or later (But it does not use any particular C++17 specific features)
* C++ Exception (-fexceptions etc.)

## Tester building and running

```
$ tar xf googletest-release-1.12.1.tar.gz
$ cd test
$ ln -s ../googletest-release-1.12.1/googletest/include ./
$ ln -s ../googletest-release-1.12.1/googletest/src ./
$ cmake -S . -B build
$ cd buld
$ make
$ ./base64_test
```
