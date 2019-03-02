#!/bin/bash

echo "Press ENTER after each test case"

for task_file in task*txt
do
    nim c -d:release ../cars.nim
    ../cars < $task_file > policy_for_$task_file
    python show_optimal_policy.py $task_file
done
