#!/bin/bash

IFS=',' read -r -a array <"numbers.txt"

sort -n <(printf "%s\n" "${array[@]}")



