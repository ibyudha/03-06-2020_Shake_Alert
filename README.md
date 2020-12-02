# 03-06-2020_ShakeAlert
Mini project that uses 2 Arduino (Uno &amp; Mega), several supporting sensors, and nrf24l01 module.

Konfigurasi Pemasangan PIN

Transmitter (Arduino Nano)
•	Sersor Gempa:	DO ==> D3
			GND ==> G
			VCC ==> V
•	LedHijau:	Positif ==> D5
•	LedMerah:	Positif ==> D6
•	nRF24L01:	CE ==> D7
			CSN ==> D8
			SCK ==> D13
			MO ==> D11
			MI ==> D12

Reciever (Arduino Mega)
•	Buzzer:		Positif ==> 11
•	LED:		Positif ==> 12
•	ButtonON:	Sinyal ==> 10
•	ButtonOFF:	Sinyal ==> 9
•	LCD:		SDA ==> SDA
			SCL ==> SCL
			+ ==> V
			- ==> G
•	nRF24L01:	CE ==> 7
			CSN ==> 8
			SCK ==> 52
			MO ==> 51
			MI ==> 50
