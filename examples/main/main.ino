#include <MegaInd.h>

const unsigned long TEST_INTERVAL = 10 * 1000;

RTCData rtcData;  // Allocate memory first

MegaInd megaInd = MegaInd(0);

void setup() {
  //Start serial communication
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n\n\n\n\n\n\n\n\Starting HAT...");

  randomSeed(analogRead(0));

  megaInd.begin();
  delay(200);

  Serial.println("Obtaining current date");

  rtcData.year = 26;
  rtcData.month = 7;
  rtcData.day = 31;
  rtcData.hour = 15;
  rtcData.minute = 15;
  rtcData.second = 0;

  megaInd.rtcSet(rtcData);
  delay(200);
  megaInd.rtcGet(rtcData);

  Serial.print(rtcData.month);
  Serial.print("/");
  Serial.print(rtcData.day);
  Serial.print("/");
  Serial.print(rtcData.year);
  Serial.print(" ");
  Serial.print(rtcData.hour);
  Serial.print(":");
  Serial.print(rtcData.minute);
  Serial.print(":");
  Serial.print(rtcData.second);
  Serial.println(" ");
}

void loop() {
  static String line = "";
  static unsigned long previousDisplay = millis() + 100;
  int val;
  double volts;
  int v;
  long wd;
  static bool loopTest = true;

  // if (millis() - previousDisplay >= TEST_INTERVAL) {
  if (loopTest) {
    Serial.println("\nStart Test...");
    // goto x;

    //Get date/time
    megaInd.rtcGet(rtcData);

    Serial.print("\tCurrent date time ");

    Serial.print(rtcData.month);
    Serial.print("/");
    Serial.print(rtcData.day);
    Serial.print("/");
    Serial.print(rtcData.year);
    Serial.print(" ");
    Serial.print(rtcData.hour);
    Serial.print(":");
    Serial.print(rtcData.minute);
    Serial.print(":");
    Serial.print(rtcData.second);
    Serial.println(" ");

    Serial.print("\tgetRTCVolt ");
    volts = megaInd.getRTCVolt();
    Serial.println(volts);

    Serial.print("\tgetRaspVolt ");
    volts = megaInd.getRaspVolt();
    Serial.println(volts);

    Serial.print("\tgetPowerVolt ");
    volts = megaInd.getPowerVolt();
    Serial.println(volts);

    Serial.print("\tgetCpuTemp ");
    int temp = megaInd.getCpuTemp();
    Serial.println(temp);

    Serial.print("\tgetFwVer ");
    double version = megaInd.getFwVer();
    Serial.println(version);

    for (int i = 0; i < 4; i++) {
      Serial.print("\tsetLed ");
      megaInd.setLedAll(0);

      int which1 = random(1, 5);
      megaInd.setLed(which1, 1);
      int which2 = random(1, 5);
      megaInd.setLed(which2, 1);
      Serial.print(which1);
      Serial.print(" and ");
      Serial.println(which2);


      Serial.print("\tgetLed ");
      for (int i = 1; i <= 4; i++) {
        int result = megaInd.getLed(i);
        Serial.print(result, HEX);
        Serial.print(" - ");
      }
      Serial.println(" ");
      delay(2000);
    }

    Serial.print("\tgetUinRange -10 - 10v ");

    megaInd.setUinRange(1, 1);
    v = random(-10, 10);
    Serial.print(v);
    Serial.print(" - ");

    for (int i = 1; i <= 4; i++) {
      val = megaInd.getUinRange(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(":");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");

    Serial.print("\tgetpm10In ");
    for (int i = 1; i <= 4; i++) {
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      volts = megaInd.getpm10In(i);
      Serial.print(volts);
      Serial.print(" ");
    }
    Serial.println(" ");


    Serial.print("\tgetUinRange ");


    megaInd.setUinRange(1, 0);
    v = random(0, 10);
    Serial.print(v);

    for (int i = 1; i <= 4; i++) {
      val = megaInd.getUinRange(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(":");
      Serial.print(val);
    }
    Serial.println(" ");

    Serial.print("\tset0_10Out ");
    for (int i = 1; i <= 4; i++)
      val = megaInd.set0_10Out(i, 0);
    int c = random(1, 5);
    int r = random(1, v);
    val = megaInd.set0_10Out(c, v);
    Serial.print(c);
    Serial.print(":");
    Serial.println(v);

    Serial.print("\tget0_10Out ");
    for (int i = 1; i <= 4; i++) {
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      volts = megaInd.get0_10Out(i);
      Serial.print(volts);
      Serial.print(" ");
    }
    Serial.println(" ");

    Serial.print("\tget0_10In ");

    for (int i = 1; i <= 4; i++) {
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      volts = megaInd.get0_10In(i);
      Serial.print(volts);
      Serial.print("V ");
    }
    Serial.println(" ");


    for (int i = 1; i <= 4; i++)
      val = megaInd.set4_20Out(i, 0);

    Serial.print("\tset4_20Out ");

    for (int i = 1; i <= 4; i++) {
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      v = random(4, 20);
      val = megaInd.set4_20Out(i, v);
      Serial.print(v);
      Serial.print(" mA ");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println(" ");

    Serial.print("\tget4_20Out ");

    for (int i = 1; i <= 4; i++) {
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      volts = megaInd.get4_20Out(i);
      Serial.print(volts);
      Serial.print(" mA ");
    }
    Serial.println(" ");

    Serial.print("\tget4_20In ");

    for (int i = 1; i <= 4; i++) {
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      volts = megaInd.get4_20In(i);
      Serial.print(volts);
      Serial.print(" mA ");
    }
    Serial.println(" ");


    Serial.print("\tgetOptoCh ");

    for (int i = 1; i <= 4; i++)
      val = megaInd.set0_10Out(i, 0);
    v = random(5, 12);
    val = megaInd.set0_10Out(4, v);
    Serial.print(v);
    Serial.println("V");
    delay(1000);
    val = megaInd.set0_10Out(4, 0);

    Serial.print("\tgetOptoCh ");

    for (int i = 1; i <= 4; i++) {
      val = megaInd.getOptoCh(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(":");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");


    Serial.print("\tsetOptoRisingCountEnable ");

    val = megaInd.setOptoRisingCountEnable(4, 1);
    Serial.print(":");
    Serial.println(val);


    Serial.print("\tgetOptoRisingCountEnable ");

    for (int i = 1; i <= 4; i++) {
      val = megaInd.getOptoRisingCountEnable(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(":");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");

    delay(3000);
    Serial.print("\tgetOpto ");

    val = megaInd.getOpto();
    Serial.print(":");
    Serial.println(val);

    Serial.print("\tgetOptoCount ");

    for (int i = 1; i <= 4; i++) {
      val = megaInd.getOptoCount(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(":");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");

    Serial.print("\trstOptoCount ");
    for (int i = 1; i <= 4; i++) {
      val = megaInd.rstOptoCount(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(":");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");

    Serial.print("\tsetOdPWM ");
    for (int i = 1; i <= 4; i++) {
      v = random(0, 100);
      val = megaInd.setOdPWM(i, v);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(v);
      Serial.print(" ");
    }
    Serial.println("");

    Serial.print("\tgetOdPWM ");

    for (int i = 1; i <= 4; i++) {
      val = megaInd.getOdPWM(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");

    /*
    Serial.print("\tbutton ");
    if (megaInd.readButton())
      Serial.println("megaInd.readButton()");
*/

    Serial.print("\tsetOd \t\t");
    for (int i = 1; i <= 4; i++) {
      v = random(0, 1 + 1);
      val = megaInd.setOd(i, v);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(v);
      Serial.print(" ");
    }
    Serial.println("");

    Serial.print("\tgetOd \t\t");
    for (int i = 1; i <= 4; i++) {
      val = megaInd.getOd(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");

    Serial.print("\tgetOptoFrequency ");

    for (int i = 1; i <= 4; i++) {
      val = megaInd.getOptoFrequency(i);
      Serial.print("\t");
      Serial.print(i);
      Serial.print(" ");
      Serial.print(val);
      Serial.print(" ");
    }
    Serial.println("");


    Serial.print("\towbScan ");

    val = megaInd.owbScan();
    Serial.print("\t");
    Serial.print(val);
    Serial.println("");

    Serial.print("\towbGetSensorNo ");

    val = megaInd.owbGetSensorNo();
    Serial.print("\t");
    Serial.print(val);
    Serial.println("");

x:

    Serial.print("\twdtSetPeriod ");

    v = random(0, 3000);
    Serial.print("\t");
    Serial.print(v);
    val = megaInd.wdtSetPeriod(v);
    Serial.print(" ");
    Serial.print(val);
    Serial.println(" ");

    Serial.print("\twdtGetPeriod ");
    wd = megaInd.wdtGetPeriod();
    Serial.print("\t");
    Serial.println(wd);

    Serial.print("\twdtReload ");

    val = megaInd.wdtReload();
    Serial.print("\t");
    Serial.print(val);
    wd = megaInd.wdtGetPeriod();
    Serial.print("\t");
    Serial.println(wd);

    Serial.print("\twdtSetDefaultPeriod ");

    v = random(0, 3000);
    Serial.print("\t");
    Serial.print(v);
    val = megaInd.wdtSetDefaultPeriod(v);
    Serial.print(" ");
    Serial.print(val);
    Serial.println(" ");

    Serial.print("\twdtGetDefaultPeriod ");
    wd = megaInd.wdtGetDefaultPeriod();
    Serial.print("\t");
    Serial.println(wd);


    Serial.print("\twdtSetOffInterval ");

    wd = random(0, 3000);
    Serial.print("\t");
    Serial.print(wd);
    val = megaInd.wdtSetOffInterval(wd);
    Serial.print(" ");
    Serial.print(val);
    Serial.println(" ");

    Serial.print("\twdtGetOffInterval ");

    wd = megaInd.wdtGetOffInterval();
    Serial.print("\t");
    Serial.print(wd);
    Serial.println(" ");

    Serial.print("\twdtGetResetCount ");
    v = megaInd.wdtGetResetCount();
    Serial.print("\t");
    Serial.println(v);

    loopTest = false;

    //wait for some time
    previousDisplay = millis();
  }
}
