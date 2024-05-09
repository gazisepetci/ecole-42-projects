import * as THREE from "three";
import { CSS2DRenderer, CSS2DObject } from "three-css2drenderer";

const webgl_height = window.innerHeight / 2;
const webgl_aspect_ratio = 5 / 3;
let scene;
let camera;
let renderer;
let labelRenderer;
const clocks = {
  animation: null,
  match: null,
  ball: null,
  player0: null,
  player1: null,
};
const gameElements = {};
const keyIntervals = {
  camera: {},
  player: {},
};
const keyPressed = {};
const cameraKeySet = "rhjklnm";
const playerKeySet = ["w", "s", "ArrowUp", "ArrowDown"];
let clientPlayer;
let matchElapsed = 0;

//

let animated = false;

let player_count = 2;
let bounce_player = "player0";

let max_skor = 5;
let skor_0 = 0;
let skor_1 = 0;
let alertStatus = false;
let alertStatus_1 = false;

let max_set_skor = 1;
let set_skor_0 = 0;
let set_skor_1 = 0;

let match_count = 0;
let tournament_4a = {
  win_1:"a",
  win_2:"b"
};
//
function gameTestInit() {
  scene = new THREE.Scene();
  camera = new THREE.PerspectiveCamera(75, webgl_aspect_ratio, 0.1, 1000);
  renderer = new THREE.WebGLRenderer({ alpha: true, antialias: true });
  labelRenderer = new CSS2DRenderer();


  renderer.setSize(webgl_height * webgl_aspect_ratio, webgl_height);

  renderer.shadowMap.enabled = true;
  renderer.shadowMap.type = THREE.PCFSoftShadowMap; // default THREE.PCFShadowMap

  renderer.domElement.style.position = "absolute";
  renderer.domElement.style.left = "50%";
  renderer.domElement.style.transform = "translateX(-50%)";

  const webtarget = document.getElementById("webgl");
  webtarget.focus();
  webtarget.appendChild(renderer.domElement);

  webtarget.addEventListener("keydown", gameKeyDownEvents);
  webtarget.addEventListener("keyup", gameKeyUpEvents);

  labelRenderer.setSize(window.innerWidth, window.innerHeight);
  labelRenderer.setSize(webgl_height * webgl_aspect_ratio, webgl_height);
  labelRenderer.domElement.style.position = "absolute";
  labelRenderer.domElement.style.left = "50%";
  labelRenderer.domElement.style.transform = "translateX(-50%)";
  //-webkit-transform: translateX(-50%);
  labelRenderer.domElement.style.pointerEvents = "none";

  webtarget.appendChild(labelRenderer.domElement);

  clocks.animation = new THREE.Clock();
  clientPlayer = "player0";
  setSceneVariables();
  if (!animated)
  {
    animate();
  }
}

function animate() {
  if (history.state.path === "/game/pong-local/") {
    animated = true;
    requestAnimationFrame(animate);
  }
  else{
    animated = false;
  }

  if (getCookie("playerData") !== "") {
    if (getCookie("selectedTournament") > 2)
      player_count = Number(getCookie("selectedTournament"));
    if (player_count == 2) {
      var playerData = JSON.parse(getCookie("playerData"));
      gameElements.player0.label.element.textContent = playerData.player1.name;
      gameElements.player1.label.element.textContent = playerData.player2.name;
    }

    gameElements.cube.rotation.x += 0.01;
    gameElements.cube.rotation.y += 0.01;

    if (gameActive ?? false) {
      const matchDelta = clocks.match.getDelta();
      matchElapsed += matchDelta;
      gameElements.timerLabel.element.textContent = matchElapsed.toFixed(1);
      moveBall();
    }
    if (player_count == 4)
      tournament_4vs();
    if (player_count == 3)
      tournament_3vs();
    renderer.render(scene, camera);
    labelRenderer.render(scene, camera);
  }
}

function setSceneVariables() {
  let geometry;
  let material;

  // Scene lights

  gameElements["ambientLight"] = new THREE.AmbientLight(0x404040); // soft white light
  scene.add(gameElements.ambientLight);

  gameElements["directionalLight"] = new THREE.DirectionalLight(0xfce570, 2.5);
  gameElements.directionalLight.position.set(0, -1, 2);
  gameElements.directionalLight.castShadow = true;
  scene.add(gameElements.directionalLight);

  gameElements["pointLight"] = new THREE.SpotLight(0xffffff, 250.0);
  gameElements.pointLight.position.set(0, 0, 20);
  gameElements.pointLight.castShadow = true;
  gameElements.pointLight.shadow.camera.near = 0.1; // default
  gameElements.pointLight.shadow.camera.far = 50000; // default
  scene.add(gameElements.pointLight);

  // Scene base

  geometry = new THREE.PlaneGeometry(50, 30);
  material = new THREE.MeshPhysicalMaterial({ color: 0xb0a0fa });
  material.transmission = 0.4;
  gameElements["board"] = new THREE.Mesh(geometry, material);
  gameElements.board.receiveShadow = true;
  scene.add(gameElements.board);

  // Camera positioning

  resetCamera();

  // Default player setup

  gameElements["player0"] = makePlayer(2, 6, 0xff60a0, -24);
  scene.add(gameElements.player0.mesh);

  gameElements["player1"] = makePlayer(2, 6, 0xff60a0, 24);
  scene.add(gameElements.player1.mesh);
  gameElements.player1.label.element.style.color = "black";
  gameElements.player1.label.element.textContent = "Player1";

  // Default ball setup

  gameElements["ball"] = makeBall(2, 0x109440, 20, 15);
  scene.add(gameElements.ball.mesh);

  const radius = gameElements.ball.mesh.geometry.parameters.radius;
  geometry = new THREE.BoxGeometry(1, 1, 1);
  material = new THREE.MeshPhysicalMaterial({ color: 0xf0a0f0 });
  material.thickness = 1.0;
  material.roughness = 0.9;
  material.transmission = 0.7;
  material.clearcoat = 0.1;
  material.clearcoatRoughness = 0;
  material.ior = 1.25;
  gameElements["cube"] = new THREE.Mesh(geometry, material);
  gameElements.cube.position.set(0, 0, radius * 3 + radius * 2);
  scene.add(gameElements.cube);

  // Labels

  gameElements["timerLabel"] = {};

  gameElements.timerLabel["element"] = document.createElement("div");
  gameElements.timerLabel.element.className = "label";
  gameElements.timerLabel.element.textContent = "00:00";
  gameElements.timerLabel.element.style.backgroundColor = "green";
  gameElements.timerLabel.element.style.color = "white";
  gameElements.timerLabel.element.style.padding = "5px";

  gameElements.timerLabel["object"] = new CSS2DObject(
    gameElements.timerLabel.element
  );
  gameElements.board.add(gameElements.timerLabel.object);

  gameElements["scoreLabel"] = {};
  gameElements.scoreLabel["element"] = document.createElement("div");
  gameElements.scoreLabel.element.className = "label";
  gameElements.scoreLabel.element.id = "pong-score-label";
  gameElements.scoreLabel.element.textContent = set_skor_0 + " - " + set_skor_1; //set skor
  gameElements.scoreLabel.element.style.backgroundColor = "#ffffff30";
  gameElements.scoreLabel.element.style.color = "black";
  gameElements.scoreLabel.element.style.padding = "5px";

  gameElements.scoreLabel["object"] = new CSS2DObject(
    gameElements.scoreLabel.element
  );
  gameElements.timerLabel.object.add(gameElements.scoreLabel.object);

  updateLabelPositions();
}

function makeBall(radius, color, vel_x = 1, vel_y = 1) {
  const geometry = new THREE.SphereGeometry(radius, 20, 16);
  let material = new THREE.MeshPhysicalMaterial({ color: color });
  material.roughness = 0.3;
  material.clearcoat = 0.2;
  material.clearcoatRoughness = 0;
  const ball = new THREE.Mesh(geometry, material);
  ball.position.set(0, 0, ball.geometry.parameters.radius);
  ball.castShadow = true; //default is false
  ball.receiveShadow = true;
  return { mesh: ball, velocity: new THREE.Vector3(vel_x, vel_y, 0) };
}

function makePlayer(width, height, color, posx, velocity = 0.2) {
  const geometry = new THREE.BoxGeometry(width, height, 2);
  const material = new THREE.MeshPhysicalMaterial({ color: color });
  const player = new THREE.Mesh(geometry, material);
  player.position.set(
    posx,
    0,
    geometry.parameters.depth * 0.15 + geometry.parameters.depth / 2
  );
  player.castShadow = true;
  player.receiveShadow = true;

  const playerDiv = document.createElement("div");
  playerDiv.textContent = "Player0";
  playerDiv.style.color = "black";
  playerDiv.style.background = "#ffffff30";
  playerDiv.style.padding = "5px";
  playerDiv.style.borderRadius = "8px";
  const label = new CSS2DObject(playerDiv);
  label.position.z = player.position.z * 5;
  player.add(label);

  return {
    mesh: player,
    velocity: velocity,
    label: { object: label, element: playerDiv },
  };
}

function gameKeyDownEvents(event) {
  event.preventDefault();
  if (keyPressed[event.key] ?? false) return;
  keyPressed[event.key] = true;

  if (cameraKeySet.includes(event.key)) {
    console.log("SETTING INTERVAL...");
    keyIntervals.camera[event.key] = setInterval(moveGameCamera, 5, event.key);
  } else if (playerKeySet.includes(event.key)) {
    keyIntervals.player[event.key] = setInterval(movePlayer, 25, event.key);
  } else if (event.key === "t") {
    toggleMatch();
  } else if (event.key === "x") {
    if (matchStarted) {
      matchFinish();
    } else {
      matchStart();
    }
  }
}

function gameKeyUpEvents(event) {
  event.preventDefault();
  if (cameraKeySet.includes(event.key)) {
    clearInterval(keyIntervals.camera[event.key]);
    keyIntervals.camera[event.key] = null;
    keyPressed[event.key] = false;
  } else if (playerKeySet.includes(event.key)) {
    clearInterval(keyIntervals.player[event.key]);
    keyIntervals.player[event.key] = null;
    keyPressed[event.key] = false;
  } else {
    keyPressed[event.key] = false;
  }
}

function moveGameCamera(key) {
  const movementFactor = 0.1;

  // TODO: camera movement could be improved to keep a certain distance

  if (key === "r") {
    resetCamera();
  } else if (key === "h") {
    camera.position.x -= movementFactor;
  } else if (key === "l") {
    camera.position.x += movementFactor;
  } else if (key === "j") {
    camera.position.y -= movementFactor;
  } else if (key === "k") {
    camera.position.y += movementFactor;
  } else if (key === "n") {
    camera.position.z -= movementFactor;
  } else if (key === "m") {
    camera.position.z += movementFactor;
  }

  camera.lookAt(0, 0, 0);
}

function resetCamera() {
  camera.position.z =
    gameElements.board.geometry.parameters.width /
    2 /
    Math.tan(((camera.fov / 2.0) * Math.PI) / 180.0);
  camera.position.y = -gameElements.board.geometry.parameters.height / 2;
  camera.position.y -= camera.position.z * 0.4;
  camera.position.z -= camera.position.z * 0.3;
  camera.position.x = 0;
  camera.lookAt(0, 0, 0);
}

function movePlayer(key) {
  const movementFactor = 1; //player speed

  const otherPlayer = clientPlayer === "player0" ? "player1" : "player0";
  const player = "ws".includes(key) ? clientPlayer : otherPlayer;
  const new_pos = gameElements[player].mesh.position.clone();

  if (key === "w" && new_pos.y < 12) {
    new_pos.y += movementFactor;
  } else if (key === "s" && new_pos.y > -12) {
    new_pos.y -= movementFactor;
  } else if (key === "ArrowUp" && new_pos.y < 12) {
    new_pos.y += movementFactor;
  } else if (key === "ArrowDown" && new_pos.y > -12) {
    new_pos.y -= movementFactor;
  }
  setPlayer(player, new_pos);
}

function moveBall() {
  const timeDelta = clocks.ball.getDelta();
  const difference = gameElements.ball.velocity
    .clone()
    .multiplyScalar(timeDelta);

  gameElements.ball.mesh.position.lerp(
    new THREE.Vector3(
      gameElements.ball.mesh.position.x + difference.x,
      gameElements.ball.mesh.position.y + difference.y,
      gameElements.ball.mesh.position.z
    ),
    0.9
  );

  const height = gameElements.board.geometry.parameters.height;
  const width = gameElements.board.geometry.parameters.width;


  const radius = gameElements.ball.mesh.geometry.parameters.radius;
  var player_0_max = gameElements["player0"].mesh.position.y + (gameElements["player0"].mesh.geometry.parameters.height / 2);
  var player_0_min = gameElements["player0"].mesh.position.y - (gameElements["player0"].mesh.geometry.parameters.height / 2);

  var player_1_max = gameElements["player1"].mesh.position.y + (gameElements["player1"].mesh.geometry.parameters.height / 2);
  var player_1_min = gameElements["player1"].mesh.position.y - (gameElements["player1"].mesh.geometry.parameters.height / 2);

  var player_wid = gameElements["player0"].mesh.geometry.parameters.width;
  if (Math.abs(gameElements.ball.mesh.position.y) > height / 2) {
    gameElements.ball.velocity.y *= -1;
  }
  if (gameElements.ball.mesh.position.x > width / 2) {
    skor_0++;
    gameElements.scoreLabel.element.textContent = skor_0 + " - " + skor_1;
    resetPositions();
  }//player_1 goal
  if (gameElements.ball.mesh.position.x < -width / 2) {
    skor_1++;
    gameElements.scoreLabel.element.textContent = skor_0 + " - " + skor_1;
    resetPositions();
  }//player_2 goal
  if (gameElements.ball.mesh.position.x - radius <= -25 + player_wid) {
    if (gameElements.ball.mesh.position.y <= player_0_max && gameElements.ball.mesh.position.y >= player_0_min && bounce_player == "player1") {
      bounce_player = "player0";
      gameElements.ball.velocity.x *= -1
    }
  }//player_1 trigger

  if (gameElements.ball.mesh.position.x + radius >= 25 - player_wid) {
    if (gameElements.ball.mesh.position.y <= player_1_max && gameElements.ball.mesh.position.y >= player_1_min && bounce_player == "player0") {
      bounce_player = "player1";
      gameElements.ball.velocity.x *= -1
    }
  }//player_2 trigger

  if (skor_0 > max_skor || skor_1 > max_skor) {
    if (skor_0 > max_skor) {
      set_skor_0++;
      skor_4_tourment(gameElements.player0.label.element.textContent);
      //var playerData = JSON.parse(getCookie("playerData"));
      //playerData.player1.score++;
      //setCookie("playerData", JSON.stringify(playerData), 365);
      gameElements.scoreLabel.element.textContent = "0" + " - " + "0";
      matchFinish();
      OtherMatches();
      skor_0 = 0;
      skor_1 = 0;
    }
    else {
      set_skor_1++;
      skor_4_tourment(gameElements.player1.label.element.textContent);
      //var playerData = JSON.parse(getCookie("playerData"));
      //setCookie("playerData", JSON.stringify(playerData), 365);
      //playerData.player2.score++;
      gameElements.scoreLabel.element.textContent = "0" + " - " + "0";
      matchFinish();
      OtherMatches();
      skor_0 = 0;
      skor_1 = 0;
    }
  }

  gameElements.cube.position.copy(gameElements.ball.mesh.position);
  gameElements.cube.position.setZ(radius * 3 + radius * 2);
}


function skor_4_tourment(player)
{
  var playerData = JSON.parse(getCookie("playerData"));
  if (player == playerData.player1.name) 
  {
    playerData.player1.score++;
    setCookie("playerData", JSON.stringify(playerData), 365);
  }
  else if (player == playerData.player2.name) 
  { 
    playerData.player2.score++;
    setCookie("playerData", JSON.stringify(playerData), 365);
  }
  else if (player == playerData.player3.name) 
  {
    playerData.player3.score++;
    setCookie("playerData", JSON.stringify(playerData), 365);
  }
  else if (player == playerData.player4.name) 
  {
    playerData.player4.score++;
    setCookie("playerData", JSON.stringify(playerData), 365);
  }
}

function tournament_3vs()
{
  if ( match_count == 0 && alertStatus == false) //first match
  {
    var playerData = JSON.parse(getCookie("playerData"));
    gameElements.player0.label.element.textContent = playerData.player1.name;
    gameElements.player1.label.element.textContent = playerData.player2.name;
    alert("Match 1: " + playerData.player1.name + " vs " + playerData.player2.name);
    alertStatus = true;
  }
  if (set_skor_0 >= max_set_skor || set_skor_1 >= max_set_skor)
  {
    match_count++;
    if (set_skor_0 >= max_set_skor && match_count == 1)
    {
      alert("Match 2: " + JSON.parse(getCookie("playerData")).player3.name + " vs " + JSON.parse(getCookie("playerData")).player1.name);
      var playerData = JSON.parse(getCookie("playerData"));
      tournament_4a["win_1"] = playerData.player1.name;
      gameElements.player0.label.element.textContent = playerData.player1.name;
      gameElements.player1.label.element.textContent = playerData.player3.name;
    }
    else if (set_skor_1 >= max_set_skor && match_count == 1)
    {
      alert("Match 2: " + JSON.parse(getCookie("playerData")).player3.name + " vs " + JSON.parse(getCookie("playerData")).player2.name);
      var playerData = JSON.parse(getCookie("playerData"));
      tournament_4a["win_1"] = playerData.player2.name;
      gameElements.player0.label.element.textContent = playerData.player2.name;
      gameElements.player1.label.element.textContent = playerData.player3.name;
    }
    if (set_skor_0 >= max_set_skor && match_count == 2)
    {
      alert(tournament_4a["win_1"] +" won the tournament");
      document.querySelector('.btn-group-vertical').style.display = "block";
      reset_game();
      document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
      document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
    }
    else if (set_skor_1 >= max_set_skor && match_count == 2)
    {
      alert(JSON.parse(getCookie("playerData")).player3.name + " won the tournament");
      document.querySelector('.btn-group-vertical').style.display = "block";
      reset_game();
      document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
      document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
    }
    else
    {
      set_skor_0 = 0;
      set_skor_1 = 0;
    }
  }
}

function tournament_4vs()
{
  if ( match_count == 0 && alertStatus_1 == false) //first match
  {
    var playerData = JSON.parse(getCookie("playerData"));
    gameElements.player0.label.element.textContent = playerData.player1.name;
    gameElements.player1.label.element.textContent = playerData.player2.name;
    alert("Match 1: " + playerData.player1.name + " vs " + playerData.player2.name);
    alertStatus_1 = true;
  }
  if (set_skor_0 >= max_set_skor || set_skor_1 >= max_set_skor)
  {
    match_count++;
    if (set_skor_0 >= max_set_skor && match_count == 1)
    {
      alert("Match 2: " + JSON.parse(getCookie("playerData")).player3.name + " vs " + JSON.parse(getCookie("playerData")).player4.name);
      var playerData = JSON.parse(getCookie("playerData"));
      tournament_4a["win_1"] = playerData.player1.name;
      gameElements.player0.label.element.textContent = playerData.player3.name;
      gameElements.player1.label.element.textContent = playerData.player4.name;
    }
    else if (set_skor_1 >= max_set_skor && match_count == 1)
    {
      alert("Match 2: " + JSON.parse(getCookie("playerData")).player3.name + " vs " + JSON.parse(getCookie("playerData")).player4.name);
      var playerData = JSON.parse(getCookie("playerData"));
      tournament_4a["win_1"] = playerData.player2.name;
      gameElements.player0.label.element.textContent = playerData.player3.name;
      gameElements.player1.label.element.textContent = playerData.player4.name;
    }
    else if (set_skor_0 >= max_set_skor && match_count == 2)
    {
      alert("Match 3: " + tournament_4a["win_1"] + " vs " + JSON.parse(getCookie("playerData")).player3.name);
      var playerData = JSON.parse(getCookie("playerData"));
      tournament_4a["win_2"] = playerData.player3.name;
      gameElements.player0.label.element.textContent = tournament_4a["win_1"];
      gameElements.player1.label.element.textContent = playerData.player3.name;
    }
    else if (set_skor_1 >= max_set_skor && match_count == 2)
    {
      alert("Match 3: " + tournament_4a["win_1"] + " vs " + JSON.parse(getCookie("playerData")).player4.name);
      var playerData = JSON.parse(getCookie("playerData"));
      tournament_4a["win_2"] = playerData.player4.name;
      gameElements.player0.label.element.textContent = tournament_4a["win_1"];
      gameElements.player1.label.element.textContent = playerData.player4.name;
    }
    else if (set_skor_0 >= max_set_skor && match_count == 3)
    {
      alert(tournament_4a["win_1"] +" won the tournament");
      document.querySelector('.btn-group-vertical').style.display = "block";
      reset_game();
      document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
      document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
    }
    else if (set_skor_1 >= max_set_skor && match_count == 3)
    {
      alert(tournament_4a["win_2"] + " won the tournament");
      document.querySelector('.btn-group-vertical').style.display = "block";
      reset_game();
      document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
      document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
    }
    set_skor_0 = 0;
    set_skor_1 = 0;
  }
}

function reset_game()
{
  player_count = 2;
  set_skor_0 = 0;
  set_skor_1 = 0;
  skor_0 = 0;
  skor_0 = 1;
  match_count = 0;
  alertStatus = false;
  alertStatus_1 = false;
  tournament_4a.win_1 = "a";
  tournament_4a.win_2 = "b";
  bounce_player = "player0";
}

function resetPositions() {
  const ball_radius = gameElements.ball.mesh.geometry.parameters.radius;
  const board_widthd2 = gameElements.board.geometry.parameters.width / 2;
  const player_widthd2 =
    gameElements.player0.mesh.geometry.parameters.width / 2;
  const player1_posx = board_widthd2 - player_widthd2;
  const player_depthd2 =
    gameElements.player0.mesh.geometry.parameters.depth / 2;
  const player_posz = player_depthd2 * 0.3 + player_depthd2;
  gameElements.ball.mesh.position.set(0, 0, ball_radius);
  gameElements.player0.mesh.position.set(-player1_posx, 0, player_posz);
  gameElements.player1.mesh.position.set(player1_posx, 0, player_posz);
}

function OtherMatches() {
  if (player_count == 2) {
    if (skor_0 >= max_skor) {
      alert( JSON.parse(getCookie("playerData")).player1.name +" won the match");
      document.querySelector('.btn-group-vertical').style.display = "block";
      reset_game();
      document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
      document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
    }
    else if (skor_1 >= max_skor) {
      alert( JSON.parse(getCookie("playerData")).player2.name +" won the match");
      document.querySelector('.btn-group-vertical').style.display = "block";
      reset_game();
      document.cookie = 'selectedTournament=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
      document.cookie = 'playerData=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
    }
  }
}

function matchStart() {
  clocks.match = new THREE.Clock();
  clocks.ball = new THREE.Clock();
  clocks.player0 = new THREE.Clock();
  clocks.player1 = new THREE.Clock();

  resetPositions();

  matchElapsed = 0.0;
  matchStarted = true;
  gameActive = true;
}

function toggleMatch() {
  if (!gameActive) {
    clocks.ball.getDelta(); // Reset clock.oldtime
    clocks.player0.getDelta();
    clocks.player1.getDelta();
    clocks.match.getDelta();
  }

  gameActive = !gameActive;
}

function matchFinish() {
  clocks.match = null;
  clocks.ball = null;
  clocks.player0 = null;
  clocks.player1 = null;

  matchElapsed = null;
  matchStarted = false;
  gameActive = false;
}

function setPlayer(player, pos) {
  const pos_z = gameElements[player].mesh.position.z;
  gameElements[player].mesh.position.lerp(
    new THREE.Vector3(pos.x, pos.y, pos_z),
    0.2
  );
}

function setBall(pos, vel) {
  const pos_z = gameElements.ball.mesh.position.z;
  gameElements.ball.mesh.position.lerp(
    new THREE.Vector3(pos.x, pos.y, pos_z),
    0.4
  );
  gameElements.ball.velocity.x = vel.x;
  gameElements.ball.velocity.y = vel.y;
}

function initBoard(width, height) {
  scene.remove(gameElements.board);
  disposeObj(gameElements.board);

  let geometry = new THREE.PlaneGeometry(width, height);
  let material = new THREE.MeshPhysicalMaterial({ color: 0xb0a0fa });
  material.transmission = 0.4;
  gameElements["board"] = new THREE.Mesh(geometry, material);
  gameElements.board.receiveShadow = true;
  scene.add(gameElements.board);

  updateLabelPositions();
  gameElements.board.add(gameElements.timerLabel.object);
  gameElements.timerLabel.object.add(gameElements.scoreLabel.object);
}

function initPlayer(player, pos, vel, width, height, nickname, username) {
  scene.remove(gameElements[player].mesh);
  disposeObj(gameElements[player].mesh);
  gameElements[player] = makePlayer(width, height, 0xff60a0, pos.x, vel);
  gameElements[player].label.element.textContent = nickname;

  if (username === getCookie("username")) {
    clientPlayer = player;
  }

  //setPlayer(player, pos);
  scene.add(gameElements[player].mesh);
}

function initBall(pos, vel, rad) {
  scene.remove(gameElements.ball.mesh);
  disposeObj(gameElements.ball.mesh);
  gameElements["ball"] = makeBall(rad, 0x109440, vel.x, vel.y);
  //setBall(pos, vel);

  updateLabelPositions();

  scene.add(gameElements.ball.mesh);
}

function hasMatchStarted() {
  return matchStarted;
}

function isGameActive() {
  return gameActive;
}

function disposeObj(obj) {
  while (obj.children.length > 0) {
    disposeObj(obj.children[0]);
    obj.remove(obj.children[0]);
  }
  if (obj.geometry) obj.geometry.dispose();

  if (obj.material) {
    //in case of map, bumpMap, normalMap, envMap ...
    Object.keys(obj.material).forEach((prop) => {
      if (!obj.material[prop]) return;
      if (
        obj.material[prop] !== null &&
        typeof obj.material[prop].dispose === "function"
      )
        obj.material[prop].dispose();
    });
    obj.material.dispose();
  }
}

function updateLabelPositions() {
  const height = gameElements.board.geometry.parameters.height;
  const radius = gameElements.ball.mesh.geometry.parameters.radius;
  gameElements.timerLabel.object.position.set(0, height / 2, radius * 5);
  gameElements.scoreLabel.object.position.set(0, 0, 5);
}

function getCookie(name) {
  var cookieName = name + "=";
  var decodedCookie = decodeURIComponent(document.cookie);
  var cookieArray = decodedCookie.split(';');
  for (var i = 0; i < cookieArray.length; i++) {
    var cookie = cookieArray[i].trim();
    if (cookie.indexOf(cookieName) === 0) {
      return cookie.substring(cookieName.length, cookie.length);
    }
  }
  return "";
}

// Çerez değerini ayarlamak için yardımcı bir fonksiyon
function setCookie(name, value, days) {
  var expires = "";
  if (days) {
    var date = new Date();
    date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
    expires = "; expires=" + date.toUTCString();
  }
  document.cookie = name + "=" + value + expires + "; path=/";
}


let matchStarted;
let gameActive;
window.lGameTestInit = gameTestInit;
window.lGameInitBoard = initBoard;
window.lGameSetPlayer = setPlayer;
window.lGameSetBall = setBall;
window.lGameInitPlayer = initPlayer;
window.lGameInitBall = initBall;
window.lGameStartMatch = matchStart;
window.lGameFinishMatch = matchFinish;
window.lGameStarted = hasMatchStarted;
window.lGameActive = isGameActive;