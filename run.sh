#!/usr/bin/env /bin/bash

set -e

TAG='eightqueens:1.0.0'

docker build --tag ${TAG} .

docker run -i --rm ${TAG}
