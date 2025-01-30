// Module..: BLDC.C
// Version.: 1.0
// Compiler: GCC-ARM
// Chip....: STM32F103xx
// Date....: January 2025
//-----------------------------------------------------------------------------

const int pwm_res = 64000000 / 2 / PWM_FREQ; // = 2000

const u8 hall_to_pos[8] =
{
  0, 0, 2, 1, 4, 5, 3, 0
};
//-----------------------------------------------------------------

static volatile int posl = 0;
static volatile int posr = 0;
volatile int pwml = 0;
volatile int pwmr = 0;
volatile int weakl = 0;
volatile int weakr = 0;

static int offsetcount = 0;
static int offsetrl1 = 2000;
static int offsetrl2 = 2000;
static int offsetrr1 = 2000;
static int offsetrr2 = 2000;
static int offsetdcl = 2000;
static int offsetdcr = 2000;

u32 buzzer_freq = 0;
u32 buzzer_pattern = 0;
static u32 buzzer_timer = 0;
u8 enable = 0;

static int curl = 0;
int timer = 0;
float batteryVoltage = BAT_NUMBER_OF_CELLS * 4.0f;
//-----------------------------------------------------------------

void block_pwm(int pwm, int pos, int* u, int* v, int* w)
{
  switch (pos)
  {
    case 0:
      *u = 0;
      *v = pwm;
      *w = -pwm;
    break;
    case 1:
      *u = -pwm;
      *v = pwm;
      *w = 0;
    break;
    case 2:
      *u = -pwm;
      *v = 0;
      *w = pwm;
     break;
    case 3:
      *u = 0;
      *v = -pwm;
      *w = pwm;
    break;
    case 4:
      *u = pwm;
      *v = -pwm;
      *w = 0;
    break;
    case 5:
      *u = pwm;
      *v = 0;
      *w = -pwm;
    break;
    default:
      *u = 0;
      *v = 0;
      *w = 0;
    break;
  }
}
//-----------------------------------------------------------------

void block_phase_current(int pos, int u, int v, int* q)
{
  switch (pos)
  {
    case 0:
      *q = u - v;
    break;
    case 1:
      *q = u;
    break;
    case 2:
      *q = u;
    break;
    case 3:
      *q = v;
    break;
    case 4:
      *q = v;
    break;
    case 5:
      *q = -(u - v);
    break;
    default:
      *q = 0;
    break;
  }
}
//-----------------------------------------------------------------

// Scan 8 channels with 2ADCs @ 20 clk cycles per sample meaning ~80 ADC
// clock cycles @ 8MHz until new DMA interrupt =~ 100KHz = 640 cpu cycles
void DMA1_Channel1_IRQHandler(void)
{
  DMA1->IFCR = DMA_IFCR_CTCIF1;

  if (offsetcount < 1000) // Calibrate ADC offsets
  {
    offsetcount++;
    offsetrl1 = (adc_buffer.rl1 + offsetrl1) / 2;
    offsetrl2 = (adc_buffer.rl2 + offsetrl2) / 2;
    offsetrr1 = (adc_buffer.rr1 + offsetrr1) / 2;
    offsetrr2 = (adc_buffer.rr2 + offsetrr2) / 2;
    offsetdcl = (adc_buffer.dcl + offsetdcl) / 2;
    offsetdcr = (adc_buffer.dcr + offsetdcr) / 2;
    return;
  }

  if (buzzer_timer % 1000 == 0) // Because you get float rounding errors if it would run every time
  {
    batteryVoltage = batteryVoltage * 0.99f + ((float)adc_buffer.batt1 * ((float)BAT_CALIB_REAL_VOLTAGE / (float)BAT_CALIB_ADC)) * 0.01f;
  }

  // Disable PWM when current limit is reached (current chopping)
  if (ABS((adc_buffer.dcl - offsetdcl) * MOTOR_AMP_CONV_DC_AMP) > DC_CUR_LIMIT || timeout > TIMEOUT || enable == 0)
  {
    LEFT_TIM->BDTR &= ~TIM_BDTR_MOE;
  }
  else
  {
    LEFT_TIM->BDTR |= TIM_BDTR_MOE;
  }

  if (ABS((adc_buffer.dcr - offsetdcr) * MOTOR_AMP_CONV_DC_AMP)  > DC_CUR_LIMIT || timeout > TIMEOUT || enable == 0)
  {
    RIGHT_TIM->BDTR &= ~TIM_BDTR_MOE;
  }
  else
  {
    RIGHT_TIM->BDTR |= TIM_BDTR_MOE;
  }

  int ul, vl, wl, ur, vr, wr;

  // Determine next position based on hall sensors
  u8 hall_ul = !(LEFT_HALL_U_PORT->IDR & LEFT_HALL_U_PIN);
  u8 hall_vl = !(LEFT_HALL_V_PORT->IDR & LEFT_HALL_V_PIN);
  u8 hall_wl = !(LEFT_HALL_W_PORT->IDR & LEFT_HALL_W_PIN);

  u8 hall_ur = !(RIGHT_HALL_U_PORT->IDR & RIGHT_HALL_U_PIN);
  u8 hall_vr = !(RIGHT_HALL_V_PORT->IDR & RIGHT_HALL_V_PIN);
  u8 hall_wr = !(RIGHT_HALL_W_PORT->IDR & RIGHT_HALL_W_PIN);

  u8 halll = hall_ul * 1 + hall_vl * 2 + hall_wl * 4;
  posl = hall_to_pos[halll];
  posl += 2;
  posl %= 6;

  u8 hallr = hall_ur * 1 + hall_vr * 2 + hall_wr * 4;
  posr = hall_to_pos[hallr];
  posr += 2;
  posr %= 6;

  block_phase_current(posl, adc_buffer.rl1 - offsetrl1, adc_buffer.rl2 - offsetrl2, &curl);
  buzzer_timer++; // Create square wave for buzzer

  if (buzzer_freq != 0 && (buzzer_timer / 5000) % (buzzer_pattern + 1) == 0)
  {
    if (buzzer_timer % buzzer_freq == 0)
    {
      GPIOA_4_TGL();
    }
  }
  else
  {
    GPIOA_4_CLR();
  }

  // Update PWM channels based on position
  block_pwm(pwml, posl, &ul, &vl, &wl);
  block_pwm(pwmr, posr, &ur, &vr, &wr);

  int weakul, weakvl, weakwl;

  if (pwml > 0)
  {
    block_pwm(weakl, (posl + 5) % 6, &weakul, &weakvl, &weakwl);
  }
  else
  {
    block_pwm(-weakl, (posl+1) % 6, &weakul, &weakvl, &weakwl);
  }

  ul += weakul;
  vl += weakvl;
  wl += weakwl;

  int weakur, weakvr, weakwr;

  if (pwmr > 0)
  {
    block_pwm(weakr, (posr+5) % 6, &weakur, &weakvr, &weakwr);
  }
  else
  {
    block_pwm(-weakr, (posr+1) % 6, &weakur, &weakvr, &weakwr);
  }

  ur += weakur;
  vr += weakvr;
  wr += weakwr;

  LEFT_TIM->LEFT_TIM_U = LIMIT(ul + pwm_res / 2, 10, pwm_res-10);
  LEFT_TIM->LEFT_TIM_V = LIMIT(vl + pwm_res / 2, 10, pwm_res-10);
  LEFT_TIM->LEFT_TIM_W = LIMIT(wl + pwm_res / 2, 10, pwm_res-10);

  RIGHT_TIM->RIGHT_TIM_U = LIMIT(ur + pwm_res / 2, 10, pwm_res-10);
  RIGHT_TIM->RIGHT_TIM_V = LIMIT(vr + pwm_res / 2, 10, pwm_res-10);
  RIGHT_TIM->RIGHT_TIM_W = LIMIT(wr + pwm_res / 2, 10, pwm_res-10);
}
