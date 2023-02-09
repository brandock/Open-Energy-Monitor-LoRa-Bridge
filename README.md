# Open-Energy-Monitor-LoRa-Bridge

My father is using Open Energy Monitor to monitor a heat pump in his new machine shop. There's no internet access in the shop, so he was taking his laptop out there periodically and downloading the emonCMS data via browser. I wanted to set up a relay for him so that the Pi base station could be in his house. It would go: OEM sensors in shop --> Moteino with RFM69CW in the shop<----->Moteino with LoRa in the shop<-----> Moteino with LoRa in the house ---> OEM base station. I think of this as a "relay", but maybe the better word is "bridge".  

![scheme](https://user-images.githubusercontent.com/17953028/212793142-f43c6f35-0e1f-4bd8-a04c-65432b14b4fb.jpg)

It works! The shop is about 70 meters from the house with some other building in between. The packets are arriving as expected in the house for over a month now.
![map](https://user-images.githubusercontent.com/17953028/212793119-a436af30-64d8-4e7a-918c-144504f75a62.jpg)

I did this using three Moteinos.
![LoRa Bridge](https://user-images.githubusercontent.com/17953028/213946740-c6d2ad57-546d-475c-8f94-bcc7c9d5ef4b.jpg)

**Moteino 1**: RFM69 radio receiving packets and repeating them via serial, similar to the receiver used with the Pi Gateway (or in this case, more similar to RFM69Pi from OEM).<br>
**Moteino 2**: LoRa radio. Listens to serial packets and repeats them via the radio.<br>
**Moteino 3**: LoRa radio. Receives packets via LoRa and repeats them via serial. Essentially an RFM2Pi.<br>


I found it easiest to wire the serial connection between Moteino 1 and Moteino 2 by flipping the former belly-up (radio side up). I used right angle headers and some protoboard. 

There are three sketches needed, and the USB interfacer (Moteino 3) needs to be added to the emonHub configuration file (emonCMS > Setup > emonHub > Edit Config > add the entry shown in this respository.)

Moteino 1: **RFM69Pi2Serial**. RFM69Pi receiver to serial. I used the RFM69Pi firmware sketch and modified the serial baud from 38400 to 115200.<br>
Moteino 2: **Serial2LoRa**. Serial to LoRa. I used the rf95_client example in the RadioHead Examples folder and changed the outbound "Hello World" in the example to the serial input.<br>
Moteino 3: **RF95LoRa2Pi**. LoRa to Pi gateay. I used the RFM69Pi firmware sketch again, but replaced the JeeLib radio library with the RH library.<br>

![IMG_0872](https://user-images.githubusercontent.com/17953028/217689758-0bbb0e3f-32e4-415f-87c6-c0fdf89cda81.JPG)

![IMG_0870](https://user-images.githubusercontent.com/17953028/217689912-de2c6df8-d6a1-4eed-b354-edddaba1ba13.JPG)

![IMG_0891](https://user-images.githubusercontent.com/17953028/217689802-77bba691-d4d8-477e-b506-1325b928bce0.JPG)

![IMG_0896](https://user-images.githubusercontent.com/17953028/217690143-d9bf8a8d-3ef3-4cd5-b302-2d13efe9e673.JPG)

