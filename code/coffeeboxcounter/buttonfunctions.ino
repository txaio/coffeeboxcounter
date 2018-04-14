void step_counter(){

}

void btn_pushed(){
  Serial.println("#BUTTON PUSHED INTERRUPT");
  display_users_debug();
  delay(1000);
}
