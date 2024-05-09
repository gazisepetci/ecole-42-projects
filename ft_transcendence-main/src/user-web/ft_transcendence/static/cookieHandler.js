function getCookie(cName) {
  const cookieValue = document.cookie
    .split("; ")
    .find((row) => row.startsWith(cName))
    ?.split("=")[1];

  return cookieValue;
}

function checkCookie(cName) {
  if (
    document.cookie
      .split(";")
      .some((item) => item.trim().startsWith(cName + "="))
  ) {
    return true;
  }
  return false;
}

// function setCookie(cName, cValue, isSecure = false) {
//   cookie = cName + "=" + cValue + "; SameSite=Strict";
//
//   if (isSecure) {
//     cookie = cookie + "; Secure";
//   }
//   document.cookie = cookie;
// }

// function deleteCookie(cName) {
//
//   console.log("Deleting cookie: " + cName); // DEBUG
//
//   document.cookie = cName + "=; expires=Thu, 01 Jan 1970 00:00:00 GMT; Secure";
// }