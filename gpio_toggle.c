#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>

#define CHIP_NAME   "gpiochip0"
#define LINE_NUM    63   

int main(void) {
    struct gpiod_chip *chip;
    struct gpiod_line *line;
    int ret;


    chip = gpiod_chip_open_by_name(CHIP_NAME);
    if (!chip) {
        perror("gpiod_chip_open_by_name");
        return 1;
    }

 
    line = gpiod_chip_get_line(chip, LINE_NUM);
    if (!line) {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(chip);
        return 1;
    }

  
    ret = gpiod_line_request_output(line, "led-toggle", 0);
    if (ret < 0) {
        perror("gpiod_line_request_output");
        gpiod_chip_close(chip);
        return 1;
    }


    for (int i = 0; i < 10; i++) {
        gpiod_line_set_value(line, 1);
        printf("LED ON\n");
        sleep(1);

        gpiod_line_set_value(line, 0);
        printf("LED OFF\n");
        sleep(1);
    }


    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return 0;
}
