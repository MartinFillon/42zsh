#!/bin/bash

if [[ $# -lt 3 ]]; then
    echo "Usage: $0 <username> <email> [git commands...]"
    exit 1
fi

USERNAME=$1
EMAIL=$2

git -c user.name=$USERNAME -c user.email=$EMAIL ${*:3}