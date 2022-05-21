FROM amazonlinux
LABEL developer='Andrey Gubaydullin'
RUN yum update -y && yum install yum-utils -y
COPY sp.sh .
RUN chmod ugo+x sp.sh
CMD ./sp.sh
