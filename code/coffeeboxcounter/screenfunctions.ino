void display_users_debug(){
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  for(int i = 0; i<NUM_USERS; i++){
    display.print(users[i].name);
    display.print("    ");
    for(int y = 0; y<4; y++){
      display.print(users[i].uid[y],HEX);
    }
    display.print("\n");
  }
  display.display();
}

void display_users_totals(){
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("TOTALS");
  display.print("\n");
  display.print("USER");
  display.print("   ");
  display.print("COFFEES");
  display.print("\n");

  for(int i = 0; i<NUM_USERS; i++){
    display.print(users[i].name);
    display.print("    ");
    display.print(users[i].current_total);
    display.print("\n");
  }
  display.display();
}

void splash_screen(){
  display.clearDisplay();

  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("COFFEEBOX");
  display.println("COUNTER\n");
  display.print("Ver: b");
  display.print(VERS);
  display.display();
}

void coffee_animate(){
  //display.display();
    // Clear the buffer.
  display.clearDisplay();

  display.clearDisplay();
  display.drawBitmap(0, 8, anim01, 128, 64, WHITE);
  display.display();
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 8, anim02, 128, 64, WHITE);
  display.display();
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 8, anim03, 128, 64, WHITE);
  display.display();
  for (int cnt = 0; cnt < 2; cnt++) {
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 8, anim04, 128, 64, WHITE);
  display.display();
  delay(700);
  display.clearDisplay();
  display.drawBitmap(0, 8, anim05, 128, 64, WHITE);
  display.display();
  }
}
