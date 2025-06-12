#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>

WebServer server(80); // Make ESP32 a website on port 80
//Port 80 --> the standard port number for websites

const char *SSID = "ACSlab";
const char *PASSWORD = "lab@ACS24";


void setup()
{
  Serial.begin(115200);
  Serial.print("Enabled serial communication");

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Open this in browser:\n http://");
  Serial.println(WiFi.localIP());

  // Set up camera
  camera_config_t config;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sccb_sda = 26;
  config.pin_sccb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.frame_size = FRAMESIZE_QVGA;
  config.jpeg_quality = 10;
  config.fb_count = 2;
  esp_camera_init(&config);

  // When someone visits the website, show them the video
  server.on("/", []()
            { server.send(200, "text/html", "<img src='/video'>"); });

  server.on("/video", []()
            {
        server.send(200, "multipart/x-mixed-replace; boundary=frame");
        while(true) {
            camera_fb_t * fb = esp_camera_fb_get();  // Get one picture from camera
            server.sendContent("--frame\r\nContent-Type: image/jpeg\r\n\r\n");
            server.sendContent_P((char*)fb->buf, fb->len);  // Send the picture
            server.sendContent("\r\n");
            esp_camera_fb_return(fb);  // Give picture back to camera
            delay(100);
        } });

  server.begin();
}

void loop()
{
  server.handleClient();
}

//https://github.com/Mausam678/ESP32-WiFi-Connection-Example/blob/main/ESP32-WiFi-Connection-Example