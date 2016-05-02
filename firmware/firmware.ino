int rows[6] = {0, 1, 2, 3, 5, 4};
int columns[17] = { 
  23, 22, 21, 20, 19,
  18, 17, 16, 15, 14,
  12, 11, 10, 9, 8,
  7, 6
};
struct keylist {
  struct keylist *next;
  struct keylist *prev;
  unsigned long keyCode;
  int column;
  int row;
};


struct keylist *first = NULL;
struct keylist *last = NULL;
                  
unsigned long normalMap[17][6] = {
  { 
    //0
    KEY_ESC, KEY_TILDE, KEY_TAB, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_LEFT_CTRL 
  },
  { 
    //1
    0, KEY_1, KEY_Q, KEY_A, KEY_Z, KEY_LEFT_GUI
  },
  { 
    //2
    KEY_F1, KEY_2, KEY_W, KEY_S, KEY_X, KEY_LEFT_ALT
  },
  { 
    //3
    KEY_F2, KEY_3, KEY_E, KEY_D, KEY_C, 0
  },
  {
    //4
    KEY_F3, KEY_4, KEY_R, KEY_F, KEY_V, 0
  },
  {
    //5
    KEY_F4, KEY_5, KEY_T, KEY_G, KEY_B, KEY_SPACE
  },
  {
    //6
    0, KEY_6, KEY_Y, KEY_H, KEY_N, 0
  },
  {
    //7
    KEY_F5, KEY_7, KEY_U, KEY_J, KEY_M, 0
  },
  {
    //8
    KEY_F6, KEY_8, KEY_I, KEY_K, KEY_COMMA, 0
  },
  {
    //9
    KEY_F7, KEY_9, KEY_O, KEY_L, KEY_PERIOD, KEY_RIGHT_ALT
  },
  {
    //10
    KEY_F8, KEY_0, KEY_P, KEY_SEMICOLON, KEY_SLASH, KEY_RIGHT_GUI 
  },
  {
    //11
    KEY_F9, KEY_MINUS, KEY_LEFT_BRACE, KEY_QUOTE, 0, 0
  },
  {
    //12
    KEY_F10, KEY_EQUAL, KEY_RIGHT_BRACE, 0, 0, 0 
  },
  {
    //13
    KEY_F11, KEY_BACKSPACE, KEY_BACKSLASH, KEY_ENTER, KEY_RIGHT_SHIFT, KEY_RIGHT_CTRL
  },
  {
    //14
    KEY_F12, KEY_INSERT, KEY_DELETE, 0, 0, KEY_LEFT
  },
  {
    //15
    0, KEY_HOME, KEY_END, 0, KEY_UP, KEY_DOWN
  },
  {
    //16
    0, KEY_PAGE_UP, KEY_PAGE_DOWN, 0, 0, KEY_RIGHT
  }
};

unsigned long fnMap[17][6] = {
  { 
    //0
    0, 0, 0, KEY_CAPS_LOCK, 0, 0 
  },
  { 
    //1
    0, 0, 0, 0, 0, 0
  },
  { 
    //2
    0, 0, 0, 0, 0, 0
  },
  { 
    //3
    0, 0, 0, 0, 0, 0
  },
  {
    //4
    0, 0, 0, 0, 0, 0
  },
  {
    //5
    0, 0, 0, 0, 0, 0
  },
  {
    //6
    0, 0, 0, 0, 0, 0
  },
  {
    //7
    KEY_MEDIA_STOP, 0, 0, 0, 0, 0
  },
  {
    //8
    KEY_MEDIA_PREV_TRACK, 0, 0, 0, 0, 0
  },
  {
    //9
    KEY_MEDIA_PLAY_PAUSE, 0, 0, 0, 0, 0
  },
  {
    //10
    KEY_MEDIA_NEXT_TRACK, 0, 0, 0, 0, 0
  },
  {
    //11
    0, 0, 0, 0, 0, 0
  },
  {
    //12
    KEY_MEDIA_MUTE, 0, 0, 0, 0, 0
  },
  {
    //13
    KEY_MEDIA_VOLUME_DEC, 0, 0, 0, 0, 0
  },
  {
    //14
    KEY_MEDIA_VOLUME_INC, KEY_PRINTSCREEN, 0, 0, 0, 0
  },
  {
    //15
    0, KEY_SCROLL_LOCK, 0, 0, 0, 0
  },
  {
    //16
    0, KEY_PAUSE, 0, 0, 0, 0
  }
};

void setup() {
  // put your setup code here, to run once:

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  
  for(int i = 0; i < 6; i++) {
    pinMode(rows[i], INPUT);
  }
  for(int i = 0; i < 17; i++) {
    pinMode(columns[i], OUTPUT);
  }
  Serial.begin(9600);
  
}

             
bool activeMap[17][6];
int fnStatus;


void loop() {
  // put your main code here, to run repeatedly:
 
  scanKeys();
  if(activeMap[12][5] != fnStatus) {
    clearKeys();
    fnStatus = activeMap[12][5];
  }
  if(fnStatus) {
    setFnKeys();
  } else {
    setNormalKeys(); 
  }
  reportKeys();
  delay(16);
}
void scanKeys() {
  for(int i = 0; i < 17; i++) {
    digitalWrite(columns[i], HIGH);
    for(int j = 0; j < 6; j++) {
      activeMap[i][j] = digitalRead(rows[j]) == HIGH;
    }
    digitalWrite(columns[i], LOW);
  }
}

void reportKeys() {
  int count = 0;
  struct keylist * current = last;

  if(current != NULL) {
    count++;
    while(current->prev != NULL && count < 6) {
      current = current->prev;
      count++;
    }
  }
  
  if(count > 0) {
    Keyboard.set_key1(current->keyCode);
    current = current ->next;
  } else {
    Keyboard.set_key1(0);
  }
  if(count > 1) {
    Keyboard.set_key2(current->keyCode);
    current = current ->next;
  } else {
    Keyboard.set_key2(0);
  }
  if(count > 2) {
    Keyboard.set_key3(current->keyCode);
    current = current ->next;
  } else {
    Keyboard.set_key3(0);
  }
  if(count > 3) {
    Keyboard.set_key4(current->keyCode);
    current = current ->next;
  } else {
    Keyboard.set_key4(0);
  }
  if(count > 4) {
    Keyboard.set_key5(current->keyCode);
    current = current ->next;
  } else {
    Keyboard.set_key5(0);
  }
  if(count > 5) {
    Keyboard.set_key6(current->keyCode);
    current = current ->next;
  } else {
    Keyboard.set_key6(0);
  }
  
  Keyboard.send_now();;
}

void setNormalKeys() {
  Keyboard.set_media(0);
  unsigned long modifiers = 0;

  //clear unclicked keys from stack;
  struct keylist * current = first;
  bool existed = false;
  while(current != NULL) {
    if(!activeMap[current->column][current->row]) {
      current = deleteEntry(current);
    } else {
      current = current ->next;
    }
  }
  
  for(int i = 0; i < 17; i++) {
    for(int j = 0; j < 6; j++) {
      if(activeMap[i][j] && normalMap[i][j]) {
        if(normalMap[i][j] > 0xF000) {
          //check if key is already in the list
          current = first;
          existed = false;
          while(current != NULL) {
            if(current->column == i && current->row == j) {
              existed = true;
            }
            current = current->next;
          }
          if(!existed) {
            createEntry(i, j, normalMap[i][j]);
          }
        } else if(normalMap[i][j] > 0xE400) {
          
        } else {
           //modifier keys
          modifiers = modifiers | normalMap[i][j];
        }
      }
    }
  }
  Keyboard.set_modifier(modifiers);
}

void setFnKeys() {
  
  Keyboard.set_modifier(0);
  //clear unclicked keys from stack;

  unsigned long mediaKey = 0;

  
  struct keylist * current = first;
  bool existed = false;
  while(current != NULL) {
    if(!activeMap[current->column][current->row]) {
      current = deleteEntry(current);
    } else {
      current = current ->next;
    }
  }
  
  for(int i = 0; i < 17; i++) {
    for(int j = 0; j < 6; j++) {
      if(activeMap[i][j] && fnMap[i][j]) {
        if(fnMap[i][j] > 0xF000) {
          //check if key is already in the list
          current = first;
          existed = false;
          while(current != NULL) {
            if(current->column == i && current->row == j) {
              existed = true;
            }
            current = current->next;
          }
          if(!existed) {
            createEntry(i, j, fnMap[i][j]);
          }
        } else if(fnMap[i][j] > 0xE400) {
          //media keys
          mediaKey = fnMap[i][j];
        } else {
          //modifier keys
        }
      }
    }
  }

  Keyboard.set_media(mediaKey);
}

struct keylist *createEntry(int column, int row, unsigned long keyCode) {
  struct keylist *entry = (struct keylist *)malloc(sizeof(struct keylist));
  entry->column = column;
  entry->row = row;
  entry->keyCode = keyCode;
  entry->next = NULL;
  if(last == NULL) {
    last = entry;
    first = entry;
    entry->prev = NULL;
  } else {
    last->next = entry;
    entry->prev = last;
    last = entry;
  }
  return entry;
}

struct keylist *deleteEntry(struct keylist* entry) {
  struct keylist *next = entry->next;
  struct keylist *prev = entry->prev;
  if(prev != NULL) {
    prev->next = next;
  }
  if(next != NULL) {
    next->prev = prev;
  }
  if(first == entry) {
    first = entry->next;
  }
  if(last == entry) {
    last = entry->prev;
  }
  free(entry);
  return next;
}

void clearKeys() {
  struct keylist *current = first;
  struct keylist *next = NULL;
  while(current != NULL) {
    next = current->next;
    free(current);
    current = next;    
  }
  first = NULL;
  last = NULL;
}

