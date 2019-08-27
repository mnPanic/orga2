#!/usr/bin/env bash
make
[ $? = 0 ] && clear && valgrind --leak-check=full ./ejercicio
