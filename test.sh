#!/usr/bin/env /bin/bash

set -e

TAG='eightqueens:1.0.0'

docker rmi -f ${TAG}

docker build --tag ${TAG} .
