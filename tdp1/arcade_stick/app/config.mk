# Compile options

VERBOSE=n
OPT=g
USE_NANO=y
SEMIHOST=n
USE_FPU=y

# Libraries
# Se agrego USE_FREERTOS

USE_LPCOPEN=y
USE_SAPI=y
USE_FREERTOS=y
FREERTOS_HEAP_TYPE=4
LOAD_INRAM=n

# Otros directorios
DRIVER_DIR = tdp1/arcade_stick/driver

INCLUDES += -I$(DRIVER_DIR)/inc
SRC += $(wildcard $(DRIVER_DIR)/src/*.c)
