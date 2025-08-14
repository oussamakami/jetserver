FROM alpine:latest

COPY . /data

VOLUME ["/data/www"]

WORKDIR /data

RUN apk update && apk add --no-cache file php-cgi build-base && make re

CMD ["./jetserver"]