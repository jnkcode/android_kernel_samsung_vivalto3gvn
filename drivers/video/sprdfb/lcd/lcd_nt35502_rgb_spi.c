/*
 * Copyright (C) 2014 Samsung
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/delay.h>
#include "../sprdfb_panel.h"
#ifdef CONFIG_LCD_ESD_RECOVERY
#include "../esd_detect.h"
#endif

#define NT35502_SpiWriteCmd(cmd)\
{\
	spi_send_cmd((cmd & 0xFF));\
}

#define  NT35502_SpiWriteData(data)\
{\
	spi_send_data((data & 0xFF));\
}

#ifndef CONFIG_FB_LCD_MULTI_RGB_SPI
unsigned int panel_id = 0x558cc0;	
#endif

static int32_t nt35502_init(struct panel_spec *self)
{
	uint32_t test_data[8] = {0};
	uint32_t left = 0;
	uint32_t top = 0;
	uint32_t right = 480;
	uint32_t bottom = 800;
	uint32_t data = 0;
	spi_send_cmd_t spi_send_cmd = self->info.rgb->bus_info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data = self->info.rgb->bus_info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read;


	pr_info("nt35502_init\n");

	/* Power Setting Sequence */

	NT35502_SpiWriteCmd(0xF0);
	NT35502_SpiWriteData(0x55);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x52);
	NT35502_SpiWriteData(0x08);
	NT35502_SpiWriteData(0x01);
	
	NT35502_SpiWriteCmd(0xB0);
	NT35502_SpiWriteData(0x0A);
	
	NT35502_SpiWriteCmd(0xB2);
	NT35502_SpiWriteData(0x60);
	
	NT35502_SpiWriteCmd(0xB3);
	NT35502_SpiWriteData(0x2B);
	
	NT35502_SpiWriteCmd(0xB4);
	NT35502_SpiWriteData(0x07);
	
	NT35502_SpiWriteCmd(0xB5);
	NT35502_SpiWriteData(0x64);
	
	NT35502_SpiWriteCmd(0xB9);
	NT35502_SpiWriteData(0x46);
	
	NT35502_SpiWriteCmd(0xBA);
	NT35502_SpiWriteData(0x26);
	
	NT35502_SpiWriteCmd(0xBC);
	NT35502_SpiWriteData(0x40);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xBD);
	NT35502_SpiWriteData(0x40);
	NT35502_SpiWriteData(0x00);
	
	/* Gamam Setting Sequence */
	
	NT35502_SpiWriteCmd(0xD1);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x06);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x0B);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x22);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x3E);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x79);
	NT35502_SpiWriteCmd(0xD2);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xAB);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xF7);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x34);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x84);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCD);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCE);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xFB);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x2F);
	NT35502_SpiWriteCmd(0xD3);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x4B);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x6C);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x80);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x99);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xA9);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xBE);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xCC);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xE2);
	NT35502_SpiWriteCmd(0xD4);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x14);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x9F);
	
	NT35502_SpiWriteCmd(0xD5);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x09);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x15);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x34);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x57);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x95);
	NT35502_SpiWriteCmd(0xD6);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xC6);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x0E);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x42);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x8F);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCD);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCE);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xFF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x32);
	NT35502_SpiWriteCmd(0xD7);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x4E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x6E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x82);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x9B);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xAB);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xC0);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xCF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xE5);
	NT35502_SpiWriteCmd(0xD8);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x16);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0xAF);
	
	NT35502_SpiWriteCmd(0xD9);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x07);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x2A);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x4B);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x87);
	NT35502_SpiWriteCmd(0xDD);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xB9);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x38);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x87);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCA);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCB);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xFF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x32);
	NT35502_SpiWriteCmd(0xDE);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x4E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x6E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x82);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x9A);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xBF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xCE);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xE3);
	NT35502_SpiWriteCmd(0xDF);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x13);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x7F);
	
	NT35502_SpiWriteCmd(0xE0);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x06);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x0B);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x22);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x3E);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x79);
	NT35502_SpiWriteCmd(0xE1);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xAB);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xF7);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x34);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x84);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCD);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCE);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xFB);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x2F);
	NT35502_SpiWriteCmd(0xE2);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x4B);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x6C);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x80);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x99);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xA9);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xBE);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xCC);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xE2);
	NT35502_SpiWriteCmd(0xE3);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x14);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x9F);
	
	NT35502_SpiWriteCmd(0xE4);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x09);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x15);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x34);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x57);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x95);
	NT35502_SpiWriteCmd(0xE5);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xC6);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x0E);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x42);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x8F);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCD);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCE);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xFF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x32);
	NT35502_SpiWriteCmd(0xE6);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x4E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x6E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x82);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x9B);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xAB);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xC0);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xCF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xE5);
	NT35502_SpiWriteCmd(0xE7);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x16);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0xAF);
	
	NT35502_SpiWriteCmd(0xE8);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x07);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x2A);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x4B);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x87);
	NT35502_SpiWriteCmd(0xE9);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xB9);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x38);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x87);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCA);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xCB);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0xFF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x32);
	NT35502_SpiWriteCmd(0xEA);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x4E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x6E);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x82);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x9A);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xBF);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xCE);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0xE3);
	NT35502_SpiWriteCmd(0xEB);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x13);
	NT35502_SpiWriteData(0x03);
	NT35502_SpiWriteData(0x7F);

	/* Initializing Sequence */
	
	NT35502_SpiWriteCmd(0xF0);
	NT35502_SpiWriteData(0x55);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x52);
	NT35502_SpiWriteData(0x08);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xB1);
	NT35502_SpiWriteData(0x06);
	NT35502_SpiWriteData(0x08);
	
	NT35502_SpiWriteCmd(0xB2);
	NT35502_SpiWriteData(0x54);
	NT35502_SpiWriteData(0x11);
	
	NT35502_SpiWriteCmd(0xB3);
	NT35502_SpiWriteData(0x20);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xB4);
	NT35502_SpiWriteData(0x09);
	NT35502_SpiWriteData(0x50);
	
	NT35502_SpiWriteCmd(0xB6);
	NT35502_SpiWriteData(0x0B);
	
	NT35502_SpiWriteCmd(0xB7);
	NT35502_SpiWriteData(0x2C);
	NT35502_SpiWriteData(0x2C);
	
	NT35502_SpiWriteCmd(0xB8);
	NT35502_SpiWriteData(0x20);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xBB);
	NT35502_SpiWriteData(0xF2);
	NT35502_SpiWriteData(0xF5);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xBC);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xC9);
	NT35502_SpiWriteData(0xC0);
	NT35502_SpiWriteData(0x82);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0xA0);
	NT35502_SpiWriteData(0xA0);
	NT35502_SpiWriteData(0x80);
	NT35502_SpiWriteData(0xC3);
	NT35502_SpiWriteData(0x47);
	NT35502_SpiWriteData(0x43);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xEC);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x04);
	NT35502_SpiWriteData(0x0F);
	NT35502_SpiWriteData(0x05);
	NT35502_SpiWriteData(0x07);
	NT35502_SpiWriteData(0x09);
	NT35502_SpiWriteData(0x0B);
	NT35502_SpiWriteData(0x0D);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x04);
	NT35502_SpiWriteData(0x05);
	NT35502_SpiWriteData(0x07);
	NT35502_SpiWriteData(0x09);
	NT35502_SpiWriteData(0x0B);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x0D);
	NT35502_SpiWriteData(0x11);
	
	NT35502_SpiWriteCmd(0xED);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x04);
	NT35502_SpiWriteData(0x0F);
	NT35502_SpiWriteData(0x05);
	NT35502_SpiWriteData(0x07);
	NT35502_SpiWriteData(0x09);
	NT35502_SpiWriteData(0x0B);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x10);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x01);
	NT35502_SpiWriteData(0x11);
	NT35502_SpiWriteData(0x05);
	NT35502_SpiWriteData(0x07);
	NT35502_SpiWriteData(0x09);
	NT35502_SpiWriteData(0x0B);
	NT35502_SpiWriteData(0x02);
	NT35502_SpiWriteData(0x0D);
	NT35502_SpiWriteData(0x03);
	
	NT35502_SpiWriteCmd(0xFF);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x55);
	NT35502_SpiWriteData(0x25);
	NT35502_SpiWriteData(0x01);	

	NT35502_SpiWriteCmd(0xFB);
	NT35502_SpiWriteData(0x03);

	NT35502_SpiWriteCmd(0xFF);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x55);
	NT35502_SpiWriteData(0x25);
	NT35502_SpiWriteData(0x00);
	
	NT35502_SpiWriteCmd(0xFF);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x55);
	NT35502_SpiWriteData(0x25);
	NT35502_SpiWriteData(0x01);	

	NT35502_SpiWriteCmd(0x6F);
	NT35502_SpiWriteData(0x1B);

	NT35502_SpiWriteCmd(0xFB);
	NT35502_SpiWriteData(0x2C);

	NT35502_SpiWriteCmd(0xFF);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x55);
	NT35502_SpiWriteData(0x25);
	NT35502_SpiWriteData(0x00);
	
	/* Disable CMD2 */
	NT35502_SpiWriteCmd(0xF0);
	NT35502_SpiWriteData(0x55);
	NT35502_SpiWriteData(0xAA);
	NT35502_SpiWriteData(0x52);
	NT35502_SpiWriteData(0x00);
	NT35502_SpiWriteData(0x00);
		
	/* Dispaly on */	
	NT35502_SpiWriteCmd(0x11);
	msleep(120);
	NT35502_SpiWriteCmd(0x29);
	msleep(70);

	return 0;
}

static int32_t nt35502_enter_sleep(struct panel_spec *self, uint8_t is_sleep)
{
	spi_send_cmd_t spi_send_cmd =
			self->info.rgb->bus_info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data =
			self->info.rgb->bus_info.spi->ops->spi_send_data;

	if (is_sleep) {
		/*Sleep In*/
		NT35502_SpiWriteCmd(0x28);
		usleep_range(20000, 25000);
		NT35502_SpiWriteCmd(0x10);
		msleep(120);
	} else {
		/*Sleep Out*/
		NT35502_SpiWriteCmd(0x11);
		msleep(120);
		NT35502_SpiWriteCmd(0x29);
		usleep_range(30000, 35000);
	}

	return 0;
}

static int32_t nt35502_set_window(struct panel_spec *self,
		uint16_t left, uint16_t top, uint16_t right, uint16_t bottom)
{
	uint32_t *test_data[4] = {0};
	spi_send_cmd_t spi_send_cmd =
			self->info.rgb->bus_info.spi->ops->spi_send_cmd;
	spi_send_data_t spi_send_data =
			self->info.rgb->bus_info.spi->ops->spi_send_data;
	spi_read_t spi_read = self->info.rgb->bus_info.spi->ops->spi_read;

	return 0;
}
static int32_t nt35502_invalidate(struct panel_spec *self)
{
	return self->ops->panel_set_window(self, 0, 0, self->width - 1,
							self->height - 1);
}

static int32_t nt35502_invalidate_rect(struct panel_spec *self,
				uint16_t left, uint16_t top,
				uint16_t right, uint16_t bottom)
{
	return self->ops->panel_set_window(self, left, top, right, bottom);
}

static int32_t nt35502_read_id(struct panel_spec *self)
{
	return 0x558cc0;
}

#ifdef CONFIG_LCD_ESD_RECOVERY
struct esd_det_info nt35502_esd_info = {
	.name = "nt35502",
	.mode = ESD_DET_INTERRUPT,
	.gpio = 86,
	.state = ESD_DET_NOT_INITIALIZED,
	.level = ESD_DET_HIGH,
};
#endif

#ifdef CONFIG_FB_BL_EVENT_CTRL
static int32_t nt35502_backlight_ctrl(struct panel_spec *self, uint16_t bl_on)
{
	if (bl_on)
		fb_bl_notifier_call_chain(FB_BL_EVENT_RESUME, NULL);
	else
		fb_bl_notifier_call_chain(FB_BL_EVENT_SUSPEND, NULL);

	return 0;
}
#endif

static struct panel_operations lcd_nt35502_rgb_spi_operations = {
	.panel_init = nt35502_init,
	.panel_set_window = nt35502_set_window,
	.panel_invalidate_rect = nt35502_invalidate_rect,
	.panel_invalidate = nt35502_invalidate,
	.panel_enter_sleep = nt35502_enter_sleep,
	.panel_readid = nt35502_read_id,
#ifdef CONFIG_FB_BL_EVENT_CTRL
	.panel_set_brightness = nt35502_backlight_ctrl,
#endif
};

static struct timing_rgb lcd_nt35502_rgb_timing = {
	.hfp = 30,
	.hbp = 20,
	.hsync = 20,
	.vfp = 6,
	.vbp = 19,
	.vsync = 4,
};

static struct spi_info lcd_nt35502_rgb_spi_info = {
	.ops = NULL,
};

static struct info_rgb lcd_nt35502_rgb_info = {
	.cmd_bus_mode  = SPRDFB_RGB_BUS_TYPE_SPI,
	.video_bus_width = 24, /*18,16*/
	.h_sync_pol = SPRDFB_POLARITY_NEG,
	.v_sync_pol = SPRDFB_POLARITY_NEG,
	.de_pol = SPRDFB_POLARITY_POS,
	.timing = &lcd_nt35502_rgb_timing,
	.bus_info = {
		.spi = &lcd_nt35502_rgb_spi_info,
	}
};

struct panel_spec lcd_panel_nt35502_rgb_spi_spec = {
	.width = 480,
	.height = 800,
	.width_hw = 52,
	.height_hw = 87,
	.fps = 62,
	.suspend_mode = SEND_SLEEP_CMD,
	.type = LCD_MODE_RGB,
	.direction = LCD_DIRECT_NORMAL,
	.is_clean_lcd = false,
	.info = {
		.rgb = &lcd_nt35502_rgb_info
	},
	.ops = &lcd_nt35502_rgb_spi_operations,
#ifdef CONFIG_LCD_ESD_RECOVERY
	.esd_info = &nt35502_esd_info,
#endif

};

struct panel_cfg lcd_nt35502_rgb_spi_main = {
	/* this panel can only be main lcd */
	.dev_id = SPRDFB_MAINLCD_ID,
	.lcd_id = 0x558cc0,
	.lcd_name = "lcd_nt35502_rgb_spi",
	.panel = &lcd_panel_nt35502_rgb_spi_spec,
};

static int __init lcd_nt35502_rgb_spi_init(void)
{
	sprdfb_panel_register(&lcd_nt35502_rgb_spi_main);
	return 0;
}

subsys_initcall(lcd_nt35502_rgb_spi_init);
