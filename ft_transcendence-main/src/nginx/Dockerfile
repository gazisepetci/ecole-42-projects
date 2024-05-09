FROM nginx

RUN mkdir -p /etc/nginx/certs && \
openssl req -x509 -newkey rsa:4096 \
-keyout /etc/nginx/certs/transcendence.key \
-out /etc/nginx/certs/transcendence.crt \
-sha256 -days 365 -nodes \
-subj '/C=TR/ST=Turkiye/L=Kocaeli/O=42Kocaeli/OU=Student/CN=localhost'

COPY nginx.conf /etc/nginx/conf.d/default.conf

CMD ["nginx", "-g", "daemon off;"]
