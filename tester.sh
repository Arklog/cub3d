#!/bin/bash

CUB3D="$1"
TEST_DATA="tester.csv"
MAP_DIR="assets/map"

TIMEOUT=2

RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

if [ -z "$1" ]
then
  echo "Usage: ./tester.sh [path to cub3D]"
  exit 1
fi

#
#	PRINT A STRING IN GREEN COLOR
#
function print_ok()
{
  echo -e "$GREEN $1 $RESET"
}

#
#	PRINT A STRING IN RED COLOR
#
function print_ko()
{
  echo -e "$RED $1 $RESET"
}

#
#	TEST ONE MAP
#
function test_one()
{
  MAP="$1"
  EXPECTED_CODE="$2"
  EXPECTED_MSG="Error: $3"

  MSG="$(timeout $TIMEOUT $CUB3D $MAP 2>&1)"
  CODE=$?

  echo "$MAP"
  if [ "$CODE" -eq "$EXPECTED_CODE" ]
  then
    print_ok "  Expected code: $EXPECTED_CODE, got $CODE"
  else
    print_ko "  Expected code: $EXPECTED_CODE, got $CODE"
  fi
}

cat $TEST_DATA | tail -n +2 | while IFS=\n read -r line; do
  MAP=$(echo $line | cut -d, -f1)
  CODE=$(echo $line | cut -d, -f2)
  MSG=$(echo $line | cut -d, -f3)

  test_one "$MAP_DIR/$MAP" $CODE "$MSG"
done
