#include <TimerOne.h>  //подключение библиотеки с таймером.

  int VoltagePinBAT = A0; //пин АЦП аккумулятора.
  int VoltagePinCHG = A1; //пин АЦП заряда.
  int RelayOutput = 2; //пин управления реле 1(подача питания к нагрузке)
  int RelayCHG = 3; //пин реле 2(подключение заряда)
  float VoltageBAT = 0; //переменная значения напряжения аккумулятора.
  float VoltageCHG = 0; //переменная значения напряжения заряда.

void setup() {
  Serial.begin(9600);
  Timer1.initialize(2000000); //инициализируем таймер на 2 сек.
  Timer1.attachInterrupt(Timer1_action); //присваеваем таймеру функцию Timer1_action
  pinMode(VoltagePinBAT, INPUT); //настраиваем пин
  pinMode(RelayOutput, OUTPUT);
  pinMode(RelayCHG, OUTPUT);
}

void loop() {
  
}

void Timer1_action()         //функция привязаная к таймеру
{
 
VoltageCHG = (analogRead(VoltagePinCHG)) * 0.0146; //замер и приведение к вольтам напряжения заряда.
VoltageBAT = (analogRead(VoltagePinBAT)) * 0.0146; //замер и приведение к вольтам напряжения аккумулятора.
  if (VoltageCHG > 13) //Если напряжение заряда больше 13 вольт
    {
      if (digitalRead(RelayCHG)==LOW) {digitalWrite(RelayCHG,HIGH);} // то, если при этом еле было выключено, включаем реле заряда.
      
    }
  else if (VoltageCHG < 12.5) //Если напряжение заряда меньше 12.5 
    {
      if (digitalRead(RelayCHG)==HIGH) {digitalWrite(RelayCHG,LOW);} // то, если при этом реле было включено, вылючаем реле заряда.
     
    }
  if (VoltageBAT > 12 or digitalRead(RelayCHG)==HIGH) //Если напряжение батареи больше 12 вольт или реле заряда включено,
    {
      if (digitalRead(RelayOutput)==LOW) {digitalWrite(RelayOutput,HIGH);} // то, если при этом реле было выключено, включаем реле заряда.
    }
  else if (VoltageBAT < 11) //Если напряжение батареи меньше 11 вольт 
    {
      if (digitalRead(RelayOutput)==HIGH) {digitalWrite(RelayOutput,LOW);} // то, если при этом реле было включено, вылючаем реле заряда.
    }

    //ВЫВОД В ПОРТ
if (digitalRead(RelayCHG)==HIGH){ Serial.println("CHG ON");} //вывод статуса заряда 
else { Serial.println("CHG OFF");} //вывод статуса заряда 
if (digitalRead(RelayOutput)==HIGH){ Serial.println("OUT ON");} //вывод статуса выхода  
else { Serial.println("OUT OFF");} //вывод статуса выхода
Serial.print("Battery voltage is: ");
Serial.println(VoltageBAT); //вывод напряжения батареи
Serial.print("Charging voltage is: ");
Serial.println(VoltageCHG); //вывод напряжения заряда
}
