typedef struct {
  // Pins connected to 7-seg pin 1, 2, 4, 5, 6, 7, 9, 10 (3 and 8 are grounded).
  uint8_t pins[8];
} num;
// States of each LED, packed into a byte.
typedef uint8_t num_glyph;

void num_init(const num* n) {
  for (uint8_t i=0; i<8; i++) pinMode(n->pins[i], OUTPUT);
};

void num_show(const num* n, num_glyph g) {
  for (uint8_t i=0; i<8; i++) {
    digitalWrite(n->pins[i], (g&(1<<i)) ? HIGH : LOW);
  }
}

// Hex digits 0-f.
static num_glyph hex[] = {
  0x77, 0x14, 0xb3, 0xb6, 0xd4, 0xe6, 0xe7, 0x34,
  0xf7, 0xf4, 0xf5, 0xc7, 0x63, 0x97, 0xe3, 0xe1,
};
// OR with a digit to set the dot.
static num_glyph dot = 0x08;

static const num num0={6,7,8,9,5,4,3,2};
void setup(){
  num_init(&num0);
}
void loop(){
  for (uint8_t i = 0; i < 16; i++) {
    for (uint8_t j = 0; j < 2; j++) {
      num_show(&num0, hex[i] | dot);
      delay(250);
      num_show(&num0, hex[i]);
      delay(250);
    }
  }
}
