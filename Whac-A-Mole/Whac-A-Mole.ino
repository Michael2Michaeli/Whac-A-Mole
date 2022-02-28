/*
 Name:		Whac_A_Mole.ino
 Created:	2/26/2022 9:34:19 PM
 Author:	micha
*/
#define buttons 3

long randNumber;
int step_counter = 0;

int analogValue = 0;

int p1_first_pin = 22;
int p1_buttons[buttons];
int p1_leds[buttons];

int p2_first_pin = 30;
int p2_buttons[buttons];
int p2_leds[buttons];

int p1_score = 0;
int p2_score = 0;

int action_speed = 1000; //delay
int action_speed_start = 1000;
unsigned long previousMillis = 0;

int pin_light;


void setup()
{
    Serial.begin(9600);

    randomSeed(analogRead(A7));
    
    for (int i = 0; i < buttons; i++)
    {
        //player 1
        p1_leds[i] = p1_first_pin + i*2;
        pinMode(p1_leds[i], OUTPUT);

        p1_buttons[i] = p1_first_pin + i * 2 + 1;
        pinMode(p1_buttons[i], INPUT_PULLUP);
        
        //player 2
        p2_leds[i] = p2_first_pin + i * 2;
        pinMode(p2_leds[i], OUTPUT);
                
        p2_buttons[i] = p2_first_pin + i * 2 + 1;
        pinMode(p2_buttons[i], INPUT_PULLUP);
        
    }       
}

bool onePlayerGame;
bool twoPlayersGame;
unsigned long currentMillis;

void loop()
{
    
    //game choose
    while (true)
    {
        for (int i = 0; i < 2; i++)
        {
            digitalWrite(p1_leds[i], HIGH);
        }

        if (digitalRead(p1_buttons[0])==LOW)
        {
            onePlayerGame = true;
            Serial.println("one player game is choose!");
            break;
        }
        else if (digitalRead(p1_buttons[1])==LOW)
        {
            twoPlayersGame = true;
            break;
        }
        
    }

    //game for 1 player
    while (onePlayerGame)
    {
        currentMillis = millis();
        
        if (p1_score < 100)
        {          
            //set button light
            if (currentMillis - previousMillis >= action_speed)
            {                
                digitalWrite(p1_leds[pin_light], LOW);
                previousMillis = currentMillis;
                pin_light = random(0, buttons);
                digitalWrite(p1_leds[pin_light], HIGH);
            }

            //get button press from player
            for (int i = 0; i < buttons; i++)
            {
                //player 1
                if (digitalRead(p1_buttons[i]) == LOW and digitalRead(p1_leds[i]))
                {
                    digitalWrite(p1_leds[i], LOW);
                    p1_score++;
                    Serial.print("Player 1 Score: ");
                    Serial.println(p1_score);
                    action_speed = action_speed_start * exp(-0.03 * p1_score);
                    //Serial.println(action_speed);
                }

            }
        }
        else
        {
            for (int i = 0; i < buttons; i++)
            {
                digitalWrite(p1_leds[i], HIGH);
            }
            delay(500);
            for (int i = 0; i < buttons; i++)
            {
                digitalWrite(p1_leds[i], LOW);
            }
            delay(500);
        }
    }    

    //game for 1 player
    while (twoPlayersGame)
    {
        currentMillis = millis();

        if (p1_score < 100 and p2_score<100)
        {
            //set button light
            if (currentMillis - previousMillis >= action_speed)
            {
                digitalWrite(p1_leds[pin_light], LOW);
                previousMillis = currentMillis;
                pin_light = random(0, buttons);
                digitalWrite(p1_leds[pin_light], HIGH);
            }

            //get button press from player
            for (int i = 0; i < buttons; i++)
            {
                //player 1
                if (digitalRead(p1_buttons[i]) == LOW and digitalRead(p1_leds[i]))
                {
                    digitalWrite(p1_leds[i], LOW);
                    p1_score++;
                    Serial.print("Player 1 Score: ");
                    Serial.println(p1_score);
                    action_speed = action_speed_start * exp(-0.03 * p1_score);
                    //Serial.println(action_speed);
                }

            }
        }
        else
        {
            for (int i = 0; i < buttons; i++)
            {
                digitalWrite(p1_leds[i], HIGH);
            }
            delay(500);
            for (int i = 0; i < buttons; i++)
            {
                digitalWrite(p1_leds[i], LOW);
            }
            delay(500);
        }
    }
}