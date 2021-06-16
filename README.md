# DesktopCapture RTSP Server
RTSP Streaming(source: Desktop screen capture) Server using GStreamer
Desktop screen capture(Windows OS) using GStreamer 

<br>
<br>
<br>

### Step 1. Install 'GStreamer' (runtime & development)

1) download(https://gstreamer.freedesktop.org/download/)

<br>

![캡처1](https://user-images.githubusercontent.com/85919240/122022422-86fdc800-ce01-11eb-9179-313beec47b0e.PNG)

2) setup type 'Complete'

<br>

![캡처2](https://user-images.githubusercontent.com/85919240/122022607-b7456680-ce01-11eb-87d2-3df628ae8b70.PNG)

<br>

### Step 2. Add environment variable

    Add 'Path' to '$(My GStreamer path)\bin'
    
<bt>
  
### Step 3. Header file copy

    Copy '$(My GStreamer path)\lib\glib-2.0\include\glibconfig.h' to '$(My GStreamer path)\include\glib-2.0\glib'
  
<br>
 
### Step 4. 'Visual Studio(My version = 2019)' configuration
  
  1) Project properties -> Debugging -> Environment
  
    Add 'path=%path%;$(My GStreamer path)\bin'
  
  <br>
  
![캡처3](https://user-images.githubusercontent.com/85919240/122024495-72223400-ce03-11eb-804d-aa512a1c186f.PNG)
  
  <br>
  
  2) Project properties -> C/C++ -> General -> Additional include directories
  
    Add '$(My GStreamer path)\include\gstreamer-1.0'
    Add '$(My GStreamer path)\include\glib-2.0'
    Add '$(My GStreamer path)\include\libxml2'
    Add '$(My GStreamer path)\include'
  
  <br>
  
  
![캡처4](https://user-images.githubusercontent.com/85919240/122025435-53706d00-ce04-11eb-910e-84c146105d5a.PNG)
  
  
  <br>
  
  3) Project properties -> Linker -> General -> Additional library directories
  
    Add '$(My GStreamer path)\lib'
  
  <br>
  
  
![캡처5](https://user-images.githubusercontent.com/85919240/122025669-80248480-ce04-11eb-9edb-57ba08b01bb0.PNG)
  
  
  <br>
  
  4) Project properties -> Linker -> Input -> Additional dependencies
  
    Add 'gobject-2.0.lib'
    Add 'glib-2.0.lib'
    Add 'gstreamer-1.0.lib'
    Add 'gstrtspserver-1.0.lib'

  <br>
  
  
![캡처6](https://user-images.githubusercontent.com/85919240/122025863-afd38c80-ce04-11eb-89c6-4fabde6b308b.PNG)

  
  <br>

  





