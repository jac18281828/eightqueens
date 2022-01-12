#!/usr/bin/env /bin/bash

set -e

VERSION=$(date +"%M%d%y")
PROJECT=jac18281828/eightqueens

docker build --progress plain . -t ${PROJECT}:${VERSION} && \
    docker run -i --rm ${PROJECT}:${VERSION}
