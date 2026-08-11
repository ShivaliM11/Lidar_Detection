#include <stdint.h>
#include "./include/pwm.h"
#include "./include/io_peripherals.h"

void pwm_setup(int pwm_range, struct io_peripherals *io)
{
    // Set PWM range to control output resolution
    io->pwm->RNG1 = pwm_range;
    io->pwm->RNG2 = pwm_range;

    // Start with a minimal PWM duty cycle
    io->pwm->DAT1 = 1;
    io->pwm->DAT2 = 1;

    // Configure PWM channels for mark-space mode
    io->pwm->CTL.field.MODE1 = 0;
    io->pwm->CTL.field.MODE2 = 0;

    // Repeat last PWM value each cycle
    io->pwm->CTL.field.RPTL1 = 1;
    io->pwm->CTL.field.RPTL2 = 1;

    // Keep PWM outputs in normal active state
    io->pwm->CTL.field.SBIT1 = 0;
    io->pwm->CTL.field.SBIT2 = 0;
    io->pwm->CTL.field.POLA1 = 0;
    io->pwm->CTL.field.POLA2 = 0;

    // Use hardware PWM instead of FIFO-based control
    io->pwm->CTL.field.USEF1 = 0;
    io->pwm->CTL.field.USEF2 = 0;

    // Enable mark-space mode for direct duty-cycle control
    io->pwm->CTL.field.MSEN1 = 1;
    io->pwm->CTL.field.MSEN2 = 1;

    // Clear PWM FIFO before enabling outputs
    io->pwm->CTL.field.CLRF1 = 1;

    // Enable both PWM channels
    io->pwm->CTL.field.PWEN1 = 1;
    io->pwm->CTL.field.PWEN2 = 1;
}
