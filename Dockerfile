FROM amazonlinux
RUN yum install -y gcc-c++ make
COPY . .
RUN make tcp && make udp