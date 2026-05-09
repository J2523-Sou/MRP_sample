from gpiozero import PWMLED
from time import sleep

led = PWMLED(21)
blue = PWMLED(19)
green = PWMLED(20)

while True:
	for i in range(101):
		led.value = i / 100
		o = 100 - i
		blue.value = o / 100
		sleep(0.01)
	for i in range(101):
		blue.value = i / 100
		o = 100 - i
		green.value = o / 100
		sleep(0.01)
	for i in range(101):
		green.value = 1 / 100
		o = 100 - i
		led.value = o / 100
		sleep(0.01)

