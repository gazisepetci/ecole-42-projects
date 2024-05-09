async function fetchWithJWT(url, options = {}) {
  const accessToken = getCookie("access_token");
  if (accessToken) {
    options.headers = {
      ...options.headers,
      Authorization: `Bearer ${accessToken}`,
    };
  }

  const response = await fetch(url, options);

  if (response.status === 401 && accessToken) {
    await refreshAccessToken();
    const newAccessToken = getCookie("access_token");
    if (newAccessToken) {
      options.headers.Authorization = `Bearer ${newAccessToken}`;
      return fetch(url, options);
    } else {
      // Invalid refresh token
      return response;
    }
  }

  return response;
}

async function refreshAccessToken() {
  // Implement logic to send refresh token to server and get new access token

  console.log("Refreshing token..."); // DEBUG

  const response = await fetch("/user/refresh-token/");
}