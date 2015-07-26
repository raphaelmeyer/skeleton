FROM ybpi-base

MAINTAINER Raphael Meyer <raphael.akira.meyer@gmail.com>

RUN apt-get update && apt-get install -y \
  cmake \
  g++ \
  git \
  libboost-all-dev \
  make \
  ruby \
  ruby-dev

RUN gem install cucumber oj

USER user

VOLUME ["/workspace"]
WORKDIR /workspace

