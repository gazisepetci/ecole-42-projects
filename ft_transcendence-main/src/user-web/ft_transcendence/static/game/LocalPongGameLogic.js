var playerDataCookie;
var playerData;

function ButtonCheck() {
    let lStartButton = document.getElementById('lStartGame');

    lStartButton.addEventListener('click', function () {
        let radioButtons = document.querySelectorAll('input[name="vbtn-radio"]');
        if (radioButtons[0].checked || radioButtons[1].checked) {
            // Seçilen turnuva bilgisini cookie'den sil
            document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
            // Oyuncu verilerini cookie'den sil
            document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';

            if (radioButtons[0].checked)
                open1v1Modal();
            else if (radioButtons[1].checked)
                openTournamentModal();
        }
        else {
            alert('Please select a game mode');
        }
    });
}

function open1v1Modal() {
    var modalHtml = `
    <div class="modal" tabindex="-1" id="playerModal">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Players</h5>
            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
          </div>
          <div class="modal-body">
            <label for="player1">1. Player Name:</label>
            <input type="text" class="form-control" id="player1" placeholder="1. Player Name">

            <label for="player2" class="mt-2">2. Player Name:</label>
            <input type="text" class="form-control" id="player2" placeholder="2. Player Name">
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
            <button type="button" class="btn btn-primary" id="savePlayers">Save</button>
          </div>
        </div>
      </div>
    </div>`;

    var modalElement = document.createElement('div');
    modalElement.innerHTML = modalHtml;

    // Insert Modal in Body
    document.body.appendChild(modalElement);

    // Open Modal
    var playerModal = new bootstrap.Modal(document.getElementById('playerModal'));
    playerModal.show();

    // Click on the Save button
    document.getElementById('savePlayers').addEventListener('click', function () {
        var player1Value = document.getElementById('player1').value;
        var player2Value = document.getElementById('player2').value;

        // Check if the fields are empty
        if (!player1Value.trim() || !player2Value.trim()) {
            alert('Please fill in all fields.');
            return;
        }

        // Check if player names are different
        if (player1Value.trim() === player2Value.trim()) {
            alert('Player names must be different.');
            return;
        }

        // Create Cookie Object
        var playerData = {
            player1: {
                name: player1Value,
                score: 0,
                matchPlayed: false
            },
            player2: {
                name: player2Value,
                score: 0,
                matchPlayed: false
            }
        };

        // Convert Object to JSON
        var playerDataJSON = JSON.stringify(playerData);

        // Create Cookie
        document.cookie = `playerData=${playerDataJSON}; path=/;`;

        // Modalı off
        playerModal.hide();
        // Ana kısımdaki butonları ve radio inputları kaldır
        var mainButtons = document.querySelector('.btn-group-vertical');
        mainButtons.style.display = 'none';
    });
}

function openTournamentModal() {
    var modalHtml = `
    <div class="modal" tabindex="-1" id="tournamentModal">
      <div class="modal-dialog">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Tournament Options and Players</h5>
            <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
          </div>
          <div class="modal-body">
            <div class="form-check">
              <input class="form-check-input" type="radio" name="tournamentOptions" id="option1" value="3">
              <label class="form-check-label" for="option1">
              3 Player Tournament Mode
              </label>
            </div>
            <div class="form-check">
              <input class="form-check-input" type="radio" name="tournamentOptions" id="option2" value="4">
              <label class="form-check-label" for="option2">
              4 Player Tournament Mode
              </label>
            </div>
            <div id="inputContainer" class="mt-3"></div>
          </div>
          <div class="modal-footer">
            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Close</button>
            <button type="button" class="btn btn-primary" id="saveTournament">Save</button>
          </div>
        </div>
      </div>
    </div>`;

    // Modalı sayfaya eklemek için div elementini oluştur
    var modalElement = document.createElement('div');
    modalElement.innerHTML = modalHtml;

    // Body içerisine modalı ekle
    document.body.appendChild(modalElement);

    // Modalı aç
    var tournamentModal = new bootstrap.Modal(document.getElementById('tournamentModal'));
    tournamentModal.show();

    // Radio butonlarına tıklandığında
    var radioButtons = document.querySelectorAll('input[name="tournamentOptions"]');
    radioButtons.forEach(function (radioButton) {
        radioButton.addEventListener('change', function () {
            var selectedValue = parseInt(this.value);

            // Seçilen sayı kadar input alanı ekleyin
            var inputContainer = document.getElementById('inputContainer');
            inputContainer.innerHTML = ''; // Önceki input alanlarını temizle

            for (var i = 0; i < selectedValue; i++) {
                var label = document.createElement('label');
                label.htmlFor = 'player' + (i + 1);
                label.innerText = `${i + 1}. Player Name:`;
                inputContainer.appendChild(label);

                var input = document.createElement('input');
                input.type = 'text';
                input.classList.add('form-control', 'mt-2');
                input.id = 'player' + (i + 1);
                input.placeholder = `${i + 1}. Player Name`;
                inputContainer.appendChild(input);
            }
        });
    });

    // Seç butonuna tıklanınca
    document.getElementById('saveTournament').addEventListener('click', function () {
        var selectedOption = document.querySelector('input[name="tournamentOptions"]:checked');

        if (!selectedOption) {
            alert('Please select a tournament option.');
            return;
        }

        var selectedValue = selectedOption.value;

        // Turnuva seçeneğini JSON formatında sakla
        var playerData = {};
        var selectedTournament = selectedValue;
        var playerNames = {};

        var inputs = document.querySelectorAll('#inputContainer input');
        for (var i = 0; i < inputs.length; i++) {
            var playerName = inputs[i].value.trim();

            if (playerName !== '') {
                var playerKey = 'player' + (i + 1);
                playerData[playerKey] = {
                    name: playerName,
                    score: 0,
                    matchPlayed: false
                };

                // Oyuncu isimlerini kontrol et
                if (playerNames[playerName]) {
                    alert('Player names must be different.');
                    return; // Fonksiyondan çık
                }
                playerNames[playerName] = true;
            }
        }

        if (Object.keys(playerData).length < selectedValue) {
            alert('Please fill in all player name fields.');
            return;
        }

        // Turnuva verisini JSON formatında cookie olarak kaydet
        document.cookie = `playerData=${JSON.stringify(playerData)}; path=/;`;
        document.cookie = `selectedTournament=${selectedTournament}; path=/;`;

        tournamentModal.hide();
        // Ana kısımdaki butonları ve radio inputları kaldır
        var mainButtons = document.querySelector('.btn-group-vertical');
        mainButtons.style.display = 'none';
    });
}

// Cookie'den veriyi çekme fonksiyonu
function getCookie(name) {
    const value = `; ${document.cookie}`;
    const parts = value.split(`; ${name}=`);
    if (parts.length === 2) return parts.pop().split(';').shift();
}

// Oyuncu bilgilerini ve puanlarını çekme
function getPlayersData() {
    var players = [];

    for (var key in playerData) {
        if (playerData.hasOwnProperty(key)) {
            players.push({
                name: playerData[key].name,
                score: playerData[key].score
            });
        }
    }
    return players;
}

// Puanlara göre oyuncuları sırala
function sortPlayersByPoints() {
    var players = getPlayersData();
    players.sort((a, b) => b.score - a.score); // Büyükten küçüğe sırala
    return players;
}

function setCookie(name, value, days) {
    var expires = "";
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + value + expires + "; path=/";
}

var lPongLink = document.querySelector('a[href="/game/pong-local/"]');

// L-Pong linkine tıklanma eventi
lPongLink.addEventListener("click", function (event) {
    // Event tetiklendiğinde yapılacak işlemler
    // Seçilen turnuva bilgisini cookie'den sil
    document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
    // Oyuncu verilerini cookie'den sil
    document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
});

function ScoreboardUpdater() {

    if (!history.state.path.startsWith("/game/pong-local/")) {
        clearInterval(intervalInventory.pong_local);
        intervalInventory.pong_local = null;
        console.log("Pong local scoreboard updater interval is cleared"); // DEBUG
        return;
    }

    // Cookie'den playerData verisini çek
    playerDataCookie = getCookie('playerData');

    // Eğer cookie'de playerData varsa, bu değeri bir objeye dönüştür
    playerData = playerDataCookie ? JSON.parse(playerDataCookie) : {};

    // Puanlara göre oyuncuları sırala
    var sortedPlayers = sortPlayersByPoints();

    // Skorborddaki konteyneri seç
    var scoreboardContainer = document.getElementById('local-pong-player-scores');

    // Mevcut skorbordu temizle
    if (scoreboardContainer !== null && scoreboardContainer.innerHTML !== '')
        scoreboardContainer.innerHTML = '';

    // Her bir oyuncu için skorbordu güncelle
    sortedPlayers.forEach(function (player, index) {
        var playerRow = document.createElement('div');
        playerRow.classList.add('row');

        // Oyuncu adını ekleyin
        var playerNameCol = document.createElement('div');
        playerNameCol.classList.add('col');
        playerNameCol.innerText = `${player.name}`;
        playerRow.appendChild(playerNameCol);

        // Puan bilgisini ve yıldızı ekleyin
        var playerScoreCol = document.createElement('div');
        playerScoreCol.classList.add('col');

        var scoreInfoRow = document.createElement('div');
        scoreInfoRow.classList.add('row', 'justify-content-between');

        var pointsCol = document.createElement('div');
        pointsCol.classList.add('col');
        pointsCol.innerText = `${player.score}W`;

        // En yüksek puan alan oyuncuya yıldız ekleyin
        if (index === 0) {
            playerNameCol.innerHTML += ' <span class="position-absolute start-50 text-warning"><i class="bi bi-star-fill"></i></span>';
        }

        scoreInfoRow.appendChild(pointsCol);
        playerScoreCol.appendChild(scoreInfoRow);
        playerRow.appendChild(playerScoreCol);

        scoreboardContainer.appendChild(playerRow);
    });
}

function LocalPongLogicInit() {
    ButtonCheck();
    if (intervalInventory.pong_local === null) {
        intervalInventory.pong_local = setInterval(ScoreboardUpdater, 500);
    }
}