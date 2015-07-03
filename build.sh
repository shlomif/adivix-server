#! /bin/sh

gcc -g -Wall -I.. -O -o test test.c srv.c daemon.c util.c signal.c -pthread

