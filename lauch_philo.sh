#!/bin/bash
# make && valgrind --tool=helgrind ./philo $1 $2 $3 $4 $5
# make && valgrind ./philo $1 $2 $3 $4
make && ./philo $1 $2 $3 $4 $5