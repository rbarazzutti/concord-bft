FROM ubuntu:18.04
RUN apt-get update && apt-get install -y cmake clang clang-format libgmp3-dev git parallel g++ autoconf automake python3 python3-pip openssl libssl-dev psmisc byobu && rm -rf /var/lib/apt/lists/*
RUN python3 -m pip install --upgrade trio
COPY docker_build.sh /tmp
RUN cd /tmp && sh docker_build.sh
COPY . /concord-bft
RUN cd /concord-bft && mkdir build && cd build && cmake .. && make && make install
RUN touch /root/.rnd # workaround for OpenSSL 1.1.1

