function chatRoom() {
  document
    .getElementById("chat-room-online-refresh")
    .addEventListener("click", chatRoomRefreshEvent);

  setTimeout(chatRoomRefreshEvent, 300); // Waiting in case user needs to reconnect.

  document
    .getElementById("chat-room-message-input")
    .addEventListener("keyup", function (e) {
      if (e.key === "Enter") {
        // enter, return
        sendChatMessageSignal(
          document.getElementById("chat-room-user-title").innerText,
          e.target.value
        );
        e.target.value = "";
      }
    });
}

// ===== SIGNALS =====

function sendChatListSignal() {
  // Ask server to send a list of online user's usernames

  if (!isSocketOpen(chatSocket)) {
    return;
  }

  chatSocket.send(
    JSON.stringify({
      type: "chat.list",
    })
  );
}

function sendChatOpenSignal(targetUsername) {
  // Ask server to establish a room with targetUsername

  if (!isSocketOpen(chatSocket)) {
    return;
  }

  chatSocket.send(
    JSON.stringify({
      type: "chat.open",
      target: targetUsername,
    })
  );
}

function sendChatMessageSignal(targetUsername, message) {
  // Send message to targetUsername

  // TODO: Check if chat room is open with targetUsername ( if not, call sendChatOpenSignal() )
  // TODO: Check if targetUsername is online

  if (!isSocketOpen(chatSocket)) {
    return;
  }

  chatSocket.send(
    JSON.stringify({
      type: "chat.message",
      target: targetUsername,
      message: message,
    })
  );
}

function receiveChatErrorSignal(data) {
  console.error("An error occured at " + data.error_at + ": " + data.message);
}

function receiveChatListSignal(data) {
  const now = new Date();
  sessionStorage.setItem(
    "online-info",
    JSON.stringify({
      last_update: now.getHours() + ":" + now.getMinutes(),
      users: data.users,
    })
  );
}

function receiveChatOpenSignal(data) {
  // Connection established with data.target (data.target ~ targetUsername)
  // Connection established in room data.room
  // Server allows sending messages to data.target

  chatRoomOpen(data.room, data.target);
}

function receiveChatMessageSignal(data) {
  // Received chatmessage from data.from
  // Received chatmessage in room data.room

  let [rooms, users] = chatRoomOpen(data.room, data.from);
  let message = data.from + ": " + data.message + "\n";
  const username = getCookie("username");

  rooms[data.room] += message;

  // If chat room is loaded:

  const element = document.getElementById("chat-room-user-title");

  if (typeof element !== "null") {
    const current_chat = element.innerText;

    if (data.from === current_chat || data.from === getCookie("username")) {
      document.getElementById("chat-room-message-content").innerText += message;
    } else {
      users[data.from]["unread_count"] += 1;
    }
  } else {
    users[data.from]["unread_count"] += 1;
  }

  sessionStorage.setItem("chat-room-history", JSON.stringify(rooms));
  sessionStorage.setItem("chat-user-room", JSON.stringify(users));

  if (typeof element !== "null") {
    updateOnlineUnread(data.from);
  }
}

// ===== EVENTS =====

function chatRoomRefreshEvent(event) {
  if (isSocketOpen(chatSocket)) {
    sendChatListSignal();
    setTimeout(updateOnlineList, 300);
  } else {
    document.getElementById("chat-room-online-log").innerHTML =
      "No connection established.";
  }
}

function chatRoomLoadEvent(event) {
  event.preventDefault();
  const username = event.target.innerText;
  const need_time = chatRoomLoadOpen(username);

  if (need_time) {
    setTimeout(chatRoomLoadContent, 300, username);
  } else {
    chatRoomLoadContent(username);
  }
}

// ===== UTILS =====

function updateOnlineList() {
  const online_info = JSON.parse(sessionStorage.getItem("online-info"));
  const target = document.getElementById("chat-room-online-log");
  target.innerHTML = "";
  for (const element of online_info.users) {
    appendOnlineUser(target, element);
  }
  document.getElementById("chat-room-online-ago").innerText =
    "Last updated at " + online_info.last_update;

  updateOnlineUnread();
}

function updateOnlineUnread(newMessageUser = "") {
  const chatting_users = JSON.parse(sessionStorage.getItem("chat-user-room"));
  const online_info = JSON.parse(sessionStorage.getItem("online-info"));

  if (newMessageUser.length > 0) {
    if (newMessageUser === getCookie("username")) {
      return;
    } else if (online_info["users"].indexOf(newMessageUser) < 0) {
      const target = document.getElementById("chat-room-online-log");
      item = appendOnlineUser(target, newMessageUser);
      if (chatting_users[item.innerText]["unread_count"] > 0) {
        item.setAttribute(
          "class",
          "ps-1 rounded bg-warning bg-gradient bg-opacity-75"
        );
      }
      online_info["users"].push(newMessageUser);
      sessionStorage.setItem("online-info", JSON.stringify(online_info));
      return;
    }
  }

  let childs = document.getElementById("chat-room-online-log").childNodes;

  childs.forEach(function (item) {
    if (item.innerText in chatting_users) {
      if (chatting_users[item.innerText]["unread_count"] > 0) {
        item.setAttribute(
          "class",
          "ps-1 rounded bg-warning bg-gradient bg-opacity-75"
        );
      } else {
        item.setAttribute("class", "ps-1");
      }
    }
  });
}

function appendOnlineUser(target, username) {
  let child = target.appendChild(document.createElement("li"));
  child.innerHTML = username;
  child.setAttribute("role", "button");
  child.classList.add("ps-1");
  child.addEventListener("click", chatRoomLoadEvent);
  return child;
}

function chatRoomOpen(room, targetUsername) {
  let rooms = JSON.parse(sessionStorage.getItem("chat-room-history"));
  let users = JSON.parse(sessionStorage.getItem("chat-user-room"));

  if (!(room in rooms)) {
    rooms[room] = "";
    sessionStorage.setItem("chat-room-history", JSON.stringify(rooms));
  }

  if (!(targetUsername in users)) {
    users[targetUsername] = {};
    users[targetUsername]["room"] = room;
    users[targetUsername]["unread_count"] = 0;
    sessionStorage.setItem("chat-user-room", JSON.stringify(users));
  }

  return [rooms, users];
}

function chatRoomLoadOpen(target) {
  const users = JSON.parse(sessionStorage.getItem("chat-user-room"));

  if (!(target in users)) {
    sendChatOpenSignal(target);
    return true;
  }
  return false;
}

function chatRoomLoadContent(target) {
  let users = JSON.parse(sessionStorage.getItem("chat-user-room"));
  document.getElementById("chat-room-user-title").innerText = target;

  if (!(target in users)) {
    document.getElementById("chat-room-message-content").innerText =
      "Chat room is not established with the target.";
    return;
  }

  let rooms = JSON.parse(sessionStorage.getItem("chat-room-history"));
  document.getElementById("chat-room-message-content").innerText =
    rooms[users[target]["room"]];

  users[target]["unread_count"] = 0;
  sessionStorage.setItem("chat-user-room", JSON.stringify(users));
  document.getElementById("chat-room-message-input").focus();
  updateOnlineUnread();
}
