FROM ubuntu:22.04

ENV LANG en_US.utf8

# dev stuff
RUN apt update
RUN apt-get install -y \
  apt-utils \
  curl \
  build-essential \
  git \
  openssh-server \
  pkg-config \
  systemd-coredump \
  manpages-dev \
  cppcheck \
  cmake \
  gdb \
  clang \
  lldb \
  lld \
  htop

# legacy build system dow not wwork with make 4.3 whcih is the default in ubuntu 22 and 24
RUN TEMP="$(mktemp)" && wget -O "$TEMP" 'http://ports.ubuntu.com/pool/main/m/make-dfsg/make_4.2.1-1.2_arm64.deb' && dpkg -i "$TEMP" && rm -f "$TEMP"

WORKDIR /home
