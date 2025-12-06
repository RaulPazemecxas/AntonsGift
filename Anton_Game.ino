// -------------------------------------------------------------
// ------------------ LIBS & LCD ------------------------
// -------------------------------------------------------------
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); 

// SECRET MSGS FOR ANTON HEHE
const char txt_raul[] PROGMEM = "Hello, Anton. I want to thank you for trusting my work, you changed my life. Without a doubt, the effort being put into Oryx will be rewarded. Visit this address to learn the story of how your gift was made: htttps://antonragin.com.br Big hug.";
const char txt_veronica[] PROGMEM = "Thank you for believing in my team and in me, and for not turning us into a McDonald's.";
const char txt_arthur[] PROGMEM = "Welcome back to Brazil, Anton! It's great to have you here again. Let's make the most of this time together and kick off 2026 with energy.";
const char txt_mateus[] PROGMEM = "Hey Anton, thank you for the opportunity, I'm very happy to be part of the Oryx team, I hope we can grow a lot in the coming years. Keep going";
const char txt_leo[]    PROGMEM = "Everyone at Oryx is doing their best and sometimes the impossible for the project. Success is just a matter of time.";
const char txt_aline[]  PROGMEM = "We want you to know that all of us are giving our very best — and often even the impossible — to help Oryx take off and reach the full potential we know it has. Our team is united, committed, and determined to overcome any challenge to turn this vision into reality.";
const char txt_cassia[] PROGMEM = "Anton, thank you for giving us the pleasure of working at ORYX! You can always count on me!";
const char txt_luana[]  PROGMEM = "I am grateful for the opportunity to be part of this, and even though I joined recently, I strongly believe in the success of this project.";
const char txt_gabriel[] PROGMEM = "Oryx has been a valuable learning experience. I believe that both I and the company can grow a lot together!";
const char txt_andre[] PROGMEM = "The effort has been continuous in all areas, and the expectation of experiencing the results of this intense work only grows";

struct MensagemTeam {
  const char* nome;       
  const char* texto_ptr; 
};

MensagemTeam mensagens[] = {
  {"Raul Pazemecxas:", txt_raul},
  {"Veronica:", txt_veronica},
  {"Arthur:",   txt_arthur},
  {"Mateus:",   txt_mateus},
  {"Leo:",      txt_leo},
  {"Aline:",    txt_aline},
  {"Cassia:",   txt_cassia},
  {"Luana:",    txt_luana},
  {"Gabriel:",  txt_gabriel},
  {"Andre:",    txt_andre}
};

int quantidadeMensagens = sizeof(mensagens) / sizeof(mensagens[0]);

// -------------------------------------------------------------
// --------------------- NOTES MUSIC ---------------------
// -------------------------------------------------------------
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#define REST 0  

#define CHOICE_OFF      0
#define CHOICE_NONE     0
#define CHOICE_RED      (1 << 0)
#define CHOICE_GREEN    (1 << 1)
#define CHOICE_BLUE     (1 << 2)
#define CHOICE_YELLOW   (1 << 3)

#define LED_RED     10
#define LED_GREEN   3
#define LED_BLUE    13
#define LED_YELLOW  5

// BUTTONS -> During the development process, some LEDs burned out. So, I got kind of fed up. Ignore if the variable name points to the wrong LED on the Arduino pin.
//Follow the circuit schematic you created; you can change the LED colors if you want xD

#define BUTTON_RED    9   
#define BUTTON_GREEN  2
#define BUTTON_BLUE   12
#define BUTTON_YELLOW 6

// BUZZER
#define BUZZER1 4
#define BUZZER2 7

// GAME
#define ROUNDS_TO_WIN 13
#define ENTRY_TIME_LIMIT 3000

#define MODE_MEMORY 0
#define MODE_BATTLE 1
#define MODE_BEEGEES 2

byte gameMode = MODE_MEMORY;
byte gameBoard[32];
byte gameRound = 0;
byte startButton = CHOICE_NONE; 

// Protótipos de funções
void play_secret_message();
void rolarMensagemPROGMEM(const char* nome, const char* textoFlash);
void play_starwars();
void play_mario();
void play_beegees();
void changeLED();
void play_winner();
void winner_sound();
void play_loser();
void buzz_sound(int buzz_length_ms, int buzz_delay_us);
void toner(byte which, int buzz_length_ms);
byte checkButton(void);
byte wait_for_button(void);
void setLEDs(byte leds);
void add_to_moves(void);
void playMoves(void);
boolean play_battle(void);
boolean play_memory(void);
void attractMode(void);

// -------------------------------------------------------------
// -------------------------- SETUP -----------------------------
// -------------------------------------------------------------
void setup()
{
  lcd.init();
  lcd.clear(); 
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);

  gameMode = MODE_MEMORY;

  // Easter egg Bee Gees (botão amarelo segurado na energização)
  if (checkButton() == CHOICE_YELLOW) play_beegees();

  // Modo batalha (botão verde segurado na energização)
  if (checkButton() == CHOICE_GREEN)
  {
    gameMode = MODE_BATTLE;

    setLEDs(CHOICE_GREEN);
    toner(CHOICE_GREEN, 150);

    setLEDs(CHOICE_RED | CHOICE_BLUE | CHOICE_YELLOW);
    while (checkButton() != CHOICE_NONE) ;
  }

  play_winner();
}

// -------------------------------------------------------------
// --------------------------- LOOP -----------------------------
// -------------------------------------------------------------
void loop()
{
  attractMode(); 

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE | CHOICE_YELLOW);
  delay(1000);
  setLEDs(CHOICE_OFF);
  delay(250);

  if (gameMode == MODE_MEMORY)
  {
    if (play_memory() == true)
    {
      play_winner();
    }
    else
    {
      if (startButton == CHOICE_BLUE) 
        play_starwars();
      else 
        play_loser();
    }
  }

  if (gameMode == MODE_BATTLE)
  {
    play_battle();
    play_loser();
  }
}

// -------------------------------------------------------------
// --------------------- FUNCTIONS IN GAME -----------------------
// -------------------------------------------------------------
boolean play_memory(void)
{
  randomSeed(millis());
  gameRound = 0;

  while (gameRound < ROUNDS_TO_WIN)
  {
    add_to_moves();
    playMoves();

    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      byte choice = wait_for_button();

      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) return false;
    }

    delay(1000);
  }
  return true;
}

boolean play_battle(void)
{
  gameRound = 0;
  while (1)
  {
    byte newButton = wait_for_button();
    gameBoard[gameRound++] = newButton;

    for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
    {
      byte choice = wait_for_button();

      if (choice == 0) return false;
      if (choice != gameBoard[currentMove]) return false;
    }
    delay(100);
  }
  return true;
}

void playMoves(void)
{
  for (byte currentMove = 0 ; currentMove < gameRound ; currentMove++)
  {
    toner(gameBoard[currentMove], 150);
    delay(150);
  }
}

void add_to_moves(void)
{
  byte newButton = random(0, 4);
  if (newButton == 0) newButton = CHOICE_RED;
  else if (newButton == 1) newButton = CHOICE_GREEN;
  else if (newButton == 2) newButton = CHOICE_BLUE;
  else if (newButton == 3) newButton = CHOICE_YELLOW;
  gameBoard[gameRound++] = newButton;
}

void setLEDs(byte leds)
{
  digitalWrite(LED_RED, (leds & CHOICE_RED) ? HIGH : LOW);
  digitalWrite(LED_GREEN, (leds & CHOICE_GREEN) ? HIGH : LOW);
  digitalWrite(LED_BLUE, (leds & CHOICE_BLUE) ? HIGH : LOW);
  digitalWrite(LED_YELLOW, (leds & CHOICE_YELLOW) ? HIGH : LOW);
}

byte wait_for_button(void)
{
  long startTime = millis();
  while ( (millis() - startTime) < ENTRY_TIME_LIMIT)
  {
    byte button = checkButton();
    if (button != CHOICE_NONE)
    {
      toner(button, 150);
      while (checkButton() != CHOICE_NONE) ;
      delay(10);
      return button;
    }
  }
  return CHOICE_NONE;
}

byte checkButton(void)
{
  if (digitalRead(BUTTON_RED) == 0) return (CHOICE_RED);
  else if (digitalRead(BUTTON_GREEN) == 0) return (CHOICE_GREEN);
  else if (digitalRead(BUTTON_BLUE) == 0) return (CHOICE_BLUE);
  else if (digitalRead(BUTTON_YELLOW) == 0) return (CHOICE_YELLOW);
  return (CHOICE_NONE);
}

void toner(byte which, int buzz_length_ms)
{
  setLEDs(which);
  switch (which)
  {
    case CHOICE_RED:    buzz_sound(buzz_length_ms, 1136); break;
    case CHOICE_GREEN:  buzz_sound(buzz_length_ms, 568); break;
    case CHOICE_BLUE:   buzz_sound(buzz_length_ms, 851); break;
    case CHOICE_YELLOW: buzz_sound(buzz_length_ms, 638); break;
  }
  setLEDs(CHOICE_OFF);
}

void buzz_sound(int buzz_length_ms, int buzz_delay_us)
{
  long buzz_length_us = buzz_length_ms * (long)1000;
  while (buzz_length_us > (buzz_delay_us * 2))
  {
    buzz_length_us -= buzz_delay_us * 2;
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(buzz_delay_us);
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    delayMicroseconds(buzz_delay_us);
  }
}

void play_winner(void)
{
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
  setLEDs(CHOICE_GREEN | CHOICE_BLUE);
  winner_sound();
  setLEDs(CHOICE_RED | CHOICE_YELLOW);
  winner_sound();
}

void winner_sound(void)
{
  for (byte x = 250 ; x > 70 ; x--)
  {
    for (byte y = 0 ; y < 3 ; y++)
    {
      digitalWrite(BUZZER2, HIGH);
      digitalWrite(BUZZER1, LOW);
      delayMicroseconds(x);
      digitalWrite(BUZZER2, LOW);
      digitalWrite(BUZZER1, HIGH);
      delayMicroseconds(x);
    }
  }
}

void play_loser(void)
{
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_RED | CHOICE_GREEN);
  buzz_sound(255, 1500);
  setLEDs(CHOICE_BLUE | CHOICE_YELLOW);
  buzz_sound(255, 1500);
}

void attractMode(void)
{
  static int redPressCount = 0;
  static int bluePressCount = 0;
  static unsigned long lastPressTime = 0;
  const unsigned long pressTimeout = 1500; 

  while (1)
  {
    setLEDs(CHOICE_RED);
    delay(100);

    byte b = checkButton();
    
    // Resetar contadores se demorar muito
    if (millis() - lastPressTime > pressTimeout && lastPressTime != 0) {
       redPressCount = 0;
       bluePressCount = 0;
       lastPressTime = 0; 
    }

    // ---------------- MARIO ----------------
    if (b == CHOICE_RED) {
      while (checkButton() == CHOICE_RED) ; // debounce
      delay(50); 

      unsigned long now = millis();
      redPressCount++;
      lastPressTime = now;
      bluePressCount = 0; // Zera o azul
      
      toner(CHOICE_RED, 50); 

      if (redPressCount >= 4) {
        redPressCount = 0;
        play_mario();   
      }
      continue; 
    }
    
    // ---------------- STARWARS AND MSG RAUL ----------------
    else if (b == CHOICE_BLUE) {
       while (checkButton() == CHOICE_BLUE) ; // debounce
       delay(50);
       
       if (redPressCount > 0) {
          redPressCount = 0; 
          bluePressCount = 0;
          
          setLEDs(CHOICE_BLUE);
          buzz_sound(50, 851);
          setLEDs(CHOICE_OFF);

          play_secret_message(); 
          continue;
       }

       bluePressCount++;
       lastPressTime = millis();
       toner(CHOICE_BLUE, 50);

       if (bluePressCount >= 4) {
          bluePressCount = 0;
          play_starwars();
       }
       continue; 
    }

    // ---------------- OUTROS BOTÕES (INICIAM O JOGO) ----------------
    else if (b != CHOICE_NONE) {
      startButton = b; 
      redPressCount = 0; 
      bluePressCount = 0;
      return; 
    }

    setLEDs(CHOICE_BLUE);
    delay(100);
    if (checkButton() != CHOICE_NONE) continue; 

    setLEDs(CHOICE_GREEN);
    delay(100);
    if (checkButton() != CHOICE_NONE) continue;

    setLEDs(CHOICE_YELLOW);
    delay(100);
    if (checkButton() != CHOICE_NONE) continue;
  }
}

// -------------------------------------------------------------
// ------------- SECRET MSG FOR ANTON xD ---------------
// -------------------------------------------------------------
void play_secret_message() {
  
  setLEDs(CHOICE_OFF);
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
  
  lcd.init();      
  lcd.backlight(); 
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Welcome Anton!");
  lcd.setCursor(0, 1);
  lcd.print("Loading msgs...");
  
  delay(2000); 

  while(1) {
    for (int i = 0; i < quantidadeMensagens; i++) {
      lcd.backlight(); 
      rolarMensagemPROGMEM(mensagens[i].nome, mensagens[i].texto_ptr);
      delay(1000); 
    }
  }
}

void rolarMensagemPROGMEM(const char* nome, const char* textoFlash) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(nome);

  int tamanhoFrase = strlen_P(textoFlash);
  int totalCaracteres = tamanhoFrase + 16;

  for (int posicao = 0; posicao < totalCaracteres; posicao++) {
    
    lcd.setCursor(0, 1);
    
    for (int j = 0; j < 16; j++) {
      int indiceAtual = posicao + j;
      
      if (indiceAtual < tamanhoFrase) {
        char c = pgm_read_byte(textoFlash + indiceAtual);
        lcd.write(c);
      } else {
        lcd.print(" "); 
      }
    }

    if (posicao == 0) {
      delay(2000); 
    } else {
      delay(250);  
    }
  }
}

// -------------------------------------------------------------
// -------------------- EASTER EGG: STAR WARS -------------------
// -------------------------------------------------------------
void play_starwars()
{
  // --- CORREÇÃO:  BUZZER1  GND para o tone funcionar no BUZZER2 ---
  noTone(BUZZER2);
  digitalWrite(BUZZER1, LOW); 
  digitalWrite(BUZZER2, LOW);
  // -----------------------------------------------------------------------------------

  const int melody[] = {
    NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4,
    NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5, NOTE_GS4, NOTE_F4, NOTE_C5, NOTE_A4,
    NOTE_A5, NOTE_A4, NOTE_A4, NOTE_A5, NOTE_GS5, NOTE_G5, NOTE_FS5, NOTE_F5, NOTE_FS5,
    REST, NOTE_AS4, NOTE_DS5, NOTE_D5, NOTE_CS5, NOTE_C5, NOTE_B4, NOTE_C5,
    REST, NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_E5
  };

  const int tempo[] = {
    500, 500, 500, 350, 150, 500, 350, 150, 650,
    500, 500, 500, 350, 150, 500, 350, 150, 650,
    500, 300, 150, 500, 325, 175, 125, 125, 250,
    325, 250, 500, 325, 175, 125, 125, 250,
    350, 250, 500, 350, 125, 500, 375, 125, 650
  };

  int total = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < total; i++)
  {
    int note = melody[i];
    int duration = tempo[i];

    // Lógica dos LEDs (Mantida igual)
    if (note != REST) {
        if (i % 4 == 0) setLEDs(CHOICE_RED);
        else if (i % 4 == 1) setLEDs(CHOICE_YELLOW);
        else if (i % 4 == 2) setLEDs(CHOICE_BLUE);
        else setLEDs(CHOICE_GREEN);
    } else {
        setLEDs(CHOICE_OFF);
    }

    // Lógica do som
    if (note == REST) {
      noTone(BUZZER2);
    } else {
      tone(BUZZER2, note, duration);
    }

    delay((int)(duration * 1.30)); 
    noTone(BUZZER2); 
  }

  setLEDs(CHOICE_OFF);
  noTone(BUZZER2);
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
}
// -------------------------------------------------------------
// -------------------- EASTER EGG: BEE GEES --------------------
// -------------------------------------------------------------
int melodyBeeGees[] = {
  NOTE_G4, NOTE_A4, 0, NOTE_C5, 0, 0, NOTE_G4, 0, 0, 0,
  NOTE_E4, 0, NOTE_D4, NOTE_E4, NOTE_G4, 0,
  NOTE_D4, NOTE_E4, 0, NOTE_G4, 0, 0,
  NOTE_D4, 0, NOTE_E4, 0, NOTE_G4, 0, NOTE_A4, 0, NOTE_C5, 0
};

int noteDuration = 115;
int LEDnumber = 0;

void play_beegees()
{
  setLEDs(CHOICE_YELLOW);
  toner(CHOICE_YELLOW, 150);

  setLEDs(CHOICE_RED | CHOICE_GREEN | CHOICE_BLUE);
  while (checkButton() != CHOICE_NONE) ;

  setLEDs(CHOICE_NONE);
  delay(1000);

  digitalWrite(BUZZER1, LOW);

  while (checkButton() == CHOICE_NONE)
  {
    for (int thisNote = 0; thisNote < 32; thisNote++) {
      changeLED();
      tone(BUZZER2, melodyBeeGees[thisNote], noteDuration);
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      noTone(BUZZER2);
    }
  }
}

void changeLED(void)
{
  setLEDs(1 << LEDnumber);
  LEDnumber++;
  if (LEDnumber > 3) LEDnumber = 0;
}

// -------------------------------------------------------------
// -------------------- EASTER EGG: MARIO -----------------------
// -------------------------------------------------------------
const int MARIO_TEMPO = 200;

const int marioScore[] = {
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8,
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4,
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4,
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
  REST,1,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4,
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
  REST,1,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2
};

void play_mario()
{
  noTone(BUZZER2);
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
  setLEDs(CHOICE_OFF);
  delay(150);

  long wholenote = (long)60000 * 4 / MARIO_TEMPO;
  int notes = sizeof(marioScore) / sizeof(marioScore[0]) / 2;

  byte ledSeq[4] = { CHOICE_RED, CHOICE_GREEN, CHOICE_BLUE, CHOICE_YELLOW };
  byte ledIndex = 0;

  for (int thisNote = 0; thisNote < notes * 2; thisNote += 2)
  {
    int note    = marioScore[thisNote];
    int divider = marioScore[thisNote + 1];
    long noteDuration = 0;

    if (divider > 0) {
      noteDuration = wholenote / divider;
    } else {
      noteDuration = wholenote / (-divider);
      noteDuration = noteDuration + noteDuration / 2; 
    }

    if (note == REST) {
      setLEDs(CHOICE_OFF);
      noTone(BUZZER2);
      delay(noteDuration);
    } else {
      setLEDs(ledSeq[ledIndex]);
      ledIndex = (ledIndex + 1) % 4;
      tone(BUZZER2, note, (int)(noteDuration * 0.9));
      delay(noteDuration);
      noTone(BUZZER2);
    }
  }

  noTone(BUZZER2);
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
  setLEDs(CHOICE_OFF);
  delay(150);
}
