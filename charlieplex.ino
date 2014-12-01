
static const uint8_t mux[6][2] = {
 {0,1},
 {1,0},
 {2,1},
 {1,2},
 {0,2},
 {2,0},
};

void off()
{
  DDRB = 0;
  PORTB = 0;
}

void on(int n)
{
  int plus = mux[n][0];
  int gnd = mux[n][1];
  
  // turn both to output
  DDRB = (1 << plus) | (1 << gnd);
  // and drive gnd to 0, plus to high
  PORTB = (1 << plus);
}

static uint8_t fb[6];

void setup()
{
  off();
}


void draw()
{
  for(int i = 0 ; i < 256 ; i++)
  {
    for (int j = 0 ; j < 6 ; j++)
    {
      if (fb[j] > i)
        on(j);
      else
        off();
    }
  }
}

void loop()
{
  for(int i = 0 ; i < 6; i++)
  {
    for (int b = 0 ; b < 128 ; b++)
    {
      fb[i] = b;
      draw();
    }
    for (int b = 128 ; b >= 0 ; b--)
    {
      fb[i] = b;
      draw();
    }
  }
}
