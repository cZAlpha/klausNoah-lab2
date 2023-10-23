#!/bin/bash

function cleanup()
{
    [ -e testFile ] && rm testFile
}

function error()
{
    echo -e "ERROR: $1"
    cleanup
    exit 1
}

make time &>> /dev/null

if [ $? -ne 0 ]; then
    error "ERROR: Makefile compilation has failed!" 
fi

[ -x time ] || error "ERROR: 'time' not found or not executable."

# If everything went fine, cleanup and give exit code 0, signifying everything is coolin'
cleanup
exit 0
