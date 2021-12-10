const int ph_Pin  = A0;
float Po = 0;
float PH_step;
int nilai_analog_PH;
double TeganganPh;

//untuk kalibrasi
float PH4 = 3.226;
float PH7 = 2.691;

void setup()
{
  pinMode (ph_Pin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  nilai_analog_PH = analogRead(ph_Pin);
  Serial.print("Nilai ADC Ph: ");
  Serial.println(nilai_analog_PH);
  TeganganPh = 3.3 / 1024.0 * nilai_analog_PH;
  Serial.print("TeganganPh: ");
  Serial.println(TeganganPh, 3);

  PH_step = (PH4 - PH7) / 3;
  Po = 7.00 + ((PH7 - TeganganPh) / PH_step);     //Po = 7.00 + ((teganganPh7 - TeganganPh) / PhStep);
  Serial.print("Nilai PH cairan: ");
  Serial.println(Po, 2);
  delay(3000);
}

/*
 * PH step = (tegangan PH4 – tegangan PH7) / (PH7 - PH4)
             = (3.1 – 2.5)/(7-4)
             = 0.6/3
             = 0.2
 */
