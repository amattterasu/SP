FROM amazonlinux
RUN yum install -y gcc-c++
COPY . .
RUN g++ first.cpp -o first && g++ second.cpp -o second
CMD ./first