FROM debian:10 AS builder

RUN apt update && \
    apt -y install build-essential g++ cmake googletest

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
RUN cp -v /build/gtest/googlemock/*.a /usr/lib
RUN cp -v /build/gtest/googlemock/gtest/*.a /usr/lib

# build eightqueens
RUN cmake -H. -Brelease -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE=on "-GUnix Makefiles"
RUN cmake --build /build/release --config RELEASE

WORKDIR /build/release

RUN ctest -C RELEASE

WORKDIR /build

RUN ls -l release

FROM debian:10

# use UTC time
RUN rm -f /etc/localtime
RUN ln -sf /usr/share/zoneinfo/UTC /etc/localtime

ENV LANG=C.UTF-8 \
    TZ=UTC

WORKDIR /queen

COPY --from=builder /build/release/eightqueens .

ENTRYPOINT /queen/eightqueens
