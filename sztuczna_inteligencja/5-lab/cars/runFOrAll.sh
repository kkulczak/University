#!/bin/bash

for task_file in chars_test1/task*txt
do
    echo pypy cars.py $task_file
done