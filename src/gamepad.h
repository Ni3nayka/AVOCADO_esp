/*
   Write for pack lib AVOCADO_esp:
   https://github.com/Ni3nayka/AVOCADO_esp
   
   Write for project AVOCADO:
   https://github.com/Ni3nayka/AVOCADO

   author: Egor Bakay <egor_bakay@inbox.ru>
   write:  november 2022
   modify: november 2022
*/

#pragma once

#ifdef ENABLE_AVOCADO_ESP_WIFI_GAMEPAD

#define GAMEPAD_JOYSTICK_QUANTITY 10
#define GAMEPAD_BUTTON_QUANTITY 30
#define GAMEPAD_ARROW_QUANTITY 10

class AVOCADO_gamepad_translater {
  
  public:

    int gamepad_joystick[GAMEPAD_JOYSTICK_QUANTITY];
    bool gamepad_button[GAMEPAD_BUTTON_QUANTITY];
    int gamepad_arrow[GAMEPAD_ARROW_QUANTITY];
    
    void gamepad_update_data(String input_data);
    void gamepad_clear_arrays();

  private:

};

int number(char a) {
  if      (a=='1') return 1;
  else if (a=='2') return 2;
  else if (a=='3') return 3;
  else if (a=='4') return 4;
  else if (a=='5') return 5;
  else if (a=='6') return 6;
  else if (a=='7') return 7;
  else if (a=='8') return 8;
  else if (a=='9') return 9;
  else return 0;
}

void AVOCADO_gamepad_translater::gamepad_clear_arrays() {
  for (int i = 0; i<GAMEPAD_JOYSTICK_QUANTITY; i++) gamepad_joystick[i] = 0;
  for (int i = 0; i<GAMEPAD_BUTTON_QUANTITY; i++) gamepad_button[i] = 0;
  for (int i = 0; i<GAMEPAD_ARROW_QUANTITY; i++) gamepad_arrow[i] = 0;
}

void AVOCADO_gamepad_translater::gamepad_update_data(String input_data) {
  // AVOCADO_gamepad_esp8266_nodeMCU::gamepad_clear_arrays();
  
  int flag = 0;
  //  { joystick: 0 0 0 0 button: 000000000000 arrow: 0 0 }
  for (int i = 0; input_data[i]!='\n' && input_data[i]!='}' && input_data[i]!=0; i++) {
    char c = input_data[i];
    if      (c=='{') {
      flag = 1;
      AVOCADO_gamepad_translater::gamepad_clear_arrays();
    }
    else if (c=='}') flag = 1000;
    else if (c=='j') flag = 199;
    else if (c=='b') flag = 299;
    else if (c=='a') flag = 399;
    else if (c==':') {
      i++;
      flag++; 
      // continue;
    }
    else if (flag>100 && flag<1000 && flag%100!=99) {
      if (c==' ' || flag>=300 && flag<400) flag++;
      if (c==' ') {}
      else if (flag>=400) {
        if (c=='-') {
          gamepad_arrow[flag-400] = -1;
          i++;
        }
        else if (c=='1') gamepad_arrow[flag-400] = 1;
      }
      else if (flag>=300) gamepad_button[flag-301] = number(c);
      else if (flag>=200) {
        int n = flag-200;
        if (gamepad_joystick[n]==0 && input_data[i-1]=='-') gamepad_joystick[n] = number(c)*(-1);
        else gamepad_joystick[n] = gamepad_joystick[n]*10 + number(c)*(gamepad_joystick[n]>=0?1:-1);
      }
    }
  }
  /*
     String myString = "10500";
     int val = myString.toInt();
     // val теперь 10500
   */
}

#else
class AVOCADO_gamepad_translater {};
#endif
