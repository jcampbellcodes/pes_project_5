#include "uart.h"

void uart_init(int64_t baud_rate)
{
	uint16_t sbr;
	uint8_t temp;

	// Enable clock gating for UART0 and Port A
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;

	// Make sure transmitter and receiver are disabled before init
	UART0->C2 &= ~UART0_C2_TE_MASK & ~UART0_C2_RE_MASK;

	// Set UART clock to 48 MHz clock
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	// Set pins to UART0 Rx and Tx
	PORTA->PCR[1] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Rx
	PORTA->PCR[2] = PORT_PCR_ISF_MASK | PORT_PCR_MUX(2); // Tx

	// Set baud rate and oversampling ratio
	sbr = (uint16_t)((SYS_CLOCK)/(baud_rate * UART_OVERSAMPLE_RATE));
	UART0->BDH &= ~UART0_BDH_SBR_MASK;
	UART0->BDH |= UART0_BDH_SBR(sbr>>8);
	UART0->BDL = UART0_BDL_SBR(sbr);
	UART0->C4 |= UART0_C4_OSR(UART_OVERSAMPLE_RATE-1);

	// Disable interrupts for RX active edge and LIN break detect, select one stop bit
	UART0->BDH |= UART0_BDH_RXEDGIE(0) | UART0_BDH_SBNS(0) | UART0_BDH_LBKDIE(0);

	// Don't enable loopback mode, use 8 data bit mode, don't use parity
	UART0->C1 = UART0_C1_LOOPS(0) | UART0_C1_M(0) | UART0_C1_PE(0);
	// Don't invert transmit data, don't enable interrupts for errors
	UART0->C3 = UART0_C3_TXINV(0) | UART0_C3_ORIE(0)| UART0_C3_NEIE(0)
			| UART0_C3_FEIE(0) | UART0_C3_PEIE(0);

	// Clear error flags
	UART0->S1 = UART0_S1_OR(1) | UART0_S1_NF(1) | UART0_S1_FE(1) | UART0_S1_PF(1);

	// Try it a different way
	UART0->S1 |= UART0_S1_OR_MASK | UART0_S1_NF_MASK |
									UART0_S1_FE_MASK | UART0_S1_PF_MASK;

	// Send LSB first, do not invert received data
	UART0->S2 = UART0_S2_MSBF(0) | UART0_S2_RXINV(0);

#if USE_UART_INTERRUPTS
	// Enable interrupts. Listing 8.11 on p. 234
	Q_Init(&TxQ);
	Q_Init(&RxQ);

	NVIC_SetPriority(UART0_IRQn, 2); // 0, 1, 2, or 3
	NVIC_ClearPendingIRQ(UART0_IRQn);
	NVIC_EnableIRQ(UART0_IRQn);

	// Enable receive interrupts but not transmit interrupts yet
	UART0->C2 |= UART_C2_RIE(1);
#endif

	// Enable UART receiver and transmitter
	UART0->C2 |= UART0_C2_RE(1) | UART0_C2_TE(1);

	// Clear the UART RDRF flag
	temp = UART0->D;
	UART0->S1 &= ~UART0_S1_RDRF_MASK;

}

char uart_getchar()
{
      /* Wait until character has been received */
      while (!(UART0->S1 & UART0_S1_RDRF_MASK));

      /* Return the 8-bit data from the receiver */
      return UART0->D;
}

bool uart_putchar_space_available ()
{
    return (UART0->S1 & UART0_S1_TDRE_MASK);
}

bool uart_getchar_present ()
{
    return (UART0->S1 & UART0_S1_RDRF_MASK);
}

void uart_putchar (char ch)
{
      /* Wait until space is available in the FIFO */
      while(!(UART0->S1 & UART0_S1_TDRE_MASK));

      /* Send the character */
      UART0->D = (uint8_t)ch;

}

// taken from DEAN
void uart_put_string(const char* str) {
	// enqueue string
	while (*str != '\0') { // Send characters up to null terminator
		uart_putchar(*str++);
	}
}

void uart_echo()
{
	while(1)
	{
		uint8_t ch = uart_getchar();
		uart_putchar(ch);
	}
}

/********************************************************************/
//#if UART_MODE == INTERRUPT
//void UART0_IRQHandler (void)
//{
//  char c = 0;
//  if (UART0->S1 & UART_S1_RDRF_MASK)
//  {
//    c = UART0->D;
//
//    if ((UART0->S1 &UART_S1_TDRE_MASK) || (UART0->S1 & UART_S1_TC_MASK))
//    {
//    	UART0->D  = c;
//    }
//  }
//}
//#endif

