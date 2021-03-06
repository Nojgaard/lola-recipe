#!/usr/bin/env bash
# tests/cover.sh.  Generated from cover.sh.in by configure.

#============================================================================#
# AUTOTEST WRAPPER SCRIPT FOR MAIN BINARY                                    #
# written by Niels Lohmann <niels.lohmann@uni-rostock.de>                    #
#============================================================================#

# This script has two modes:
# 1. if the environment variable COVER is set to YES, the test cases are
#    called as is, but before each test case, the environment variables of
#    gcov are set to store all coverage data of the executable in a newly
#    created directory. The data is not yet processed - this is done by
#    other Makefile targets.
#
# 2. otherwise, the given executable is called without code coverage tool


# evaluate COVER variable
case $COVER in
  "YES")
    # derive test name from current directory (assuming GNU Autotest); the
    # info filename is suffixed with a random number to allow for multiple
    # invokations of this script for the same test
    dir=`pwd`
    TESTNAME=`basename $dir`
    COVERDIR=/home/nikolai/share/lola-2.0/tests/cover/$TESTNAME-$RANDOM
    mkdir -p $COVERDIR

    # set flags for gcov to store all runtime cover information in the cover
    # directory
    export GCOV_PREFIX_STRIP=1000
    export GCOV_PREFIX=$COVERDIR

    # execute executable and remember exit code
    exec bash -c "$*"
    result=$?

    # exit with executable's exit code
    exit $result  
  ;;

  *)
    exec bash -c "$*"
    exit $?
  ;;
esac
