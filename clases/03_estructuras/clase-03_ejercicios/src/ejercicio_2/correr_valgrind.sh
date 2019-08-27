#!/usr/bin/env bash
make
clear
valgrind --leak-check=full ./ejercicio
