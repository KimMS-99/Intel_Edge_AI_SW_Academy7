// PIR 노이즈 억제(비대칭 안정시간) + 예열 + 예열 종료 안내 출력
const int LED_PIN = 8;
const int PIR_PIN = 9;

const unsigned long WARMUP_MS = 30000;    // 30s (AM312면 5000)
const unsigned long ON_STABLE_MS = 100;   // HIGH 100ms 지속 시 '감지'
const unsigned long OFF_STABLE_MS = 2000; // LOW 2s 지속 시 '미감지'

bool motion = false;
int lastRaw = LOW;
unsigned long lastEdgeMs = 0;
unsigned long t0;

bool readyAnnounced = false; // ← 예열 종료 알림 1회용 플래그

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(PIR_PIN, INPUT);
    Serial.begin(115200);
    Serial.println("PIR warm-up...");
    t0 = millis();
}

void loop()
{
    unsigned long now = millis();
    unsigned long elapsed = now - t0;

    // 1) 예열 구간은 무시
    if (elapsed < WARMUP_MS)
    {
        digitalWrite(LED_PIN, LOW);
        return;
    }
    // 1-1) 예열이 끝난 '첫 순간'에만 한 번 출력
    if (!readyAnnounced)
    {
        readyAnnounced = true;
        Serial.println("Warm-up done. PIR monitoring started.");
    }

    // 2) 노이즈 억제: 상태 변화 감지
    int raw = digitalRead(PIR_PIN);
    if (raw != lastRaw)
    {
        lastRaw = raw;
        lastEdgeMs = now; // 에지 시각 갱신
    }

    // 3) 안정시간 충족 시 상태 전환
    if (!motion && raw == HIGH && (now - lastEdgeMs >= ON_STABLE_MS))
    {
        motion = true;
        digitalWrite(LED_PIN, HIGH);
        Serial.println("MOTION START");
    }
    if (motion && raw == LOW && (now - lastEdgeMs >= OFF_STABLE_MS))
    {
        motion = false;
        digitalWrite(LED_PIN, LOW);
        Serial.println("MOTION END");
    }

    delay(5);
}
