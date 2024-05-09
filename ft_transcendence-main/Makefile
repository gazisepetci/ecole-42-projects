PARENT_DIR=$(notdir $(CURDIR))

all: start

start:
	docker-compose up --build

no-build:
	docker-compose up

stop:
	docker-compose down

refresh:
	docker image rm -f $(PARENT_DIR)-user-web
	docker image rm -f $(PARENT_DIR)-chat-web
	docker image rm -f $(PARENT_DIR)-game-web
	docker image rm -f $(PARENT_DIR)-master-nginx
	docker image rm -f $(PARENT_DIR)-user-nginx
	docker image rm -f $(PARENT_DIR)-chat-nginx
	docker image rm -f $(PARENT_DIR)-game-nginx
	docker system prune
	docker volume prune
	docker volume rm -f $(PARENT_DIR)_user-media
	docker volume rm -f $(PARENT_DIR)_user-postgres
	docker volume rm -f $(PARENT_DIR)_user-static

up: start
down: stop
re: refresh
reset: refresh

.PHONY: all start no-build stop refresh up down re reset
