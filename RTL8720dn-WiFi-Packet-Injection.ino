#include <wifi_conf.h>
#include "wifi_cust_tx.h"

#define WIFI_CHANNEL 48
#define WIFI_SSID "Hidden WiFi"
#define WIFI_PASS "verysecurepassword"

void setup() {
  wifi_on(RTW_MODE_AP); // An access point is needed for frame injection to work properly, but we can just hide its ssid
  wifi_start_ap_with_hidden_ssid(WIFI_SSID, RTW_SECURITY_WPA2_AES_PSK, WIFI_PASS, 11, 18, WIFI_CHANNEL);
}

void loop() {
  uint8_t src_mac[6] = {0xC0, 0x06, 0xC3, 0x05, 0x50, 0x1E};  // Please make sure that this isn't someone elses BSSID
  uint8_t dst_mac[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  // You can replace this with a different BSSID in order to target only one device

  wifi_tx_deauth_frame(src_mac, dst_mac);                     // Transmit a deauth frame
  wifi_tx_beacon_frame(src_mac, dst_mac, "My New SSID");      // Send a beacon frame

  delay(10);
}
