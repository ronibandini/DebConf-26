#include <Arduino_LED_Matrix.h>
#include <Arduino_RouterBridge.h>

Arduino_LED_Matrix matrix;

uint8_t frame[104] = {0};

constexpr int MATRIX_WIDTH = 13;
constexpr int MATRIX_HEIGHT = 8;
constexpr int SCROLL_DELAY_MS = 80;


/*
 * Returns one vertical column of a 5x7 character.
 * Bit 0 is the top pixel; bit 6 is the bottom pixel.
 */
uint8_t glyphColumn(char character, uint8_t column) {
  character = toupper(character);

  if (column >= 5) {
    return 0;
  }

  switch (character) {
    case 'A': {
      const uint8_t glyph[5] = {0x7E, 0x09, 0x09, 0x09, 0x7E};
      return glyph[column];
    }
    case 'B': {
      const uint8_t glyph[5] = {0x7F, 0x49, 0x49, 0x49, 0x36};
      return glyph[column];
    }
    case 'C': {
      const uint8_t glyph[5] = {0x3E, 0x41, 0x41, 0x41, 0x22};
      return glyph[column];
    }
    case 'D': {
      const uint8_t glyph[5] = {0x7F, 0x41, 0x41, 0x22, 0x1C};
      return glyph[column];
    }
    case 'E': {
      const uint8_t glyph[5] = {0x7F, 0x49, 0x49, 0x49, 0x41};
      return glyph[column];
    }
    case 'F': {
      const uint8_t glyph[5] = {0x7F, 0x09, 0x09, 0x09, 0x01};
      return glyph[column];
    }
    case 'G': {
      const uint8_t glyph[5] = {0x3E, 0x41, 0x49, 0x49, 0x7A};
      return glyph[column];
    }
    case 'H': {
      const uint8_t glyph[5] = {0x7F, 0x08, 0x08, 0x08, 0x7F};
      return glyph[column];
    }
    case 'I': {
      const uint8_t glyph[5] = {0x41, 0x41, 0x7F, 0x41, 0x41};
      return glyph[column];
    }
    case 'J': {
      const uint8_t glyph[5] = {0x20, 0x40, 0x41, 0x3F, 0x01};
      return glyph[column];
    }
    case 'K': {
      const uint8_t glyph[5] = {0x7F, 0x08, 0x14, 0x22, 0x41};
      return glyph[column];
    }
    case 'L': {
      const uint8_t glyph[5] = {0x7F, 0x40, 0x40, 0x40, 0x40};
      return glyph[column];
    }
    case 'M': {
      const uint8_t glyph[5] = {0x7F, 0x02, 0x0C, 0x02, 0x7F};
      return glyph[column];
    }
    case 'N': {
      const uint8_t glyph[5] = {0x7F, 0x04, 0x08, 0x10, 0x7F};
      return glyph[column];
    }
    case 'O': {
      const uint8_t glyph[5] = {0x3E, 0x41, 0x41, 0x41, 0x3E};
      return glyph[column];
    }
    case 'P': {
      const uint8_t glyph[5] = {0x7F, 0x09, 0x09, 0x09, 0x06};
      return glyph[column];
    }
    case 'Q': {
      const uint8_t glyph[5] = {0x3E, 0x41, 0x51, 0x21, 0x5E};
      return glyph[column];
    }
    case 'R': {
      const uint8_t glyph[5] = {0x7F, 0x09, 0x19, 0x29, 0x46};
      return glyph[column];
    }
    case 'S': {
      const uint8_t glyph[5] = {0x46, 0x49, 0x49, 0x49, 0x31};
      return glyph[column];
    }
    case 'T': {
      const uint8_t glyph[5] = {0x01, 0x01, 0x7F, 0x01, 0x01};
      return glyph[column];
    }
    case 'U': {
      const uint8_t glyph[5] = {0x3F, 0x40, 0x40, 0x40, 0x3F};
      return glyph[column];
    }
    case 'V': {
      const uint8_t glyph[5] = {0x1F, 0x20, 0x40, 0x20, 0x1F};
      return glyph[column];
    }
    case 'W': {
      const uint8_t glyph[5] = {0x7F, 0x20, 0x18, 0x20, 0x7F};
      return glyph[column];
    }
    case 'X': {
      const uint8_t glyph[5] = {0x63, 0x14, 0x08, 0x14, 0x63};
      return glyph[column];
    }
    case 'Y': {
      const uint8_t glyph[5] = {0x03, 0x04, 0x78, 0x04, 0x03};
      return glyph[column];
    }
    case 'Z': {
      const uint8_t glyph[5] = {0x61, 0x51, 0x49, 0x45, 0x43};
      return glyph[column];
    }

    case '0': {
      const uint8_t glyph[5] = {0x3E, 0x51, 0x49, 0x45, 0x3E};
      return glyph[column];
    }
    case '1': {
      const uint8_t glyph[5] = {0x00, 0x42, 0x7F, 0x40, 0x00};
      return glyph[column];
    }
    case '2': {
      const uint8_t glyph[5] = {0x62, 0x51, 0x49, 0x49, 0x46};
      return glyph[column];
    }
    case '3': {
      const uint8_t glyph[5] = {0x22, 0x41, 0x49, 0x49, 0x36};
      return glyph[column];
    }
    case '4': {
      const uint8_t glyph[5] = {0x18, 0x14, 0x12, 0x7F, 0x10};
      return glyph[column];
    }
    case '5': {
      const uint8_t glyph[5] = {0x27, 0x45, 0x45, 0x45, 0x39};
      return glyph[column];
    }
    case '6': {
      const uint8_t glyph[5] = {0x3C, 0x4A, 0x49, 0x49, 0x30};
      return glyph[column];
    }
    case '7': {
      const uint8_t glyph[5] = {0x01, 0x71, 0x09, 0x05, 0x03};
      return glyph[column];
    }
    case '8': {
      const uint8_t glyph[5] = {0x36, 0x49, 0x49, 0x49, 0x36};
      return glyph[column];
    }
    case '9': {
      const uint8_t glyph[5] = {0x06, 0x49, 0x49, 0x29, 0x1E};
      return glyph[column];
    }

    case '-': {
      const uint8_t glyph[5] = {0x08, 0x08, 0x08, 0x08, 0x08};
      return glyph[column];
    }
    case '.': {
      const uint8_t glyph[5] = {0x00, 0x60, 0x60, 0x00, 0x00};
      return glyph[column];
    }
    case '!': {
      const uint8_t glyph[5] = {0x00, 0x00, 0x5F, 0x00, 0x00};
      return glyph[column];
    }
    case ':': {
      const uint8_t glyph[5] = {0x00, 0x36, 0x36, 0x00, 0x00};
      return glyph[column];
    }
    case ' ':
    default:
      return 0;
  }
}


void clearFrame() {
  memset(frame, 0, sizeof(frame));
}


void shiftLeft(uint8_t newColumn) {
  for (int row = 0; row < MATRIX_HEIGHT; row++) {
    for (int column = 0; column < MATRIX_WIDTH - 1; column++) {
      frame[row * MATRIX_WIDTH + column] =
          frame[row * MATRIX_WIDTH + column + 1];
    }

    frame[row * MATRIX_WIDTH + MATRIX_WIDTH - 1] =
        (newColumn >> row) & 0x01;
  }

  matrix.draw(frame);
  delay(SCROLL_DELAY_MS);
}


void displayText(String message) {
  clearFrame();
  matrix.draw(frame);

  // Blank columns before the text enters.
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    shiftLeft(0);
  }

  for (unsigned int characterIndex = 0;
       characterIndex < message.length();
       characterIndex++) {

    char character = message.charAt(characterIndex);

    for (uint8_t glyphColumnIndex = 0;
         glyphColumnIndex < 5;
         glyphColumnIndex++) {

      shiftLeft(glyphColumn(character, glyphColumnIndex));
    }

    // One blank column between characters.
    shiftLeft(0);
  }

  // Let the final text leave the display.
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    shiftLeft(0);
  }
}


void setup() {
  matrix.begin();
  matrix.setGrayscaleBits(1);
  clearFrame();
  matrix.draw(frame);

  Bridge.begin();

  // Matrix operations run safely in Arduino's main loop.
  Bridge.provide_safe("displayText", displayText);
}


void loop() {
}