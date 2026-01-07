/*
 * ESP32 Rickroll Captive Portal
 * 
 * A harmless prank captive portal that broadcasts a "free wifi" network
 * and serves a full-screen rickroll GIF when users connect.
 * 
 * Built with Arduino framework for maximum portability across ESP32 boards.
 * 
 * Credits:
 * - ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
 * - PlatformIO: https://github.com/platformio/platformio-core
 * - ESP32-C6 Arduino Support: https://github.com/pioarduino/platform-espressif32
 * 
 * DISCLAIMER: This software is for educational and harmless prank purposes only.
 * Use responsibly and in compliance with local laws and regulations.
 * 
 * License: MIT (see LICENSE file)
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <LittleFS.h>

const char* ssid = "free wifi";
const char* password = ""; // Open network

WebServer server(80);
DNSServer dnsServer;

// HTML page with full-screen rickroll GIF
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
    <title></title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        html, body {
            width: 100%;
            height: 100%;
            overflow: hidden;
            background: #000;
        }
        img {
            width: 100vw;
            height: 100vh;
            object-fit: contain;
            display: block;
            image-rendering: auto;
        }
    </style>
</head>
    <body>
    <img src="/rickroll.gif?t=1" alt="" id="gif">
    <script>
        // Force reload if GIF doesn't animate
        setTimeout(function() {
            var img = document.getElementById('gif');
            var src = img.src.split('?')[0];
            img.src = src + '?t=' + new Date().getTime();
        }, 100);
    </script>
</body>
</html>
)rawliteral";

void handleRoot() {
    server.send_P(200, "text/html", index_html);
}

void handleGIF() {
    File file = LittleFS.open("/rickroll.gif", "r");
    if (!file) {
        server.send(404, "text/plain", "GIF not found");
        return;
    }
    
    // Set headers to prevent caching and ensure proper content type
    server.sendHeader("Content-Type", "image/gif");
    server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
    server.sendHeader("Pragma", "no-cache");
    server.sendHeader("Expires", "0");
    
    // Use streamFile which handles binary data correctly
    server.streamFile(file, "image/gif");
    file.close();
}

void handleGenerate204() {
    server.send_P(200, "text/html", index_html);
}

void handleConnectTest() {
    // Windows checks this, but we still rickroll them
    server.send_P(200, "text/html", index_html);
}

void handleNotFound() {
    server.send_P(200, "text/html", index_html);
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    // Initialize LittleFS
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
        return;
    }

    // Start WiFi Access Point
    Serial.println("Starting WiFi Access Point...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    // Setup DNS server for captive portal - redirect ALL DNS queries
    dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
    dnsServer.start(53, "*", IP); // Redirect all DNS queries to our IP

    // Setup web server routes - handle all captive portal detection endpoints
    server.on("/", handleRoot);
    server.on("/rickroll.gif", HTTP_GET, handleGIF);
    
    // Android captive portal detection
    server.on("/generate_204", handleGenerate204);
    server.on("/gen_204", handleGenerate204);
    
    // iOS captive portal detection
    server.on("/hotspot-detect.html", handleGenerate204);
    server.on("/library/test/success.html", handleGenerate204);
    server.on("/success.txt", handleGenerate204);
    
    // Windows captive portal detection
    server.on("/connecttest.txt", handleConnectTest);
    server.on("/ncsi.txt", handleConnectTest);
    server.on("/redirect", handleGenerate204);
    
    // Additional common endpoints
    server.on("/fwlink", handleGenerate204);
    server.on("/canonical.html", handleGenerate204);
    server.on("/kindle-wifi/wifiredirect.html", handleGenerate204);
    
    // Catch-all - redirect everything to rickroll
    server.onNotFound(handleNotFound);

    // Start web server
    server.begin();
    Serial.println("HTTP server started");
    Serial.println("Captive portal is ready!");
    Serial.println("Connect to 'free wifi' network and open any website");
}

void loop() {
    // Process DNS requests immediately for faster captive portal triggering
    dnsServer.processNextRequest();
    server.handleClient();
    delay(1); // Minimal delay for faster response
}
