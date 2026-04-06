
const int lalulintasHijau = 11;
const int lalulintasKuning = 10;
const int lalulintasMerah = 9;
const int PejalanHijau = 13;
const int PejalanMerah = 12;
const int buttonPin = 2;

// Variable flag untuk interrupt
volatile bool crossRequest = false;

void setup() {
  pinMode(lalulintasHijau, OUTPUT);
  pinMode(lalulintasKuning, OUTPUT);
  pinMode(lalulintasMerah, OUTPUT);
  pinMode (PejalanHijau, OUTPUT);
  pinMode(PejalanMerah, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // menggunakan Interrupt 0 pada Pin 2
  // trigger saat tombol ditekan
  attachInterrupt(digitalPinToInterrupt(buttonPin), pejalanWait, FALLING);

  //kondisi Awal
  setInitialState();
}

void loop() {
  if (crossRequest) {
    delay(500); //jeda tombol ditekan
    ubahTraffic();
    crossRequest = false; // Reset permintaan
  }
}

//fungsi yang dijalankan saat interrupt aktif
void pejalanWait() {
  crossRequest = true;
}

void setInitialState() {
  digitalWrite(lalulintasHijau, HIGH);
  digitalWrite(lalulintasKuning, LOW);
  digitalWrite(lalulintasMerah, LOW);
  digitalWrite(PejalanHijau, LOW);
  digitalWrite(PejalanMerah, HIGH);
}
 
void ubahTraffic() {
  //saat button ditekan, kendaraan merah, pedestrian hijau
  digitalWrite(lalulintasHijau, LOW);
  digitalWrite(lalulintasMerah, HIGH);
  delay(500); //jeda
  digitalWrite(PejalanMerah, LOW);
  digitalWrite(PejalanHijau, HIGH);

  //menentukan waktu menyeberang
  delay(5000);

  //setelah waktu tertentu, pedestrian kembali Merah
  digitalWrite(PejalanHijau, LOW);
  digitalWrite(PejalanMerah, HIGH);
  delay(1000);

  //kendaraan masuk fase Kuning (transisi)
  digitalWrite(lalulintasMerah, LOW);
  digitalWrite(lalulintasKuning, HIGH);
  delay(2000);

  //kembali ke kondisi awal
  setInitialState();
}