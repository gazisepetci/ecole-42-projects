function homeUpdateLoop() {
  setTimeout(homeUpdateOnlineStatus, 300);
  if (intervalInventory.home === null) {
    intervalInventory.home = setInterval(homeUpdateOnlineStatus, 5000);
  }
}

function homeUpdateOnlineStatus() {
  if (!history.state.path.startsWith("/home/")) {
    clearInterval(intervalInventory.home);
    intervalInventory.home = null;
    console.log("Home online status loop is terminated"); // DEBUG
    return;
  }

  if (!isSocketOpen(chatSocket)) {
    return;
  }

  sendChatListSignal();
  setTimeout(homeUpdateOnlineContent(), 300);
}

function homeUpdateOnlineContent() {
  const list = document.getElementById("home-friend-list");
  const online_list = JSON.parse(sessionStorage.getItem("online-info"));
  
  if ("users" in online_list) {
    for (const child of list.children) {
      const splitted = child.id.split("-");
      const username = splitted[splitted.length - 1];
      const status_span = child.querySelector("span");

      if (online_list.users.includes(username)) {
        status_span.setAttribute("class", "online_icon");
      } else {
        status_span.setAttribute("class", "offline_icon");
      }
    }
  }
}