/** \file
 * Charlieplex demo.
 *
 * This sketch uses Charlieplexing with the three digital output pins
 * on the Adafruit GEMA to drive six LEDs with PWM.
 *
 * More info: https://trmm.net/Charlieplex
 */


#define NUM_LEDS 6 // Maximum with 3 output pins

#define CHARLIE(pin_vcc, pin_gnd) \
	{ 1 << (pin_vcc), 1 << (pin_gnd) }

static const uint8_t mux[NUM_LEDS][2] = {
	CHARLIE(0,1),
	CHARLIE(1,0),
	CHARLIE(2,1),
	CHARLIE(1,2),
	CHARLIE(0,2),
	CHARLIE(2,0),
};

void off()
{
	DDRB = 0;
	PORTB = 0;
}

void on(int n)
{
	uint8_t vcc = mux[n][0];
	uint8_t gnd = mux[n][1];
  
	// turn both to output
	PORTB = 0;
	DDRB = vcc | gnd;
	PORTB = vcc;
}

static uint8_t fb[NUM_LEDS];

void setup()
{
  off();
}


void draw()
{
	for(uint8_t i = 0 ; i < 255 ; i++)
	{
		for (uint8_t j = 0 ; j < NUM_LEDS ; j++)
		{
			if (fb[j] > i)
				on(j);
			else
				off();
		}
	}
}


static void
decay(
	const uint8_t speed
)
{
	for(int i = 0 ; i < NUM_LEDS ; i++)
	{
		if (fb[i] > speed)
			fb[i] -= speed;
		else
			fb[i] = 0;
	}
}


void loop()
{
	for(int i = 0 ; i < NUM_LEDS; i++)
	{
		for(int delay = 0 ; delay < 50 ; delay++)
		{
			if (fb[i] < 200)
				fb[i] += 4;
			draw();
			decay(1);
		}
	}
}
