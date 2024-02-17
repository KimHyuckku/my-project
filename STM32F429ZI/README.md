# STM 설치 및 기본설정

https://www.st.com/en/development-tools/stm32cubeide.html#get-software
**[STM32 32-bit Arm Cortex® MCU & MPU](https://www.st.com/ko/stm32/stm32/stm32intro.html)**

STM32 Cube Ide을 windows용으로 다운로드

경로 설정을 모두 한 뒤, File-New-STM32 Project를 누른다


![Untitled](https://github.com/KimHyuckku/my-project/assets/148949177/d611463d-bdfc-40a6-a8d3-1b43e59749ea)
Board Selector에서 나와 맞는 보드를 고른다.
![Untitled (1)](https://github.com/KimHyuckku/my-project/assets/148949177/42c17d2d-5de9-40bd-aef4-90ff4b44dbf1)
![Untitled (2)](https://github.com/KimHyuckku/my-project/assets/148949177/6b959954-79b9-4660-9bc3-b14d3fbd18f9)
설치 및 설정 완료


# ComPortMaster 설정

window 우클릭, 장치관리자-포트(Com & LPT)- STMicroelectronics STLink Virtual COM Port(COM3)에서 COM3부분을 확인하고 COM3을 Device 부분에 입력. 숫자가 다를수 있음

![Untitled (3)](https://github.com/KimHyuckku/my-project/assets/148949177/2262f79e-650d-4b57-bd07-70db15a0d0c1)

(연결을 안해서 COM3가 없음)

Baudrate는 지정된 것으로.  설정할 땐 9600으로 했음(STM32에서도 바꾸는 설정)

![Untitled (4)](https://github.com/KimHyuckku/my-project/assets/148949177/7a728abc-3f3d-441f-8191-8d2656d2ce0f)

코딩에서 실행했을 때 Open port 눌러야 사용 시작


