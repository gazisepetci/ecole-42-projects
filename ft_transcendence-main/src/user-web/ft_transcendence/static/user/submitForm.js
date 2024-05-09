function submitForm(formInstance, toBind) {
  const form = formInstance;
  const formData = new FormData(form);

  console.log("SubmitForm Called"); // DEBUG

  let postData = {};
  formData.forEach((value, key) => {
    postData[key] = value;
  });

  const requestUrl = form.getAttribute("action");

  console.log("Calling fetch..."); // DEBUG

  fetch(requestUrl, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify(postData),
  })
    .then((response) => response.json())
    .then((data) => {
      if (data.success) {
        if (typeof toBind === "function") {
          bindFunc = toBind;
        }
        loadContent(data.redirect);
      } else {
        const target = document.getElementById("form_error");
        target.innerHTML = "";
        for (const error of data.errors) {
          // fix : data.errors undefined
          newElement = document.createElement("div");
          newElement.setAttribute("role", "alert");
          newElement.classList.add("alert", "alert-danger");
          newElement.innerText = error;
          target.appendChild(newElement);
        }
      }
    });
}

function fetchOAuthUrl() {
  // OAuth URL'sini al ve yeni bir pencere aç
  fetch("/user/get-oauth-url/")
    .then((response) => response.json())
    .then((data) => {
      const oauthWindow = window.open(
        data.oauth_url,
        "oauthWindow",
        "width=600,height=700"
      );

      // OAuth penceresi kapandığında kullanıcı oturumunu kontrol et
      const checkWindowClosed = setInterval(() => {
        if (oauthWindow.closed) {
          clearInterval(checkWindowClosed);
          loadContent(data.redirect);
        }
      }, 1000);
    })
    .catch((error) => console.error("Error fetching OAuth URL:", error));
}

