function bindLogin() {
  //addEventListener on #loginButton for submitForm()
  //addEventListener on .oauth-button for 42Login

  document
    .getElementById("loginSubmitButton")
    .addEventListener("click", (e) => {
      e.preventDefault();
      submitForm(e.currentTarget.form, bindTwoFactor);
    });

  console.log("called bindLogin()"); // DEBUG, Should be called when login page appears

  const a_42login = document.getElementById("42LoginLink");
  a_42login.addEventListener("click", (e) => {
    e.preventDefault();
    fetchOAuthUrl();
  });
}

function bindRegister() {
  console.log("called bindRegister()"); // DEBUG, Should be called when register page appears

  document
    .getElementById("registerSubmitButton")
    .addEventListener("click", (e) => {
      e.preventDefault();
      submitForm(e.currentTarget.form, bindLogin);
    });
}

function bindTwoFactor() {
  document.getElementById("2FASubmitButton").addEventListener("click", (e) => {
    e.preventDefault();
    submitForm(e.currentTarget.form);
  });
}

function bindLogout(anchorInstance) {
  // Logout is supposed to work in the exactly opposite way
  // The content should be requested after logout is complete

  sessionStorage.clear();

  anchorInstance.addEventListener("click", (e) => {
    e.preventDefault();
    fetch(anchorInstance.href)
      .then((response) => response.json())
      .then((data) => {
        loadContent(data.redirect);
      });
  });
}

function bindHome() {
  homeUpdateLoop();
}

function bindRanking() {}

function bindProfile() {
  profileEvents();
}

function bindChatRoom() {
  chatRoom();
}

function bindPongRoom() {
  pongRoom();
  window.gameTestInit();
}

function bindPongLocal() {
  window.lGameTestInit();
  LocalPongLogicInit();
  document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
  document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
}

/*function bindAnchor(anchorInstance) {
  anchorInstance.removeEventListener("click", loadContentEvent);

  anchorInstance.addEventListener("click", (e) => {
    e.preventDefault();
    // bindFunc = func;
    loadContent(e.currentTarget);
  });
}*/

function updateContentAnchors() {
  /*
    Set SPA switch for all anchors in element (#main-content)
    */

  console.log("calling updatecontentAnchors..."); // DEBUG
  
  const element = document.getElementById("main-content");
  const anchors = element.querySelectorAll("a");

  for (let i = 0; i < anchors.length; i++) {
    anchors[i].addEventListener("click", loadContentEvent);
  }
}

function loadContent(anchorInstanceOrPath, pushHistory = true) {
  let requestUrl;

  if (typeof anchorInstanceOrPath === "string") {
    requestUrl = anchorInstanceOrPath;
  } else {
    requestUrl = anchorInstanceOrPath.getAttribute("href");
  }

  fetchWithJWT(requestUrl)
    .then((response) => response.text())
    .then((text) => {
      const element = document.getElementById("main-content");

      if (pushHistory) {
        const state = getState(requestUrl, bindFunc);
        history.pushState(state, "", "");
      }

      for (const key of Object.keys(urlFuncMap)) {
        if (requestUrl.startsWith(key)) {
          bindFunc = urlFuncMap[key];
          break;
        }
      }

      element.innerHTML = text;
    });
  checkUserSession();
  return false;
}

function loadContentEvent(event) {
  event.preventDefault();
  loadContent(event.currentTarget);
}

function loadHistoryEvent(event) {
  const path = event.state.path;
  const binder_name = event.state.binder_name;
  const binder = binder_name !== null ? window[binder_name] : null;

  //console.log(path); // DEBUG
  //console.log(binder_name); // DEBUG
  //console.log(binder) // DEBUG

  bindFunc = binder;
  loadContent(path, false);
}

function getState(path, binder) {
  return {
    path: path,
    binder_name:
      binder !== null && typeof binder !== "undefined" ? binder.name : null,
  };
}

function closeSocket(socketInstance) {
  if (typeof socketInstance === "object") {
    if (socketInstance.readyState === WebSocket.OPEN) {
      socketInstance.close();
    }
  }
}