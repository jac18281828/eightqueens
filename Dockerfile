FROM debian:10 AS builder

RUN apt update && \
    apt -y install build-essential g++ cmake googletest

WORKDIR /build

COPY CMakeLists.txt .
COPY src src/
COPY include include/
COPY test test/

# build googletest
RUN cmake -H/usr/src/googletest -Bgtest -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE=on "-GUnix Makefiles" && (cd /build/gtest && make -j all)

# This is the builder!
RUN cp /build/gtest/googlemock/gtest/*.a /usr/lib

# build eightqueens
RUN cmake -H. -Brelease -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_VERBOSE_MAKEFILE=on "-GUnix Makefiles" && (cd release && make -j all test)

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
