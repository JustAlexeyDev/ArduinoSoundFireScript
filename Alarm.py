import serial
import time
import os
import psutil

ser = serial.Serial('COM3', 9600) 

def play_audio(file_path):
    print(f"Звуковое оповещение: {file_path}")
    os.system(f'start {file_path}')  

def close_audio_app():
    for proc in psutil.process_iter(['pid', 'name']):
        if 'Microsoft.Media.Player.exe' in proc.info['name'] or 'vlc.exe' in proc.info['name']:  # Замените на имя вашего аудиоприложения
            print(f"Ресет системы: {proc.info['name']}")
            proc.kill()

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').rstrip()
        print(f"Причина: {line}")
        if line == "ALARM":
            play_audio('C:/Users/Eva-Desktop/Downloads/04299.mp3')
        elif line == "RESET":
            close_audio_app()
    time.sleep(1)