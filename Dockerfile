FROM java:8
WORKDIR /app
COPY Main.java .
RUN javac Main.java
CMD ["java", "Main"]