#include "RB3203_i2c-periphery.hpp"

i2cPeriphery::i2cPeriphery(gpio_num_t sda,gpio_num_t scl)
{
    i2c_config_t cfg = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sda,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_io_num = scl,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
    };
    cfg.master.clk_speed = 100000; // 100kHz

    esp_err_t err = i2c_param_config(I2C_NUM_0, &cfg);
    ESP_ERROR_CHECK(err);

    err = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
    ESP_ERROR_CHECK(err);
}

int i2cPeriphery::readAcceleration(int8_t axis, int adres)
{
    uint8_t data[2];

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (adres << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 59+2*axis, true);

    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, portMAX_DELAY);
    i2c_cmd_link_delete(cmd);

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x01 << 1) | I2C_MASTER_READ, true); // Čtení z adresy 0x1

    i2c_master_read_byte(cmd, &data[1], I2C_MASTER_ACK); // přečtení jednoho bytu, odešle se odezva ACK - úspěšně přečteno

    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, portMAX_DELAY);
    i2c_cmd_link_delete(cmd);


    cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (adres << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 60+2*axis, true);

    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, portMAX_DELAY);
    i2c_cmd_link_delete(cmd);

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x01 << 1) | I2C_MASTER_READ, true); // Čtení z adresy 0x1

    i2c_master_read_byte(cmd, &data[1], I2C_MASTER_ACK); // přečtení jednoho bytu, odešle se odezva ACK - úspěšně přečteno
    
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, portMAX_DELAY);
    i2c_cmd_link_delete(cmd);

    return (data[0]<<8)+data[1];
}