const navFuncMap = {
  Home: bindHome,
  Login: bindLogin,
  Pong: bindPongRoom,
  "L-Pong": bindPongLocal,
  Chat: bindChatRoom,
  ChatRoom: bindChatRoom,
  Profile: bindProfile,
};

const urlFuncMap = {
  "/home/": bindHome,
  "/user/register/": bindRegister,
  "/user/login/": bindLogin,
  "/user/profile/": bindProfile,
  "/user/two-factor/": bindTwoFactor,
  "/game/pong/": bindPongRoom,
  "/game/pong-local/": bindPongLocal,
  "/chat/": bindChatRoom,
  "/chat/test/": bindChatRoom,
};

const items = document.getElementsByClassName("nav-item");
const main_content = document.getElementById("main-content");
let bindFunc;
let chatSocket;
let pongSocket;
let pongRoomUrl = "/game/pong/";
let intervalInventory = {home: null, pong_local: null};
const observer = new MutationObserver(function (mutations) {
  for (const mutation of mutations) {
    console.log(mutation); // DEBUG

    mutation.addedNodes.forEach((element) => {
      // === DEBUG ===
      if (!element.tagName) {
        console.log("non class found! " + element.nodeName);
      } else if (element.classList.contains("eoc")) {
        console.log("eoc found!");
        updateContentAnchors();
        if ((bindFunc !== null) & (typeof bindFunc !== "undefined")) {
          bindFunc();
          bindFunc = null;
        }
      } else {
        console.log("other class found! " + element.className);
      }
      // === DEBUG ===
    });
  }
});

observer.observe(main_content, { childList: true });

for (i = 0; i < items.length; i++) {
  const anchor = items[i].querySelector("a");

  if (anchor.text !== "Logout") {
    anchor.addEventListener("click", (e) => {
      e.preventDefault();
      loadContent(e.currentTarget);
    });
  } else {
    bindLogout(anchor);
  }
}

window.addEventListener("load", (e) => {
  if (history.state == null) {
    history.replaceState(getState("/home/", urlFuncMap["/home/"]), "", "");
  }
  loadHistoryEvent(history);
});

window.addEventListener("unload", (e) => {
  closeSocket(chatSocket);
  closeSocket(pongSocket);
});

window.addEventListener("popstate", (e) => {
  loadHistoryEvent(e);
});