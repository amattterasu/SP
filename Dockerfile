FROM amazonlinux
LABEL developer='Andrey Gubaydullin'
RUN yum update -y && yum install make glibc-devel gcc patch nasm -y 
COPY . .