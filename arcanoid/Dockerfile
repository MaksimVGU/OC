FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y g++ && \
    apt-get clean

COPY . /app
WORKDIR /app
RUN g++ -o game main.cpp

CMD ["./game"]
