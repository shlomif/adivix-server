#! /bin/sh

clang -g -Wall -I. -I.. -O -o srvtest test/test.c srv.c daemon.c util.c signal.c C-Thread-Pool/thpool.c -pthread

