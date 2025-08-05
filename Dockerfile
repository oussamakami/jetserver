FROM alpine:latest

RUN apk update && apk add file php-cgi && mkdir /data

WORKDIR /data

CMD ["./jetserver"]