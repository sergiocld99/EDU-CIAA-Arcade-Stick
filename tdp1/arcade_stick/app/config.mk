# Compile options

VERBOSE=n
OPT=g
USE_NANO=y
SEMIHOST=n
USE_FPU=y

# Otros directorios
DRIVER_DIR = tdp1/arcade_stick/driver

INCLUDES += -I$(DRIVER_DIR)/inc
SRC += $(wildcard $(DRIVER_DIR)/src/*.c)
