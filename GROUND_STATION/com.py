import serial

BOARD_COM = "COM13"

try:
    board = serial.Serial(port = BOARD_COM, baudrate=115200, timeout = 1)
except:
    board = None
    raise RuntimeError("timeout on ground station connection")


def readline() -> str:
    return board.readline()