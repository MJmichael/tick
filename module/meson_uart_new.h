/*
 *  linux/include/linux/serial_8250.h
 *
 *  Copyright (C) 2004 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#ifndef _LINUX_AM_UART_H
#define _LINUX_AM_UART_H
#include <mach/am_regs.h>
#define UART_OVERFLOW_ERR (0x01<<18)
#define UART_FRAME_ERR (0x01<<17)
#define UART_PARITY_ERR (0x01<<16)

#define UART_CLEAR_ERR (0x01<<24)

#define UART_RXENB	       (0x01<<13)
#define UART_RXEMPTY			(0x01<<20)
#define UART_RXFULL			(0x01<<19)
#define UART_TXENB         (0x01<<12)
#define UART_TXEMPTY     (0x01<<22)
#define UART_TXFULL   (0x01<<21)

#define UART_TXRST      (0x01<<22)
#define UART_RXRST      (0x01<<23)
#define UART_RXINT_EN   (0x01<<27)
#define UART_TXINT_EN   (0x01<<28)

#define UART_WFIFO      0
#define UART_RFIFO      1
#define UART_CONTROL    2
#define UART_STATUS     3
#define UART_MISC       4
#define UART_REG5   	5

#define P_UART(uart_base,reg)    	CBUS_REG_ADDR(uart_base+reg)
#define P_UART_WFIFO(uart_base)   	P_UART(uart_base,UART_WFIFO)
#define P_UART_RFIFO(uart_base)   	P_UART(uart_base,UART_RFIFO)

#define P_UART_CONTROL(uart_base)    P_UART(uart_base,UART_CONTROL)
#define UART_CNTL_MASK_BAUD_RATE                (0xfff)
#define UART_CNTL_MASK_TX_EN                    (1<<12)
#define UART_CNTL_MASK_RX_EN                    (1<<13)
#define UART_CNTL_MASK_2WIRE                    (1<<15)
#define UART_CNTL_MASK_STP_BITS                 (3<<16)
#define UART_CNTL_MASK_STP_1BIT                 (0<<16)
#define UART_CNTL_MASK_STP_2BIT                 (1<<16)
#define UART_CNTL_MASK_PRTY_EVEN                (0<<18)
#define UART_CNTL_MASK_PRTY_ODD                 (1<<18)
#define UART_CNTL_MASK_PRTY_TYPE                (1<<18)
#define UART_CNTL_MASK_PRTY_EN                  (1<<19)
#define UART_CNTL_MASK_CHAR_LEN                 (3<<20)
#define UART_CNTL_MASK_CHAR_8BIT                (0<<20)
#define UART_CNTL_MASK_CHAR_7BIT                (1<<20)
#define UART_CNTL_MASK_CHAR_6BIT                (2<<20)
#define UART_CNTL_MASK_CHAR_5BIT                (3<<20)
#define UART_CNTL_MASK_RST_TX                   (1<<22)
#define UART_CNTL_MASK_RST_RX                   (1<<23)
#define UART_CNTL_MASK_CLR_ERR                  (1<<24)
#define UART_CNTL_MASK_INV_RX                   (1<<25)
#define UART_CNTL_MASK_INV_TX                   (1<<26)
#define UART_CNTL_MASK_RINT_EN                  (1<<27)
#define UART_CNTL_MASK_TINT_EN                  (1<<28)
#define UART_CNTL_MASK_INV_CTS                  (1<<29)
#define UART_CNTL_MASK_MASK_ERR                 (1<<30)
#define UART_CNTL_MASK_INV_RTS                  (1<<31)
#define P_UART_STATUS(uart_base)  P_UART(uart_base,UART_STATUS )
#define UART_STAT_MASK_RFIFO_CNT                (0x7f<<0)
#define UART_STAT_MASK_TFIFO_CNT                (0x7f<<8)
#define UART_STAT_MASK_PRTY_ERR                 (1<<16)
#define UART_STAT_MASK_FRAM_ERR                 (1<<17)
#define UART_STAT_MASK_WFULL_ERR                (1<<18)
#define UART_STAT_MASK_RFIFO_FULL               (1<<19)
#define UART_STAT_MASK_RFIFO_EMPTY              (1<<20)
#define UART_STAT_MASK_TFIFO_FULL               (1<<21)
#define UART_STAT_MASK_TFIFO_EMPTY              (1<<22)
#define P_UART_MISC(uart_base)    P_UART(uart_base,UART_MISC   )

typedef struct UART_WRITE_REG{
	uint32_t fifo_wdata:8;
	uint32_t reserved:24;
}uart_write_reg_t;

typedef struct UART_READ_REG{
	uint32_t fifo_rdata:8;
	uint32_t reserved:24;
}uart_read_reg_t;

typedef struct UART_CONTRL_REG{
	uint32_t baud_rate:12;
	uint32_t uart_tx_en:1;
	uint32_t uart_rx_en:1;
	uint32_t reserved:1;
	uint32_t two_wire_en:1;
	uint32_t stop_bit_len:2;
	uint32_t parity_type:1;
	uint32_t parity_en:1;
	uint32_t uart_data_len:2;
	uint32_t uart_tx_rst:1;
	uint32_t uart_rx_rst:1;
	uint32_t uart_clear_err:1;
	uint32_t uart_rx_invert:1;
	uint32_t uart_tx_invert:1;
	uint32_t uart_rx_int_env:1;
	uint32_t uart_tx_int_env:1;
	uint32_t cts_inv:1;
	uint32_t err_mask_en:1;
	uint32_t rts_inv:1;
}uart_contrl_reg_t;

typedef struct UART_STATUS_REG{
	uint32_t rx_fifo_data_count:7;
	uint32_t reserved:1;
	uint32_t tx_fifo_data_count:7;
	uint32_t reserved:1;
	uint32_t parity_err:1;
	uint32_t frame_err:1;
	uint32_t tx_fifo_werr:1;
	uint32_t rx_fifo_full:1;
	uint32_t rx_fifo_empty:1;
	uint32_t tx_fifo_full:1;
	uint32_t tx_fifo_empty:1;
	uint32_t cts_level:1;
	uint32_t recv_fifo_overflow:1;
	uint32_t uart_xmit_busy:1;
	uint32_t uart_recv_busy:1;
	uint32_t reserved:5;
}uart_status_reg_t;

typedef struct UART_INTCTL_REG{
	uint32_t recv_irq_cnt:8;/*uart generates an interrupt when the number bytes in recv fifo is large than the valus*/
	uint32_t xmit_irq_cnt:8;/*uart generates an interrupt when the number bytes in tran fifo is below than the valus*/
	uint32_t rx_fil_sel:3;
	uint32_t rx_fil_tb_sel:1;
	uint32_t baud_rate_ext:4;
	uint32_t cts_fil_sel:3;
	uint32_t cts_fil_tb_sel:1;
	uint32_t async_fifo_en:1;
	uint32_t async_fifo_purge:1;
	uint32_t use_old_rx_baud:1;
	uint32_t reserved:1;
}uart_intctl_reg_t;

typedef struct UART_REG5_REG{
	uint32_t new_baud_rate:23;
	uint32_t use_new_baud_rate:1;
	uint32_t reserved:8;
}uart_reg5_reg_t;

typedef volatile struct{
	volatile uart_write_reg_t wdata;
	volatile uart_read_reg_t rdata;
	volatile uart_contrl_reg_t mode;
	volatile uart_status_reg_t status;
	volatile uart_intctl_reg_t intctl;
	volatile uart_reg5_reg_t reg5;
} am_uart_t;
/*
typedef volatile struct {
  volatile unsigned long wdata;
  volatile unsigned long rdata;
  volatile unsigned long mode;
  volatile unsigned long status;
  volatile unsigned long intctl;
  volatile unsigned long reg5;
} am_uart_t;
*/

#define SERIAL_MAGIC 0x5301

/*
 * This should be used by drivers which want to register
 * their own 8250 ports without registering their own
 * platform device.  Using these will make your driver
 * dependent on the 8250 driver.
 */
struct uart_port;

#endif
