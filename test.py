import serial

serial_port = '/dev/ttyUSB0'  # Zmień na odpowiedni port szeregowy używany przez ESP32
baud_rate = 115200  # Ta sama prędkość transmisji, co w kodzie ESP32

try:
    # Utwórz obiekt do obsługi połączenia szeregowego
    ser = serial.Serial(serial_port, baud_rate)
    print(f"Otwarto port szeregowy {serial_port}.")

    # Oczekiwanie na dane z ESP32 i ich wyświetlanie
    while True:
        if ser.in_waiting > 0:
            received_data = ser.readline().decode().strip()
            print("Otrzymane dane z LoRa:", received_data)

except KeyboardInterrupt:
    # Obsługa przerwania przez użytkownika (Ctrl+C)
    print("Odbieranie danych zakończone")
except serial.SerialException as e:
    # Obsługa błędów połączenia szeregowego
    print(f"Błąd: {e}")
finally:
    # Zamknięcie połączenia szeregowego
    ser.close()
    print("Zamknięto port")