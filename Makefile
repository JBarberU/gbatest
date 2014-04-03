SRC_DIR=src
SRC=test.c
TARGET_NAME=test
BIN_DIR=build

$TARGET_NAME: 
	mkdir -p $(BIN_DIR)
	arm-none-eabi-gcc -mthumb -mthumb-interwork -c $(SRC_DIR)/$(SRC) -o $(BIN_DIR)/$(TARGET_NAME).o
	arm-none-eabi-gcc -specs=gba.specs -mthumb-interwork $(BIN_DIR)/$(TARGET_NAME).o -o $(BIN_DIR)/$(TARGET_NAME).elf
	arm-none-eabi-objcopy -O binary $(BIN_DIR)/$(TARGET_NAME).elf $(BIN_DIR)/$(TARGET_NAME).gba
	gbafix $(BIN_DIR)/$(TARGET_NAME).gba

run:
	VisualBoyAdvance $(BIN_DIR)/$(TARGET_NAME).gba

clean:
	rm -r build
