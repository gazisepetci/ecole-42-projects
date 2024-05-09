# ft\_transcendence
![Docker-compose schema](/assets/images/ft_transcendence_schema.png "ft_transcendence schema")

## Makefile
- `make [start, up]` composes the project with build option
- `make (stop, down)` stops the running containers
- `make no-build` composes the project w/o build option
- `sudo make (refresh, re)` removes all images (except postgres and redis) and volumes added by this project. You may need to change `$(PARENT_DIR)-*` pattern to `$(PARENT_DIR)_*` depending on docker-compose implementation on your system.

## Microservices
#### user-web
Serves all html files in the project, authenticates users and stores user information in `user-db` database. Static files are served via `user-nginx`, all scripts are loaded at index. User authentication and storage functions of this services can be split to another microservice for further improvement.
#### game-web
Serves WebSocket endpoints for remote Pong games. Runs asynchronously. Each client connection corresponds to a Pong game room, thus a connection can only be established to create or join a room. Users can send messages to each other and run commands in the room, the status of the room is periodically pinged to all connected clients.
#### chat-web
Serves WebSocket endpoints for chat utility. Runs asynchronously. Each connection adds the client to an online user pool, currently the chat only allows for private conversations between online users. Although we have not fully implemented the live chat module specified in the project subject, this service is utilized to keep a record of online users.

## Specification for Environment Variables

#### GLOBAL\_WEB\_ALLOWED\_HOSTS
Global `ALLOWED_HOSTS` setting, applies to all Django projects
- Required for: user-web, game-web, chat-web
- Specific Config Variables: `USER_WEB_ALLOWED_HOSTS`, `GAME_WEB_ALLOWED_HOSTS`, `CHAT_WEB_ALLOWED_HOSTS`
- Example:
  ```shell
  GLOBAL_WEB_ALLOWED_HOSTS=localhost,ft_transcendence,127.0.0.1,192.168.1.6
  ```

#### CSRF\_TRUSTED\_ORIGINS
Specifies `CSRF_TRUSTED_ORIGINS` setting in user-web Django project, used in form validation of POST/PUT requests
- Required for: user-web
- Example:
  ```shell
  CSRF_TRUSTED_ORIGINS=https://localhost:3600,https://ft_transcendence:443
  ```

#### JWT\_KEY
Global signature key for JWT authentication
- Required for: user-web, game-web, chat-web

#### OAUTH\_CLIENT\_ID / OAUTH\_CLIENT\_SECRET / OAUTH\_CLIENT\_REDIRECT
42 Login API credentials, used in remote authentication
- Required for: user-web

#### EMAIL\_HOST / EMAIL\_HOST\_USER / EMAIL\_HOST\_PASSWORD / EMAIL\_PORT
SMTP server credentials, used in two-factor authentication
- Required for: user-web

#### POSTGRES\_DB / POSTGRES\_USER / POSTGRES\_PASSWORD
PostgreSQL login credentials
- Required for: user-db, user-web

#### USER\_WEB\_SECRET\_KEY / GAME\_WEB\_SECRET\_KEY / CHAT\_WEB\_SECRET\_KEY
Specifies `SECRET_KEY` variable in the settings of Django projects
- Required for: user-web, game-web, chat-web
- Note: This variable should not be modified after building database and Django services
