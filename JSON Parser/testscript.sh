#!/bin/bash


function AssertInvalid {
  if [ $1 == "INVALID" ]; then
    echo "Test Passed ✅"
    return 0
  else
    echo "Test Failed ❌"
    return 1
  fi
}

function AssertValid {
  if [ $1 == "VALID" ]; then
    echo "Test Passed ✅"
    return 0
  else
    echo "Test Failed ❌"
    return 1
  fi
}


gcc parser.c -o p
#---------------------------------------------------


echo "STEP ONE TESTS:"
#---------------------------------------------------
echo "Valid JSON Tests"
status=$(./p tests/step1/valid.json)
AssertValid $status
#---------------------------------------------------
echo "Invalid Json Tests"
status=$(./p tests/step1/invalid.json)
AssertInvalid $status
#---------------------------------------------------


echo "STEP TWO TESTS:"
#---------------------------------------------------
echo "Valid JSON Tests"
status=$(./p tests/step2/valid.json)
AssertValid $status
status=$(./p tests/step2/valid.json)
AssertValid $status
#---------------------------------------------------
echo "Invalid Json Tests"
status=$(./p tests/step2/invalid.json)
AssertInvalid $status
status=$(./p tests/step2/invalid2.json)
AssertInvalid $status
#---------------------------------------------------


echo "STEP THREE TESTS:"
#---------------------------------------------------
echo "Valid JSON Tests"
status=$(./p tests/step3/valid.json)
AssertValid $status
#---------------------------------------------------
echo "Invalid Json Tests"
status=$(./p tests/step3/invalid.json)
AssertInvalid $status
#---------------------------------------------------
echo "STEP FOUR TESTS:"
#---------------------------------------------------
echo "Valid JSON Tests"
status=$(./p tests/step4/valid.json)
AssertValid $status
status=$(./p tests/step4/valid.json)
AssertValid $status
#---------------------------------------------------
echo "Invalid Json Tests"
status=$(./p tests/step4/invalid.json)
AssertInvalid $status
#---------------------------------------------------