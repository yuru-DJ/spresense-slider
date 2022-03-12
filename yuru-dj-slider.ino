#include <Wire.h>
#include <RPR-0521RS.h>

RPR0521RS rpr0521rs;

void setup() {
  byte rc;

  Serial.begin(115200);    /*  Modify : set the serial speed to 11500 kbps  */
  while (!Serial);

  Wire.begin();

  rc = rpr0521rs.init();
}

void loop() {
  byte rc;
  unsigned short ps_val;
  float als_val;
  byte near_far;

  rc = rpr0521rs.get_psalsval(&ps_val, &als_val);
  if (rc == 0) {
    Serial.print(F("RPR-0521RS (Proximity)     = "));
    Serial.print(ps_val);
    Serial.print(F(" [count]"));
    near_far = rpr0521rs.check_near_far(ps_val);
    if (near_far == RPR0521RS_NEAR_VAL) {
      Serial.println(F(" Near"));
    } else {
      Serial.println(F(" Far"));
    }

    if (als_val != RPR0521RS_ERROR) {
      Serial.print(F("RPR-0521RS (Ambient Light) = "));
      Serial.print(als_val);
      Serial.println(F(" [lx]"));
      Serial.println();
    }
  }

  delay(500);
}
