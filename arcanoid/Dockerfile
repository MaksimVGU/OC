FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y g++ && \
    apt-get clean

COPY . /app
WORKDIR /app
RUN g++ -o game game.cpp

CMD ["./game"]
