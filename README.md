# Desktop usb hid control

As my old keyboard did not have any multimedia control , each time i was playing i could not play/pause or even rise up the music volume.
So i decided to make a box with some basic hid functions , at first i though of making a library but doing some research about how to do it i found a wonderfull arduino library:
>https://github.com/NicoHood/HID

it fitted almost all my needs, and the ones that didn't like muting discord where achive by making some macros with the pro-micro keyboard capabilities:
>https://www.sparkfun.com/products/12640
>

![alt text](https://cdn.sparkfun.com//assets/parts/9/3/2/6/12640-01a.jpg)

BEWARE!!! THERE ARE TWO MODELS THE 5V AND THE 3.3V NOT SELECTING THE CORRECT MODEL IN ARDUINO IDE WILL BRICK YOUR PRO-MICRO,IT CAN BE RECOVERED AS SHOWN IN HERE(this happened to me so please be carefull):
>https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/troubleshooting-and-faq
>

You'll have to install NicoHood's library and add to the arduino ide the .json , you'll find it in here:
>https://github.com/sparkfun/Arduino_Boards
>
For the time being this is the .json, be aware that it could change, in case it does not work refer to the upper link.
>https://raw.githubusercontent.com/sparkfun/Arduino_Boards/master/IDE_Board_Manager/package_sparkfun_index.json
>

About minimal to be used items

- Rotatory encoder(volume control)
- Five push buttons for hid
- Push button (different from the hid ones) , to move between the 3 profiles
- Two leds to show the profile(no ligh-profile 0 , one-profile 1,two-profile 2)

my full set up
 - All above
 - Another push button to turn on/off the pc
 - Two 6 pin connectors(two pins for powering on/off & four for usb )
  
       ![alt text](https://i.ebayimg.com/images/i/182071474659-0-0/s-l140/p.jpg)
 
 
 - Two meters of 6 core cable (depending on your mobo on/off pins if they work by grounding you could make it with just five core and 5       pins connectors)
 
       ![alt text](https://i.ebayimg.com/images/i/301725499558-0-0/s-l140/p.jpg)
 
 - Motherboard usb conector
 - Blank backplate from pc box expanding ports
 
 
