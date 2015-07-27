#! /bin/sh

clang -g -Wall -I. -I.. -O -o test test.c srv.c daemon.c util.c signal.c C-Thread-Pool/thpool.c -pthread

