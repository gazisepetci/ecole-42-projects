FROM debian:buster

RUN apt-get update && apt-get install -y nginx openssl

RUN mkdir -p /etc/nginx/ssl

COPY ./conf/nginx.conf /etc/nginx/conf.d/
COPY ./tools/nginx.sh /var/www

EXPOSE 443

RUN chmod +x /var/www/nginx.sh

RUN mkdir -p /run/nginx

ENTRYPOINT [ "var/www/nginx.sh" ]

CMD [ "nginx", "-g", "daemon off;" ]
