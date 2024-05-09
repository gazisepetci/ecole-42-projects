let pongRoomConnected = {};
let pongRoomName;
let pongGameType;
let pongNextPlayers = [];
let pongCurrentPlayers = [];
let pongRedraw = false;
let pongDrawn = false;

function pongRoom() {
  document.querySelector("#pong-message-input").focus();
  document
    .querySelector("#pong-message-input")
    .addEventListener("keyup", function (e) {
      if (e.key === "Enter") {
        // enter, return
        document.querySelector("#pong-message-submit").click();
      }
    });

  document
    .getElementById("pong-message-log")
    .addEventListener("keydown", pongRoomLogEscapeEvent);

  document
    .getElementById("pong-message-input")
    .addEventListener("keydown", pongRoomLogEscapeEvent);

  if (isSocketOpen(pongSocket)) {
    setDisabledPongRoom(false);
    setTimeout(function () {
      pongRedraw = true;
    }, 500);
  } else {
    setDisabledPongRoom(true);
  }

  document
    .getElementById("pong-room-switch-type")
    .addEventListener("click", function (e) {
      pingSwitchType(pongSocket);
    });

  document
    .querySelector("#pong-message-submit")
    .addEventListener("click", function (e) {
      const messageInputDom = document.querySelector("#pong-message-input");
      const message = messageInputDom.value;
      let type;

      if (message.startsWith("/")) {
        type = "chat.command";
      } else {
        type = "chat.message";
      }

      pongSocket.send(
        JSON.stringify({
          type: type,
          message: message,
        })
      );
      messageInputDom.value = "";
    });

  document
    .querySelector("#pong-room-connect")
    .addEventListener("click", function (e) {
      const messageInputDom = document.querySelector("#pong-room-input");
      const message = messageInputDom.value;
      const roomName = message;

      if (isSocketOpen(pongSocket)) {
        pongSocket.close();
      }

      pongSocket = new WebSocket(
        "wss://" + window.location.host + "/ws/pong/" + roomName + "/"
      );

      pongSocket.onopen = function (e) {
        pongRoomName = roomName;
        const msgLog = document.getElementById("pong-message-log");
        if (msgLog !== null) {
          msgLog.value += "[!] Connected to " + pongSocket.url + "\n";
          msgLog.value += "======================================================\n";
          msgLog.value += "Player controls: W,S\nCamera controls: H,J,K,L,N,M\n\n";
          msgLog.value += "A match is concluded if time limit is reached\n";
          msgLog.value += "and one player scores more than the other.\n\n";
          msgLog.value += "Type \"/help\" to learn more about commands\n";
          msgLog.value += "======================================================\n";
        }
        setDisabledPongRoom(false);
        const target = document.getElementById("webgl");
        target.style.visibility = "visible";
        target.focus();
      };

      pongSocket.onmessage = function (e) {
        const info = JSON.parse(e.data);
        if (info.type === "pong.status") {
          const log = document.getElementById("pong-ping-log");
          if (log !== null) log.value = JSON.stringify(info, null, 4);
          if (("current_players" in info) & (info.current_players.length > 0)) {
            replaceOutput(
              info.players[info.current_players[0]],
              "pong-player1-log",
              ["0", info.current_players[0]]
            );
            replaceOutput(
              info.players[info.current_players[1]],
              "pong-player2-log",
              ["1", info.current_players[1]]
            );
          }
          handlePongGame(info);
        } else {
          const log = document.getElementById("pong-message-log");
          if (log !== null) {
            onTop = log.scrollHeight === log.scrollTop;
            log.value += info.message + "\n";
            if (onTop) log.scrollTop = log.scrollHeight;
          }
        }
      };

      pongSocket.onclose = function (e) {
        const log = document.getElementById("pong-message-log");
        if (log !== null) {
          log.value += "[!] Pong socket closed at " + pongSocket.url + "\n";
        }
        setDisabledPongRoom();
        pongRoomName = null;
      };
    });

  document.querySelector("#pong-room-disconnect").onclick = function (e) {
    pongSocket.close();
  };

  document.querySelector("#pong-room-ready").onclick = function (e) {
    pingReady(pongSocket);
  };

  document.querySelector("#pong-room-move-up").onclick = function (e) {
    pingMove(pongSocket, true);
  };

  document.querySelector("#pong-room-move-down").onclick = function (e) {
    pingMove(pongSocket, false);
  };
}

function pingReady(socket) {
  socket.send(
    JSON.stringify({
      type: "pong.ready",
      message: "",
    })
  );
}

function pingMove(socket, to_up = true) {
  socket.send(
    JSON.stringify({
      type: "pong.move",
      to_up: to_up,
    })
  );
}

function pingSwitchType(socket) {
  let targetType;
  if (pongGameType === 1) {
    targetType = "TOURNAMENT";
  } else {
    targetType = "ONEVONE";
  }

  socket.send(
    JSON.stringify({
      type: "pong.setting",
      settings: { type: targetType },
    })
  );
}

function syntaxHighlight(json) {
  if (typeof json != "string") {
    json = JSON.stringify(json, undefined, 4);
  }
  json = json
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
  return json.replace(
    /("(\\u[a-zA-Z0-9]{4}|\\[^u]|[^\\"])*"(\s*:)?|\b(true|false|null)\b|-?\d+(?:\.\d*)?(?:[eE][+\-]?\d+)?)/g,
    function (match) {
      let cls = "number";
      if (/^"/.test(match)) {
        if (/:$/.test(match)) {
          cls = "key";
        } else {
          cls = "string";
        }
      } else if (/true|false/.test(match)) {
        cls = "boolean";
      } else if (/null/.test(match)) {
        cls = "null";
      }
      return '<span class="' + cls + '">' + match + "</span>";
    }
  );
}

function replaceOutput(input, targetElementId, playerInfo = ["x", "username"]) {
  const target = document.getElementById(targetElementId);
  if (target === null) return;
  target.innerHTML = "";
  target.appendChild(document.createElement("h3")).innerHTML =
    "player " + playerInfo[0] + ": " + playerInfo[1];
  target.appendChild(document.createElement("pre")).innerHTML =
    syntaxHighlight(input);
}

function setDisabledPongRoom(setBool = true) {
  document.querySelector("#pong-message-submit").disabled = setBool;
  document.querySelector("#pong-message-input").disabled = setBool;
  document.querySelector("#pong-room-ready").disabled = setBool;
  document.querySelector("#pong-room-move-up").disabled = setBool;
  document.querySelector("#pong-room-move-down").disabled = setBool;
}

function handlePongGame(info) {
  pongGameType = info.game_type;
  pongCurrentPlayers = info.current_players;

  updateScoreBoard(info);

  if (info.status === 5 && !pongDrawn) {
    pongRedraw = true;
  }

  if (pongRedraw) {
    pongRedraw = false;
    window.gameInitBoard(info.board_size[0], info.board_size[1]);
    let ball = ballDict(info.ball);
    window.gameInitBall(ball.pos, ball.vel, ball.rad);
    let count = 0;
    for (const p of info.current_players) {
      let p_info = info.players[p];
      p_info["width"] = info.paddle_size[0];
      p_info["height"] = info.paddle_size[1];
      const player = playerDict(p_info, p);
      window.gameInitPlayer(
        "player" + count,
        player.pos,
        player.vel,
        player.width,
        player.height,
        player.nickname,
        player.username
      );
      count += 1;
    }
    pongDrawn = true;
  }
  else if (info.status === 2 && !window.gameActive()) {
    pongDrawn = false;
    window.gameStartMatch();
  } else if ((info.status === 3 || info.status === 4) && window.gameActive()) {
    window.gameFinishMatch();
  } else if (info.status === 2) {
    if (pongGameType === 2) {
      notifyNextPlayers(info.next_players);
    }
    updateScoreLabel(info);
    let ball = ballDict(info.ball);
    window.gameSetBall(ball.pos, ball.vel);

    let count = 0;
    for (const p of info.current_players) {
      let p_info = info.players[p];
      p_info["width"] = info.paddle_size[0];
      p_info["height"] = info.paddle_size[1];
      const player = playerDict(p_info, p);
      window.gameSetPlayer("player" + count, player.pos);
      count += 1;
    }
  }
}

function ballDict(info_ball) {
  return {
    pos: { x: info_ball.pos_x, y: info_ball.pos_y },
    vel: { x: info_ball.vel_x, y: info_ball.vel_y },
    rad: info_ball.radius,
  };
}

function playerDict(p_info, username) {
  return {
    pos: { x: p_info.pos_x, y: p_info.pos_y },
    vel: p_info.vel,
    nickname: p_info.nickname,
    username: username,
    width: p_info.width,
    height: p_info.height,
  };
}

function updateScoreLabel(info) {
  const score0 = info.players[info.current_players[0]].score;
  const score1 = info.players[info.current_players[1]].score;

  const label = document.getElementById("pong-score-label");
  if (label !== null) label.innerText = score0 + " - " + score1;
}

function updateScoreBoard(info) {
  let stripped = {};

  for (const key of Object.keys(info.players)) {
    const value = info.players[key];
    stripped[key] = [
      value.nickname,
      value.is_owner,
      value.wins,
      value.total_score,
    ];
  }

  if (pongRedraw || !isSameConnected(pongRoomConnected, stripped)) {
    pongRoomConnected = stripped;

    const element = document.getElementById("pong-player-scores");
    element.innerHTML = "";
    for (const [key, value] of Object.entries(pongRoomConnected)) {
      const row = element.appendChild(document.createElement("div"));
      row.classList.add("row");

      const name = row.appendChild(document.createElement("div"));
      name.classList.add("col");
      name.textContent = value[0];
      if (value[1]) {
        const span = name.appendChild(document.createElement("span"));
        span.classList.add("position-absolute", "start-50", "text-warning");
        span.innerHTML = '<i class="bi bi-star-fill"></i>';
      }

      const scores = row.appendChild(document.createElement("div"));
      scores.classList.add("col");
      const score_row = scores.appendChild(document.createElement("div"));
      score_row.classList.add("row", "justify-content-between");
      const win = score_row.appendChild(document.createElement("div"));
      win.classList.add("col");
      win.textContent = value[2] + "W";
      const total_score = score_row.appendChild(document.createElement("div"));
      total_score.classList.add("col");
      total_score.textContent = value[3] + "TP";
    }
  }
}

function isSameConnected(dict1, dict2) {
  if (Object.keys(dict1).length !== Object.keys(dict2).length) {
    return false;
  } else {
    const a1 = Object.entries(dict1).sort();
    const a2 = Object.entries(dict2).sort();

    for (let i = 0; i < a1.length; i++) {
      const e1 = a1[i];
      const e2 = a2[i];

      // e1[0] key / username
      // e1[1] value / [nickname, is_owner, wins, total_score, score]

      if (e1.length !== e2.length) {
        return false;
      } else if (e1[0] !== e2[0]) {
        return false;
      }

      const val1 = e1[1];
      const val2 = e2[1];

      if (val1.length !== val2.length) {
        return false;
      }

      for (let j = 0; j < val1.length; j++) {
        if (val1[j] !== val2[j]) {
          return false;
        }
      }
    }
  }
  return true;
}

function notifyNextPlayers(next_players) {
  if (isSameNextPlayers(pongNextPlayers, next_players)) {
    return;
  }

  pongNextPlayers = next_players;
  const toastEl = document.createElement("div");
  toastEl.classList.add("toast");
  toastEl.setAttribute("role", "alert");
  toastEl.setAttribute("aria-live", "assertive");
  toastEl.setAttribute("aria-atomic", "true");

  const header = toastEl.appendChild(document.createElement("div"));
  header.classList.add("toast-header");
  const strong = header.appendChild(document.createElement("strong"));
  strong.classList.add("me-auto");
  strong.innerHTML = "Pong";
  const button = header.appendChild(document.createElement("button"));
  button.classList.add("btn-close");
  button.setAttribute("type", "button");
  button.setAttribute("data-bs-dismiss", "toast");
  button.setAttribute("aria-label", "Close");

  const body = toastEl.appendChild(document.createElement("div"));
  body.classList.add("toast-body");
  body.innerHTML =
    "Next players in tournament " +
    pongNextPlayers[0] +
    " vs " +
    pongNextPlayers[1];

  document.getElementById("toast-content").appendChild(toastEl);

  const toast = new bootstrap.Toast(toastEl);
  toast.show();
  setTimeout(toast.dispose, 5000);
}

function isSameNextPlayers(arr1, arr2) {
  if (arr1.length !== arr2.length) {
    return false;
  }

  for (let i = 0; i < arr1.length; i++) {
    if (arr1[i] !== arr2[i]) {
      return false;
    }
  }

  return true;
}

function pongRoomLogEscapeEvent(event) {
  if (event.key == "Escape") {
    const target = document.getElementById("webgl");
    target.style.visibility = "visible";
    target.focus();
  }
}