const HEXMAP = "0123456789ABCDEF".split("");


document.querySelector("button").onclick = generateHexVal;
document.querySelector("span").onclick = NotificationSlide;

function generateHexVal() {
  let randomVals = [],
    HEXVAL = ["#"];
  while (randomVals.length < 6) {
    randomVals.push(randomNumber(16));
  }
  randomVals.forEach((val) => {
    HEXVAL.push(HEXMAP[val]);
  });
  updateUI(HEXVAL.join(""));
  return true;
}

function randomNumber(MAX) {
  return Math.floor(Math.random() * Math.floor(MAX));
}
function updateUI(HEXVAL) {
    updateBackgroundColor(HEXVAL);
    updateHexCode(HEXVAL);
}

function updateBackgroundColor(HEXVAL) {
    document.body.style.backgroundColor = HEXVAL;
    document.getElementById("themeColor").content = HEXVAL;

}
function updateHexCode(HEXVAL) {
    document.getElementById("HexVal").innerText = HEXVAL;
}
function NotificationSlide() {
  const NOTIFICATION = document.getElementById('Notification'),
        HEXVALUE = document.querySelector('span').innerText;
        HOLDER = document.getElementById('ValueHolder');
  NOTIFICATION.style.top = "20px";
  setTimeout(()=>{NOTIFICATION.style.top = "-8.5vh"}, 2000);
  HOLDER.value = HEXVALUE;
  HOLDER.select();
  HOLDER.setSelectionRange(0, 99999);
  document.execCommand("copy");
}