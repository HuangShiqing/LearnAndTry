DIR="./Debug/"
SRC="./src/"
if [ ! -d "${DIR}" ]; then
    mkdir "${DIR}"
fi

g++ "${SRC}"Convolution.cpp -c -o "${DIR}"Convolution.o
g++ "${SRC}"Pool.cpp -c -o "${DIR}"Pool.o
g++ "${SRC}"OpConverter.cpp -c -o "${DIR}"OpConverter.o
g++ "${SRC}"main.cpp "${DIR}"Convolution.o "${DIR}"Pool.o "${DIR}"OpConverter.o -o main