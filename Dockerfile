FROM ubuntu:24.10

RUN  apt update

RUN  apt install -y clang-tidy                 \
                    fonts-liberation           \
                    gcc                        \
                    gnuplot                    \
                    gpg                        \
                    lsb-release                \
                    make                       \
                    musl-dev                   \
                    software-properties-common \
                    valgrind
