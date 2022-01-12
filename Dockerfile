FROM debian:stable-slim AS builder

RUN apt update && \
    apt -y install build-essential g++ cmake googletest
RUN apt clean

WORKDIR /build

COPY CMakeLists.txt .
COPY src src/
COPY include include/
COPY test test/

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
