# Lab 6 — OpenCV Video Processing

## Опис проєкту
Ця лабораторна робота реалізує програму для обробки відео з камери в реальному часі з використанням бібліотеки OpenCV.  
Користувач може перемикати різні режими обробки зображення та змінювати параметри через інтерактивні елементи.

---

## Функціонал
- Отримання відео з камери
- Обробка кадрів у реальному часі
- Перемикання режимів обробки через клавіатуру
- Інтерактивний trackbar для параметра blur

---

## Режими (клавіші)

- `1` — Original
- `2` — Grayscale
- `3` — Gaussian Blur
- `4` — Canny Edge Detection
- `5` — Invert Colors
- `6` — Sobel Filter
- `7` — Threshold Binarization
- `ESC` — вихід

---

## Структура проєкту
include/
├── CameraProvider.hpp
├── FrameProcessor.hpp
├── KeyProcessor.hpp
├── Display.hpp

src/
├── main.cpp
├── CameraProvider.cpp
├── FrameProcessor.cpp
├── KeyProcessor.cpp
├── Display.cpp

CMakeLists.txt
build.sh
run.sh
preinstall.sh
.gitignore
README.md


---

## Вимоги до системи

### Операційна система:
- Linux (Ubuntu 20.04+)

### Залежності:
- OpenCV 4.x
- CMake >= 3.10
- GCC / G++

### Рекомендоване залізо:
- CPU: Intel i3 / Ryzen 3 або вище
- RAM: 4 GB+
- Веб-камера (або віртуальний пристрій)

---

## Запуск проєкту

### 1. Встановлення залежностей
chmod +x preinstall.sh
./preinstall.sh
### 2. Збірка
chmod +x build.sh
./build.sh
### 3. Запуск
chmod +x run.sh
./run.sh
