void set_YM3812_def()
{
	WriteDataBus(0,0,0x20);
	WriteDataBus(0,1,0x01);
	WriteDataBus(0,0,0x40);
	WriteDataBus(0,1,0x10);
	WriteDataBus(0,0,0x60);
	WriteDataBus(0,1,0xF0);
	WriteDataBus(0,0,0x80);
	WriteDataBus(0,1,0x77);
	WriteDataBus(0,0,0xA0);
	WriteDataBus(0,1,0x98);

	WriteDataBus(0,0,0x23);
	WriteDataBus(0,1,0x01);
	WriteDataBus(0,0,0x43);
	WriteDataBus(0,1,0x00);
	WriteDataBus(0,0,0x63);
	WriteDataBus(0,1,0xF0);
	WriteDataBus(0,0,0x83);
	WriteDataBus(0,1,0x77);
	WriteDataBus(0,0,0xB0);
	WriteDataBus(0,1,0x31);

}
