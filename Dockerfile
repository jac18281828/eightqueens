FROM debian:stable-slim AS builder
RUN export DEBIAN_FRONTEND=noninteractive && \
    apt update && \
        apt install -y -q --no-install-recommends \
        build-essential cmake googletest
RUN apt clean
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY CMakeLists.txt .
COPY src src/
COPY include include/
COPY test test/

ENV MAKEFLAGS=-j8

# build googletest
RUN cmake -H/usr/src/googletest -B/build/gtest -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE=on "-GUnix Makefiles"
RUN cmake --build /build/gtest --config RELEASE

WORKDIR /build/gtest
RUN ctest -C RELEASE

WORKDIR /build

# This is the builder! copy at will
RUN cp -v /build/gtest/lib/*.a /usr/lib

# build eightqueens
RUN cmake -H. -Brelease -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE=on "-GUnix Makefiles"
RUN cmake --build /build/release --config RELEASE

WORKDIR /build/release

RUN ctest -C RELEASE

WORKDIR /build

FROM debian:stable-slim

WORKDIR /queen

COPY --from=builder /build/release/eightqueens .

ENTRYPOINT /queen/eightqueens
