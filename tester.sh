#!/bin/bash

if [ -z "$1" ]
then
  echo "Usage: ./tester.sh [path to cub3D]"
  exit 1
fi

CUB3D="$1"
TEST_DATA="tester.csv"

