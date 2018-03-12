void Write_24LCxx(unsigned char control,unsigned int adress, unsigned char databyte){
    I2C_Start();
    I2C_Wr(control);   //0xA0,0xA1, 0xA2,
    I2C_Wr((adress&0xFF00)>>8);
    I2C_Wr(adress &0x00FF);
    I2C_Wr(databyte);
    I2C_Stop();
    __delay_ms(10);
}


unsigned char Read_24LCxx(unsigned char control,unsigned int adress){
     unsigned char  EEPROM_Read;
    I2C_Start();
    I2C_Wr(control);
    I2C_Wr((adress&0xFF00)>>8);
    I2C_Wr(adress &0x00FF);
    I2C_Repeated_Start();
    I2C_Wr(0xA1);
    EEPROM_Read =I2CReadbyte();
    I2C_Stop();
    return EEPROM_Read;
}