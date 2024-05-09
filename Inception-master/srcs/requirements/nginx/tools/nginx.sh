#!/bin/bash
if [ ! -f /etc/ssl/private/nginx.key ] || [ ! -f /etc/ssl/certs/nginx.crt ]; then
echo "Nginx: setting up ssl ...";
openssl req -x509 -nodes -days 365 -newkey rsa:4096 -keyout /etc/ssl/private/nginx.key -out /etc/ssl/certs/nginx.crt -subj "/C=TR/ST=KOCAELI/L=GEBZE/O=42Kocaeli/CN=uercan.42.fr";
echo "Nginx: ssl is set up!";
fi

sed -i "s/server_name \$DOMAIN_NAME/server_name $DOMAIN_NAME/g" /etc/nginx/conf.d/nginx.conf

exec "$@"
