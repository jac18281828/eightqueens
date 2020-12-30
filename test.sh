#!/usr/bin/env /bin/bash

set -e

TAG='cairns_gemini_match:1.0'

docker rmi -f ${TAG}

docker build --tag ${TAG} .

