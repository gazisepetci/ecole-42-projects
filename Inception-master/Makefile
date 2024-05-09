DC := docker-compose -f ./srcs/docker-compose.yml
COMPOSE_FILE	:= docker-compose.yml
COMPOSE_DIR		:= ./srcs/
USER			:= uercan
WP_DIR			:= /home/$(USER)/data/wordpress
DB_DIR			:= /home/$(USER)/data/mariadb

all:
	@mkdir -p $(WP_DIR)
	@mkdir -p $(DB_DIR)
	@$(DC) up -d --build

down:
	@$(DC) down

re: clean all

clean:
	@rm -rf $(WP_DIR) $(DB_DIR)
	@$(DC) down --rmi all --volumes
	@docker image prune -f
	@docker network prune -f
	@docker system prune -af

fclean: clean ## It thoroughly cleans the Docker environment and gets it ready for a fresh start.
	@if [ $$(docker ps -aq | wc -l) -gt 0 ]; then \
		docker stop $$(docker ps -aq); \
		docker rm -vf $$(docker ps -aq); \
	fi
	@if [ $$(docker images -aq | wc -l) -gt 0 ]; then \
		docker rmi -f $$(docker images -aq); \
	fi
	@if [ $$(docker volume ls -q | wc -l) -gt 0 ]; then \
		docker volume rm $$(docker volume ls -q); \
	fi
	@if [ $$(docker network ls | grep -v "bridge\|none\|host" | awk '{print $$1}' | tail -n +2 | wc -l) -gt 0 ]; then \
		docker network rm $$(docker network ls | grep -v "bridge\|none\|host" | awk '{print $$1}' | tail -n +2); \
	fi
	@rm -rf $(WP_DIR) $(DB_DIR)

.PHONY: all down re clean
