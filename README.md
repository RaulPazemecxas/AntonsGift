# 🎁 The Anton Gift: A Saga of Code & Solder

> *"Hello, Anton. Have a good journey."*

## 📖 The Story

This repository contains the source code and digital assets for the **Secret Santa** gift presented to **Anton Ragin**, Oryx Capital's visionary investor.

The gift is a dual-experience designed to test memory and celebrate the team:

1.  **The Hardware:** A physical, Arduino-based memory game (inspired by *Simon Says* / *Genius*) built from scratch.
2.  **The Software:** A specialized C++ firmware packed with Easter Eggs and a companion website that tells the "comic book" story of how this device was forged.

---

## 🕹️ The Hardware (Arduino Game)

The core of the gift is a reaction and memory game. The player must repeat the sequence of flashing LEDs. However, this isn't just a toy; it's a communication device.

### Features
* **🧠 Memory Challenge:** Randomly generated sequences that get progressively harder.
* **📟 LCD Display:** Provides real-time feedback, scores, and scrolling hidden messages.
* **🔊 Audio Feedback:** Piezo buzzer integration for game sounds and musical themes.

---

## 🥚 Secret Features (Easter Eggs)

By inputting specific **"Cheat Codes"** (button combinations) on the device, the firmware unlocks hidden functions:

* **The Team's Voice:** Displays scrolling messages from the entire Oryx Capital team.
* **The Plumber's Anthem:** Plays the iconic *Super Mario Bros* theme.
* **The Dark Side:** Plays the *Imperial March* from Star Wars.

---

## 💻 Under the Hood: The C++ Firmware

The logic resides in `Anton_Game.ino`. The code was meticulously optimized for the AVR architecture to handle extensive string manipulation without exhausting the microcontroller's RAM.

### Key Technical Highlight: PROGMEM Optimization

To store the heartfelt messages from the team without crashing the Arduino's limited dynamic memory (SRAM), we utilized the `<avr/pgmspace.h>` library. Instead of standard string handling, messages are burned directly into the **Flash Memory (Program Space)** using the `PROGMEM` modifier:

```cpp

// Example from the source code
const char txt_arthur[] PROGMEM = "Welcome back to Brazil, Anton! ...";

struct MensagemTeam {
  const char* nome;      
  const char* texto_ptr; // Pointer to Flash memory
};

```

# Custom Memory Scrolling

Because the data lives in Flash, we cannot print it using standard Serial.print or lcd.print. We implemented a custom buffer reader that fetches data byte-by-byte directly from the chip's storage:


// The magic happens here: pgm_read_byte reads directly from Flash

char c = pgm_read_byte(textoFlash + indiceAtual);
lcd.write(c);
This architecture allows for smooth scrolling of long text strings on the 16x2 LCD display while keeping the game logic fast and responsive.

# 🎨 The Companion Website
Located in the AntonSecret/ folder, this web project serves as the manual and "Making Of" documentary, presented in a Retro Comic Book style.

# Web Tech Stack
-> HTML5 & Tailwind CSS: For the responsive, comic-panel layout.

-> Vanilla JS (comic.js): Handles the page turning logic, language toggling (EN/PT), and audio atmosphere (Zelda theme).

-> Custom CSS (comic.css): Implements halftone patterns, skewed borders, and "speech bubble" aesthetics.
