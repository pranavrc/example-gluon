var gMiniumBreakInt = 50;
var gCurrentlyBreakInt = 0;
var gPlayerReference = null;
var gLastScoreUpdateInt = 0;
var gEndedGameBool = false;
var gTrapReference = null;
var gStarReference = null;
function initialize(){
    Component.paused = false;
}
function start(){
  Game.score = 0;
  Game.end = false;
  
  gTrapReference = Game.getFromScene("Trap");
  gStarReference = Game.getFromScene("Star");
  gPlayerReference = Game.clone(Game.getFromScene("Player"));
  gPlayerReference.setPosition(-25, -40);
  gPlayerReference.enabled = true;
}

function update(time){
  if(Game.end == false){
    this.deployTrap();
    if(Game.score%6 ==0 && Game.score != gLastScoreUpdateInt){
      this.updateScore(Game.score/6);
    }
  }else{
    if(gEndedGameBool==false){
      this.end();
    }
    if(this.GameObject.Key_Reset.isActionHeld()){
      this.resetGame();
    }
  }

    
}
function deployTrap(){
  gCurrentlyBreakInt++;
  if(gCurrentlyBreakInt >=gMiniumBreakInt){
    if(Math.random()*11 > 9){
      var trap = Game.clone(gTrapReference);
      trap.setPosition(50,-40);
      trap.enabled = true;
      gCurrentlyBreakInt =0;
    }
  }

}
function updateScore(score){
  gLastScoreUpdateInt =score*6;
  var star =Game.clone(gStarReference);
  star.setPosition(((score%6)*8)-20,Math.floor(score/6)*8);
  star.enabled=true;

}
function end(){
  gEndedGameBool = true;
  var score =Game.clone(Game.getFromScene("ScoreText"));
  score.setPosition(-30,0);
  score.enabled = true;
  var resetText =Game.clone(Game.getFromScene("ResetText"));
  resetText.setPosition(-5,-10);
  resetText.enabled = true;
  
}
function resetGame(){
  Game.resetCurrentScene();
}