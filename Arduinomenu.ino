//v.1
//you need library LiquidCrystal_V1.2.1.zip
//edit after add LiquidCrystal_V1.2.1.zip file ...\LiquidCrystal\I2CIO.cpp
//str
//
//#include <../Wire/Wire.h>
//to
//
//#include <Wire.h>

#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//it will be 0x3f or maybe 0x27
LiquidCrystal_I2C lcd(0x3f, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

volatile unsigned long start = 0; 
volatile unsigned long stop = 0; 
unsigned long m = 0; 
unsigned long p = 0;
unsigned long l = 0;
unsigned long ll = 0;
unsigned long lll = 0;
unsigned long d = 0;
unsigned long smax = 0;
//button pin
int sp = 6;
//laser pin
int sl = 8;
//led pin
int sd = 13;
//int c = 0;
//int b = 0;
//pm first menu position
int pm = 0;
//submenu choise
int sm = 0;
//int t = 250; 
//boolean sw = false;
boolean done = false;
boolean c = false;
boolean cc = false;
boolean ac = false;
//slon laser button
int slon = EEPROM.read(0);
int slbon = EEPROM.read(1);
int slbt = 0;
int sllon = EEPROM.read(2);
int sllbon = EEPROM.read(3);
int sllbt = 0;
boolean bll = false;
boolean blll = false;
//boolean slon = false;
boolean bl = false;
boolean submenu = false;
boolean ssubmenu = false;
int pb = 0;



void setup() {
pinMode(sp, INPUT);
pinMode(sl, OUTPUT);
pinMode(sd, OUTPUT);
digitalWrite(sp, HIGH);
//Serial.begin(9600);      // open the serial port at 9600 bps:   

lcd.begin(16,2);
byte xx[] = {EEPROM.read(4), EEPROM.read(5)};
int *y = (int *)&xx;
slbt = y[0];
byte xxx[] = {EEPROM.read(6), EEPROM.read(7)};
int *yy = (int *)&xxx;
sllbt = yy[0];

}


  


void loop() {
   
//status

if (pm == 0) {
  
lcd.setCursor(0, 0);
lcd.print("Laser:");
lcd.setCursor(0, 1);
lcd.print("Led:");
if (slon == 0) {
lcd.setCursor(6, 0);
lcd.print("off ");}
if (slon == 1) {
lcd.setCursor(6, 0);
lcd.print("on ");}
if (slbon == 0) {
lcd.setCursor(10, 0);
lcd.print("bl:off");
}
if (slbon == 1) {
lcd.setCursor(10, 0);
lcd.print(slbt);
}
if (sllon == 0) {
lcd.setCursor(4, 1);
lcd.print("off   ");}
if (sllon == 1) {
lcd.setCursor(4, 1);
lcd.print("on    ");}
if (sllbon == 0) {
lcd.setCursor(10, 1);
lcd.print("bl:off ");
}
if (sllbon == 1) {
lcd.setCursor(10, 1);
lcd.print(sllbt);
}
}


if ((slon == 0) && (slbon == 0)) {
digitalWrite (sl, LOW);
}

if ((slon == 1) && (slbon == 0)) {
digitalWrite (sl, HIGH);
}

if ((slon == 1) && (slbon == 1)) {
if ((millis() - ll >  slbt) && (bll == true)){
digitalWrite (sl, HIGH);
ll = millis();
bll = false;
}
if ((millis() - ll >  slbt) && (bll == false)){
digitalWrite (sl, LOW);
ll = millis();
bll = true;
}
}
//led status
if ((sllon == 0) && (sllbon == 0)) {
digitalWrite (sd, LOW);
}

if ((sllon == 1) && (sllbon == 0)) {
digitalWrite (sd, HIGH);
}

if ((sllon == 1) && (sllbon == 1)) {
if ((millis() - lll >  sllbt) && (blll == true)){
digitalWrite (sd, HIGH);
lll = millis();
blll = false;
}
if ((millis() - lll >  sllbt) && (blll == false)){
digitalWrite (sd, LOW);
lll = millis();
blll = true;
}
}


  
  if ((digitalRead(sp) == HIGH))
  {  
p = p + 1;
if (p > 100) {
lcd.setCursor(14, 0);
lcd.print("OK");

}
m = millis();
//Serial.println(p);
  }

if ((millis() - m >  20) && (p > 0)) { 

if (p < 100) {
c = true;
p = 0;
d = millis();
}
if (p > 100) {
cc = true;
p = 0;
d = millis();

}

}

if (cc == true) {
  cc = false;
  done = false;
 if ((submenu == false) && (ssubmenu == false) && (done == false))  {  
submenu = true;
sm = pm;
pm = 1;


d = millis();
done = true;
}

if ((submenu == true) && (ssubmenu == false)&& (done == false)) {  
ssubmenu = true;
ac = true; 

d = millis();

done = true;
}
if ((submenu == true) && (ssubmenu == true)&& (done == false)) {  
ac = false; 
ssubmenu = false;
if (sm == 1 ) {
 byte *x = (byte *)&slbt;
EEPROM.write(4, x[0]);
EEPROM.write(5, x[1]);  
}
if (sm == 2 ) {
 byte *x = (byte *)&sllbt;
EEPROM.write(6, x[0]);
EEPROM.write(7, x[1]);  
}

d = millis();
done = true;
} 
}

if (c == true) {

c = false;
if ((submenu == false) && (ssubmenu == false)) {
pm = pm + 1;
}
if ((submenu == true) && (ssubmenu == false)) {
pm = pm + 1;
}
//Serial.println("c");
if ((pm >= 5) && (submenu == false) && (ssubmenu == false)) {
 pm = 1;
}
if ((pm >= 5) && (submenu == true) && (ssubmenu == false)) {
 pm = 1;
}

if ((submenu == true) && (ssubmenu == true)) {  
ac = true; 

}

}



if ((submenu == false) && (ssubmenu == false)) {

switch (pm) {
  case 1: 
lcd.setCursor(0, 1);
lcd.print("2 Led 13        ");
  break;
  case 2:                                                                                                         
lcd.setCursor(0, 0);
lcd.print("1 Laser         ");
  break;
  case 3:
lcd.setCursor(0, 1);
lcd.print("4 Reset         ");
  break;
  case 4:
lcd.setCursor(0, 0);
lcd.print("3 Info          ");
  break;
}
}
//laser menu
if ((sm == 1) && (submenu == true) && (ssubmenu == false)) {

switch (pm) {
  case 1: 
lcd.setCursor(0, 1);
//lcd.print("Blink Off/On   ");

if ( slbon == 1) {
lcd.print("Blink Off       "); }
else {
lcd.print("Blink On        ");
}

  break;
  case 2:                                                                                                         
lcd.setCursor(0, 0);
//lcd.print("Laser Off/On   ");

if ( slon == 1) {
lcd.print("Laser Off       "); }
else {
lcd.print("Laser On        ");
}

  break;
  case 3:
  lcd.setCursor(0, 1);
lcd.print("Blink Less      ");
  break;
  case 4:                                                                                                         
lcd.setCursor(0, 0);
lcd.print("Blink More      ");
  break;
}

}
//led menu
if ((sm == 2) && (submenu == true) && (ssubmenu == false)) {

switch (pm) {
  case 1: 
lcd.setCursor(0, 1);
//lcd.print("Blink Off/On   ");

if ( sllbon == 1) {
lcd.print("Blink Off       "); }
else {
lcd.print("Blink On        ");
}

  break;
  case 2:                                                                                                         
lcd.setCursor(0, 0);
//lcd.print("Laser Off/On   ");

if ( sllon == 1) {
lcd.print("Led  Off        "); }
else {
lcd.print("Led  On         ");
}

  break;
  case 3:
  lcd.setCursor(0, 1);
lcd.print("Blink Less      ");
  break;
  case 4:                                                                                                         
lcd.setCursor(0, 0);
lcd.print("Blink More      ");
  break;
}

}



//menu starts 


if (pm == 1 && (millis() - l >  450) && (bl == false) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 1 && (millis() - l >  450) && (bl == true) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("1 Laser         ");
l = millis();
bl = false;
}
if (pm == 2 && (millis() - l >  450) && (bl == false) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 2 && (millis() - l >  450) && (bl == true) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("2 Led 13        ");
l = millis();
bl = false;
}
if (pm == 3 && (millis() - l >  450) && (bl == false) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 3 && (millis() - l >  450) && (bl == true) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("3 Info          ");
l = millis();
bl = false;
}
if (pm == 4 && (millis() - l >  450) && (bl == false) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 4 && (millis() - l >  450) && (bl == true) && (submenu == false) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("4 Reset         ");
l = millis();
bl = false;
}
//menu ends 

//submenu starts

if (pm == 1 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 1 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 0);

if ( slon == 1) {
lcd.print("Laser Off       "); }
else {
lcd.print("Laser On        ");
}

l = millis();
bl = false;
}
if (pm == 2 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 2 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 1);


if ( slbon == 1) {
lcd.print("Blink Off       "); }
else {
lcd.print("Blink On        ");
}


l = millis();
bl = false;
}
if (pm == 3 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 3 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("Blink More      ");
l = millis();
bl = false;
}
if (pm == 4 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 4 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 1) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("Blink Less      ");
l = millis();
bl = false;
}
//led submenu
if (pm == 1 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 1 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 0);

if ( sllon == 1) {
lcd.print("Led  Off        "); }
else {
lcd.print("Led  On         ");
}

l = millis();
bl = false;
}
if (pm == 2 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 2 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 1);


if ( sllbon == 1) {
lcd.print("Blink Off       "); }
else {
lcd.print("Blink On        ");
}


l = millis();
bl = false;
}
if (pm == 3 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 3 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("Blink More      ");
l = millis();
bl = false;
}
if (pm == 4 && (millis() - l >  450) && (bl == false) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("                ");
l = millis();
bl = true;
}
if (pm == 4 && (millis() - l >  450) && (bl == true) && (submenu == true) && (sm == 2) && (ssubmenu == false)){
lcd.setCursor(0, 1);
lcd.print("Blink Less      ");
l = millis();
bl = false;
}
//submenu ends

//ssubmenus starts
if ((pm == 3) && (submenu == true) && (sm == 1) && (ssubmenu == true)){
lcd.setCursor(0, 0);
lcd.print("Blink More >>>  ");
lcd.setCursor(0, 1);
lcd.print("               ");
lcd.setCursor(0, 1);
lcd.print(slbt);
}
if ((pm == 4) && (submenu == true) && (sm == 1) && (ssubmenu == true)){
lcd.setCursor(0, 0);
lcd.print("Blink Less <<<  ");
lcd.setCursor(0, 1);
lcd.print("               ");
lcd.setCursor(0, 1);
lcd.print(slbt);
}

if ((pm == 3) && (submenu == true) && (sm == 2) && (ssubmenu == true)){
lcd.setCursor(0, 0);
lcd.print("Blink More >>>  ");
lcd.setCursor(0, 1);
lcd.print("               ");
lcd.setCursor(0, 1);
lcd.print(sllbt);
}
if ((pm == 4) && (submenu == true) && (sm == 2) && (ssubmenu == true)){
lcd.setCursor(0, 0);
lcd.print("Blink Less <<<  ");
lcd.setCursor(0, 1);
lcd.print("               ");
lcd.setCursor(0, 1);
lcd.print(sllbt);
}

if ((pm == 1) && (submenu == true) && (sm == 3) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("Laser Dot Diod  ");
lcd.setCursor(0, 1);
lcd.print("650nm 5mW 5v    ");
}
if ((pm == 2) && (submenu == true) && (sm == 3) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("Led             ");
lcd.setCursor(0, 1);
lcd.print("just led        ");
}
if ((pm == 3) && (submenu == true) && (sm == 3) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("none            ");
lcd.setCursor(0, 1);
lcd.print("3               ");
}
if ((pm == 4) && (submenu == true) && (sm == 3) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("none            ");
lcd.setCursor(0, 1);
lcd.print("4               ");
}
if ((pm == 1) && (submenu == true) && (sm == 4) && (ssubmenu == false)){
lcd.setCursor(0, 0);
lcd.print("Cleaned         ");
lcd.setCursor(0, 1);
lcd.print("                ");
slon = 0;
slbon = 0;
sllon = 0;
sllbon = 0;
slbt = 0;
sllbt = 0;
EEPROM.write(0, 0);
EEPROM.write(1, 0);
EEPROM.write(2, 0);
EEPROM.write(3, 0);
EEPROM.write(4, 0);
EEPROM.write(5, 0);
EEPROM.write(6, 0);
EEPROM.write(7, 0);
}
//actions start
//laser status
if ((ac == true) && (sm == 1) && (pm == 1) && (slon == 1) && (ssubmenu == true)){

slon = 0;
ac = false;
ssubmenu = false;
EEPROM.write(0, 0);

}
if ((ac == true) && (sm == 1) && (pm == 1) && (slon == 0) && (ssubmenu == true)){

slon = 1;
ac = false;
ssubmenu = false;
EEPROM.write(0, 1);

}
//blink status
if ((ac == true) && (submenu == true) && (sm == 1) && (pm == 2) && (slbon == 1) && (ssubmenu == true)){

slbon = 0;
ac = false;
ssubmenu = false;
EEPROM.write(1, 0);
}
if ((ac == true) && (submenu == true) && (sm == 1) && (pm == 2) && (slbon == 0) && (ssubmenu == true)){

slbon = 1;
ac = false;
ssubmenu = false;
EEPROM.write(1, 1);
}
//blink laser more
if ((ac == true) && (submenu == true) && (sm == 1) && (pm == 3) && (ssubmenu == true)){

slbt = slbt + 10;
ac = false;
}
//blink laser less
if ((ac == true) && (submenu == true) && (sm == 1) && (pm == 4) && (ssubmenu == true)){

slbt = slbt - 10;
ac = false;
}
//led status
if ((ac == true) && (sm == 2) && (pm == 1) && (sllon == 1) && (ssubmenu == true)){

sllon = 0;
ac = false;
ssubmenu = false;
EEPROM.write(2, 0);

}
if ((ac == true) && (sm == 2) && (pm == 1) && (sllon == 0) && (ssubmenu == true)){

sllon = 1;
ac = false;
ssubmenu = false;
EEPROM.write(2, 1);

}
//blink status
if ((ac == true) && (submenu == true) && (sm == 2) && (pm == 2) && (sllbon == 1) && (ssubmenu == true)){

sllbon = 0;
ac = false;
ssubmenu = false;
EEPROM.write(3, 0);
}
if ((ac == true) && (submenu == true) && (sm == 2) && (pm == 2) && (sllbon == 0) && (ssubmenu == true)){

sllbon = 1;
ac = false;
ssubmenu = false;
EEPROM.write(3, 1);
}
//blink laser more
if ((ac == true) && (submenu == true) && (sm == 2) && (pm == 3) && (ssubmenu == true)){

sllbt = sllbt + 10;
ac = false;
}
//blink laser less
if ((ac == true) && (submenu == true) && (sm == 2) && (pm == 4) && (ssubmenu == true)){

sllbt = sllbt - 10;
ac = false;
}
//actions ands

//time out menu starts

if ((millis() - d >  5000) && (p == 0)) {
done = false;
if ((ssubmenu == true) && (submenu == true)&& (done == false)){
ssubmenu = false; 
d = millis();
done = true;
}
if ((submenu == true) && (ssubmenu == false) && (done == false)) {
submenu = false;
pm = sm;
sm = 0; 
c = false;
cc = false;
d = millis();
done = true;
}
if ((submenu == false) && (ssubmenu == false) && (done == false)) {
pm = 0;

done = true;
}

}


//time out menu ends

}
//void loop last }


void begin() {
  start = millis(); 
}

void end() {
  stop = millis() - start; 
}
