FROM ubuntu:20.04

RUN apt-get update && apt install cmake -y && llvm@9

RUN mkdir -p /usr/src/TaskManager/
WORKDIR /usr/src/TaskManager/
COPY . /usr/src/TaskManager/

VOLUME ["/usr/local/bin/cmake",\
        "/usr/local/opt/openssl@1.1",\
        "/usr/local/Cellar/protobuf@3.6/3.6.1.3_3",\
        "/Users/valeriisudakov/libs/boost_1_74",\
        "/usr/local/Cellar/grpc/1.36.2",\
        "/usr/local/Cellar/googletest/1.10.0"\
        ]

RUN cmake -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl@1.1\
          -DProtobuf_ROOT=/usr/local/Cellar/protobuf@3.6/3.6.1.3_3\
          -DBoost_ROOT=/Users/valeriisudakov/libs/boost_1_74\
          -DGRPC_ROOT=/usr/local/Cellar/grpc/1.36.2\
          -DGTEST_ROOT=/usr/local/Cellar/googletest/1.10.0\
          -DCMAKE_CXX_FLAGS="-fprofile-arcs -ftest-coverage"\
          .
RUN cmake --build .

RUN chmod a+x ./Server
ENTRYPOINT ["./Server"]
