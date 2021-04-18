#!/bin/bash
#Author:HuangShiqing
#Time:2021-03-09 17:40:09
#Name:mk.sh
#Description:This is a awesome script.

# check is flatbuffer installed or not
git submodule init
git submodule update
# if [ ! -d $FLATBUFFER_DIR ]; then
#   git clone https://github.com/google/flatbuffers.git
# fi

ROOT_DIR=$(pwd)
FLATBUFFER_DIR=${ROOT}/flatbuffers

FLATC=${FLATBUFFER_DIR}/build/flatc
if [ ! -e $FLATC ]; then
  echo "*** building flatc ***"
  cd ${FLATBUFFER_DIR}
  # make tmp dir
  [ ! -d build ] && mkdir build
  cd build && rm -rf *

  # build
  cmake .. && cmake --build . --target flatc -- -j4
fi

cd ${ROOT_DIR}
${FLATC} monster.fbs --cpp
${FLATC} net.fbs --cpp --binary --reflect-names --gen-object-api --gen-compare

g++ monster_write.cpp -o monster_write -I ./flatbuffers/include/ -std=c++11
g++ monster_read.cpp -o monster_read -I ./flatbuffers/include/ -std=c++11

g++ net_write.cpp -o net_write -I ./flatbuffers/include/ -std=c++11 -O0 -g
g++ net_read.cpp -o net_read -I ./flatbuffers/include/ -std=c++11 -O0 -g
