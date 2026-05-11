# Lab 7 — Computer Vision & Multithreading (OpenCV DNN)

## Мета роботи
Реалізація системи обробки відеопотоку з камери з використанням OpenCV та багатопоточності.
Основна мета — винести важкі обчислення (детекцію обличчя) в окремий потік, щоб не блокувати UI.


## Архітектура проєкту

Проєкт складається з таких модулів:

### CameraProvider
Відповідає за захоплення кадрів з камери через `cv::VideoCapture`.

### FrameProcessor
Обробка зображення:
- Blur
- Grayscale
- Canny
- Sobel
- Invert
- Threshold
- Brightness (через trackbar)

### KeyProcessor
Обробка натиснутих клавіш і перемикання режимів фільтрів.

### FaceDetector (Multithreading module)
- Використовує `std::thread`
- Виконує нейромережеву детекцію облич (OpenCV DNN)
- Працює у фоновому потоці
- Використовує `std::mutex` для захисту даних
- Використовує `std::atomic<bool>` для завершення потоку

### Main thread (UI)
- Отримує кадри з камери
- Передає кадр у FaceDetector
- Отримує координати облич
- Малює bounding boxes
- Відображає відео (`cv::imshow`)
- Відображає FPS

## Використані технології
- C++
- OpenCV (video processing + DNN)
- CMake
- std::thread (multithreading)
- std::mutex (synchronization)
- std::atomic (thread control)

  

## Встановлення залежностей

### Linux:
bash

./preinstall.sh

## Збірка проєкту
mkdir build

cd build

cmake ..

make

## Запуск
./app
