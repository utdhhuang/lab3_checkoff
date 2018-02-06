volatile int state = LOW;
volatile int flag = HIGH;


String inputString = "";
boolean stringComplete = false;
boolean enable_flag = 0;
boolean mode_flag = 1;


int myArray[20];
int myTimeArray[20];
float myVoltageArray[20];
int count = 0;
int storedVals = 0;
 
void setup()
{
  Serial.begin(9600);
  inputString.reserve(200);

  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, state);

  pinMode(PUSH2, INPUT_PULLUP);
  attachInterrupt(PUSH2, blink, FALLING);
}

void loop()
{
    if (enable_flag and mode_flag)
  {
      digitalWrite(GREEN_LED, state); //LED starts OFF
      if(flag) {
      count++;
      Serial.println(count);
      flag = LOW;
      int sensorValue = analogRead(A3);
      Serial.println(sensorValue);
      delay(500);
  }
  }
  if (enable_flag and !mode_flag)
  {
      int sensorValue = analogRead(A3);
      Serial.println(sensorValue);
      delay(500);
  }
  if (stringComplete)
  {
    Serial.println(inputString);
    if (inputString == "menu\n")
    {
      Serial.println("enable\ndisable\nauto\nmanual\ndisplay\nerase\nstats\n");
    }
    else if (inputString == "enable\n")
    {
      Serial.println("auto or manual?");
    //check to see if already enabled
    if(enable_flag)
    {
    Serial.println("already enabled!");
    }
    else
    {
     enable_flag = 1;
     Serial.println("enabled!");
    }
    }
  else if (inputString == "disable\n")
    {
      Serial.println("checking for disable...");
    //check to see if already disabled
    if(!enable_flag)
    {
    Serial.println("already disabled!");
    }
    else
    {
     enable_flag = 0;
     Serial.println("disabled!");
    }
    }
  else if (inputString == "auto\n")
    {
      Serial.println("checking for auto...");
        //check to see if already auto
    if(!mode_flag)
    {
    Serial.println("auto already enabled!");
    }
    else
    {
     mode_flag = 0;
     Serial.println("auto enabled!");
    }
    }
  else if (inputString == "manual\n")
    {
      Serial.println("checking for manual...");
    //check to see if already manual
    if(mode_flag)
    {
    Serial.println("manual already enabled!");
    }
    else
    {
     mode_flag = 1;
     Serial.println("manual enabled!");
    }
    }
  else if (inputString == "display\n")
    {
      Serial.println("calling display...");
    }
  else if (inputString == "erase\n")
    {
      Serial.println("calling erase...");
    }
  else if (inputString == "stats\n")
    {
      Serial.println("calling stats...");
    }
  else
  {
      Serial.println("bad input, type 'menu' for a list of options...");
  }
    inputString = "";
    stringComplete = false;
    
  }


}

void serialEvent()
{
  while(Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

void blink()
{
  state = !state;
  flag = HIGH;
}


