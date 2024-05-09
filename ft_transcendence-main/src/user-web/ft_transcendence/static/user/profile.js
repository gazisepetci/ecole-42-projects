function profileEvents() {
  document
    .getElementById("profilePhotoForm")
    .addEventListener("submit", function (event) {
      event.preventDefault(); // Formun normal submit işlemi engellenir.

      const fileInput = document.getElementById("profilePhoto");
      if (fileInput.files.length === 0) {
        alert("Please select a file to upload.");
        return;
      }

      const formData = new FormData();
      formData.append("image", fileInput.files[0]); // 'image' yerine sunucu tarafında beklenen alan adını kullanın.

      fetchWithJWT("/user/get_image/", {
        // API endpoint'inizi doğru yolla güncelleyin.
        method: "PUT",
        body: formData,
      })
        .then((response) => {
          if (!response.ok) {
            throw response;
          }
          return response.json();
        })
        .then((data) => {
          if (data.success) {
            alert("Profile photo updated successfully!");
          } else {
            if (data.errors) {
              alert(
                "Failed to update profile photo: " + data.errors.join(", ")
              );
            } else {
              alert("Failed to update profile photo: Unknown error");
            }
          }
        })
        .catch((error) => {
          error
            .json()
            .then((errData) => {
              if (errData && errData.errors) {
                console.error(
                  "Error updating profile photo:",
                  errData.errors.join(", ")
                );
              } else {
                console.error(
                  "Error updating profile photo: Failed to parse error message"
                );
              }
            })
            .catch(() => {
              console.error(
                "Error updating profile photo: Network or parse error"
              );
            });
        });
    });

  document
    .getElementById("passwordForm")
    .addEventListener("submit", function (event) {
      event.preventDefault(); // Formun varsayılan submit işlemini engelle

      const oldPassword = document.getElementById("oldPassword").value;
      const newPassword = document.getElementById("newPassword").value;
      const confirmPassword = document.getElementById("confirmPassword").value;

      fetchWithJWT("/user/change-password/", {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
          old_password: oldPassword,
          new_password1: newPassword,
          new_password2: confirmPassword,
        }),
      })
        .then((response) => response.json()) // Yanıtı JSON olarak ayrıştır
        .then((data) => {
          if (data.success) {
            alert("Password changed successfully!");
          } else {
            // Sunucudan dönen hata mesajlarını göster
            alert("Failed to change password: " + data.errors.join(", "));
          }
        })
        .catch((error) => {
          console.error("Error:", error);
          alert("An error occurred while changing the password.");
        });
    });

  document
    .getElementById("deleteProfile")
    .addEventListener("click", function () {
      if (
        confirm(
          "Are you sure you want to delete your profile? This action cannot be undone."
        )
      ) {
        fetchWithJWT("/user/delete-account/", {
          method: "DELETE",
        })
          .then(() => {
            loadContent("/home/"); // Redirect to home page after deletion
          })
          .catch((error) => {
            console.error("Error:", error);
          });
      }
    });

  document
    .getElementById("profile-2fa-setting-submit")
    .addEventListener("click", submitTwoFactorSetting);

  const addFriendButton = document.getElementById("add-friend-button");
  const delFriendButton = document.getElementById("del-friend-button");
  const blockUserButton = document.getElementById("block-user-button");
  const unblkUserButton = document.getElementById("unblock-user-button");
  if (addFriendButton !== null) addFriendButton.addEventListener("click", function () { friendRequest("PUT"); });
  if (delFriendButton !== null) delFriendButton.addEventListener("click", function () { friendRequest("DELETE"); });
  if (blockUserButton !== null) blockUserButton.addEventListener("click", function () { blockRequest("PUT"); });
  if (unblkUserButton !== null) unblkUserButton.addEventListener("click", function () { blockRequest("DELETE") });
}

function submitTwoFactorSetting() {
  const twoFactorType = document.getElementById("twoFactorType").value;

  // Eğer 2FA devre dışı bırakılıyorsa, DELETE isteği gönder
  if (twoFactorType === "0") {
    fetchWithJWT("/user/remove-two-factor/", {
      method: "DELETE",
      headers: {
        "Content-Type": "application/json",
      },
    })
      .then((response) => response.json())
      .then((data) => {
        alert(data.message);
      })
      .catch((error) => {
        console.error("Error:", error);
        alert("Error updating 2FA settings.");
      });
  } else {
    // Eğer 2FA etkinleştiriliyorsa, PUT isteği gönder
    fetchWithJWT(`/user/add-two-factor/${twoFactorType}/`, {
      method: "PUT",
      headers: {
        "Content-Type": "application/json",
      },
    })
      .then((response) => response.json())
      .then((data) => {
        if (data.success && twoFactorType === "3") {
          alert(
            `2FA set successfully. Use this TOTP secret for setup: ${data.secret}`
          );
        } else {
          alert(data.message);
        }
      })
      .catch((error) => {
        console.error("Error:", error);
        alert("Error updating 2FA settings.");
      });
  }
}

function friendRequest(method) {
  const username = document.getElementById("targetUsername").innerText;
  
  fetchWithJWT("/user/friend-request/" + username + "/", {
    method: method,
  })
    .then((response) => response.json())
    .then((data) => {
      alert(data.success || data.error);
    })
    .catch((error) => {
      console.error("Error:", error);
    });
}

function blockRequest(method) {
  const username = document.getElementById("targetUsername").innerText;

  fetchWithJWT("/user/block-request/" + username + "/", {
    method: method,
  })
    .then((response) => response.json())
    .then((data) => {
      alert(data.success || data.error);
    })
    .catch((error) => {
      console.error("Error:", error);
    });
}
