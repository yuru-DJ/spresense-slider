#include <Wire.h>
#include <RPR-0521RS.h>

RPR0521RS rpr0521rs;

void setup() {
  Serial.begin(115200);

  Wire.begin();

  byte rc = rpr0521rs.init();
}

void loop() {
  byte rc;
  unsigned short ps_val;
  float als_val;
  byte near_far;

  rc = rpr0521rs.get_psalsval(&ps_val, &als_val);
  if (rc == 0) {
    near_far = rpr0521rs.check_near_far(ps_val);
    if (near_far == RPR0521RS_NEAR_VAL) {
      Serial.println("NEAR");
    } else {
      Serial.println("FAR");
    }
  }

  delay(10);
}
