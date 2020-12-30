#!/usr/bin/env /bin/bash

set -e

docker build .

docker run -i --rm
