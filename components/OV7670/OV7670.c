#include "OV7670.h"

esp_err_t ov7670_init()
{
    printf("%s\n", "init");

    gpio_set_level(1, GPIO_NUM_15);
    gpio_set_level(0, GPIO_NUM_15); 

    esp_err_t err;
    i2c_cmd_handle_t cmd;
    i2c_config_t i2c_conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA,
        .scl_io_num = I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 24000000,
    };
    err = i2c_param_config(I2C_NUM_0, &i2c_conf);
	if (err != ESP_OK)
        return (ESP_FAIL);

    err = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    if (err != ESP_OK)
        return (ESP_FAIL);

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    err = i2c_master_write_byte(cmd, (OV7670_ADDR_WRITE  << 1) | 1, true);
    if (err != ESP_OK)
    {
        return (ESP_FAIL);
    }

    err = i2c_master_write_byte(cmd, 0x11, 0x01);
    if (err != ESP_OK)
    {
        printf("%s\n", "can't write register");
        return (ESP_FAIL);
    }
   /*  i2c_master_write_byte(cmd, 0x12, 0x00);
    i2c_master_write_byte(cmd, 0x0C, 0x00);
    i2c_master_write_byte(cmd, 0x03E, 0x00);
    i2c_master_write_byte(cmd, 0x70, 0x3A);
    i2c_master_write_byte(cmd, 0x71, 0x35);
    i2c_master_write_byte(cmd, 0x72, 0x11);
    i2c_master_write_byte(cmd, 0x73, 0xF0);
    i2c_master_write_byte(cmd, 0xA2, 0x02); */
     // DBVl clock scale

    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 10 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (err != ESP_OK)
        return (ESP_FAIL); 

    return (ESP_OK);
}

esp_err_t ov7670_read()
{
    printf("%s\n", "read");
    esp_err_t err;
    i2c_cmd_handle_t cmd;
    cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (OV7670_ADDR_READ), true);
    i2c_master_write_byte(cmd, 0xA, 0x1);
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (err != ESP_OK) {
        return err;
    }

    uint8_t result[42];
    memset(result, 0, 42);

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (OV7670_ADDR_READ), true);
    i2c_master_read(cmd, result, 42, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    err = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (err != ESP_OK)
    {
        printf("%s\n", "can't write read bit");
        return (ESP_FAIL);
    }

    for(int i = 0; i < 42; i++)
    {
        printf("%d\n", result[i]);
    }
    printf("%s\n", "read end");
    uint8_t buff[1024];
    memset(buff, 0, 1024);

    for(int i = 0; i < 1024; i++)
    {
        //printf("%d\n", buff[i]);
    }

    return (ESP_OK);
}

