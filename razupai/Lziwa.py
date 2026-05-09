from gpiozero import PWMLED
from time import sleep

led = PWMLED(18)

while True:
	for i in range(100):
		led.value = i / 100.0
		sleep(0.01)

	for i in range(100, 0, -1):
		led.value = i / 100.0
		sleep(0.01)


