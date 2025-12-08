#include <U8g2lib.h>
#include <Keypad.h>

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const byte cell = 4;
const byte gridW = 128 / cell;
const byte gridH = 64 / cell;

byte snakeX[120], snakeY[120];
byte length = 3;

int dirX = 1, dirY = 0;
byte foodX, foodY;

unsigned int score = 0;
unsigned int highScore = 0;

void spawnFood() {
  foodX = random(0, gridW);
  foodY = random(0, gridH);
}

void resetGame() {
  length = 3;
  dirX = 1; dirY = 0;
  score = 0;

  for (byte i = 0; i < length; i++) {
    snakeX[i] = 6 - i;
    snakeY[i] = 5;
  }

  spawnFood();
}

void drawGameOver() {
  String msg = "GAME OVER!";
  int len = msg.length() * 12; // approx char width
  int pos = 128;

  for (int t = 0; t < len + 128; t+=4) {
    u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_logisoso16_tr);
      u8g2.drawStr(pos - t, 30, msg.c_str());
      u8g2.setFont(u8g2_font_6x12_tr);
      char buf[20];
      sprintf(buf, "Score:%u", score);
      u8g2.drawStr(0, 55, buf);
      sprintf(buf, "Best:%u", highScore);
      u8g2.drawStr(80, 55, buf);

    } while(u8g2.nextPage());
    delay(150);
  }

  char k = 0;
  while (!k) k = keypad.getKey();
  resetGame();
}

void readKeypad() {
  char key = keypad.getKey();
  if (!key) return;

  switch(key) {
    case '1': if (dirY != 1) { dirX=0; dirY=-1; } break; // UP
    case '7': if (dirY != -1) { dirX=0; dirY=1; } break; // DOWN
    case '4': if (dirX != 1) { dirX=-1; dirY=0; } break; // LEFT
    case '6': if (dirX != -1) { dirX=1; dirY=0; } break; // RIGHT
    case 'A': resetGame(); break;                        // restart
  }
}
void setup() {
  u8g2.begin();
  randomSeed(analogRead(0));
  resetGame();
}

void loop() {
  readKeypad();

  for (int i = length - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move head
  snakeX[0] += dirX;
  snakeY[0] += dirY;

  // Wall collision
  if (snakeX[0] >= gridW || snakeY[0] >= gridH || snakeX[0] < 0 || snakeY[0] < 0) {
    if (score > highScore) highScore = score;
    drawGameOver();
  }

  // Self collision
  for (byte i = 1; i < length; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      if (score > highScore) highScore = score;
      drawGameOver();
    }
  }

  // Eating food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (length < 119) length++;
    score++;
    spawnFood();
  }

  // Draw game
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x12_tr);
    char buf[20];
    sprintf(buf, "Score:%u", score);
    u8g2.drawStr(0, 10, buf);
    sprintf(buf, "Best:%u", highScore);
    u8g2.drawStr(70, 10, buf);

    // Food
    u8g2.drawBox(foodX * cell, foodY * cell, cell, cell);

    // Snake
    for (byte i = 0; i < length; i++) {
      u8g2.drawBox(snakeX[i] * cell, snakeY[i] * cell, cell, cell);
    }

  } while(u8g2.nextPage());

  delay(120);
}
