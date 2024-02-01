# 영상처리 Vision AI


## Visual Studio 설정 image watch 

도구 - 다른창 - image watch로 킬 수 있음. 이미지워치는 디버그 환경 때 사용

## OpenCV

https://opencv.org/releases/ 들어가서 windows용 설치


![image](https://github.com/KimHyuckku/my-project/assets/148949177/41259758-9b0e-4390-be9c-e4b74d402871)

비주얼 스튜디오 들어가서 프로젝트 - 속성창 들어간뒤 구상 속성 - 일반 - 출력 디렉터리에서 위에 $(SolutionDir)Build\$(Platform)로 바꾸고, 대상 이름 마지막에 D를 붙힘(Debug를 뜻함)


![image](https://github.com/KimHyuckku/my-project/assets/148949177/4d9209fd-44b1-48f1-8f9b-d867fa42f894)


그리고 다시 속성창 위 구성 탭에서 디버그를 Release로 바꾼 뒤 똑같이 $(SolutionDir)Build\$(Platform)로 바꾼다 이름은 안바꿈



![image](https://github.com/KimHyuckku/my-project/assets/148949177/eb654dfb-543f-46a9-97f0-1b781824112b)

그 다음 코드를 실행하면 Build파일이 생기고 그 안쪽에 exe파일과 d가 붙은 exe파일이 생겨나는 것을 볼 수 있다.



![image](https://github.com/KimHyuckku/my-project/assets/148949177/9c7bb9cb-db7a-4649-8569-4f21cabdf329)

구성을 모든 구성으로 바꾸고 구성속성-일반-C++언어 표준을 ISO C++20표준으로 바꾸면 최신으로 바꿔준다.



![image](https://github.com/KimHyuckku/my-project/assets/148949177/586309c6-385e-428c-9f89-fc6e13ecc676)

속성페이지 C/C++ 일반- 추가 포함 디렉토리 ../thirdparty/opencv_480/build/include;%(AdditionalIncludeDirectories)추가



![image](https://github.com/KimHyuckku/my-project/assets/148949177/825ef5a1-503b-4056-a4c4-ff857afdd4f5)

속성페이지 링커-일반-추가 라이브러리 디렉터리 ../thirdparty/opencv_480/build/x64/vc16/lib;%(AdditionalLibraryDirectories)

위에 C/C++과 링커 추가하는 것은 구성에서 Debug, Release, 모든 구성 모두 바꿔주기


![image](https://github.com/KimHyuckku/my-project/assets/148949177/1562186e-cd0e-4042-a53c-13b314d9c95c)

![image](https://github.com/KimHyuckku/my-project/assets/148949177/df4f93a4-fdc1-4d06-b155-9ef22d401105)
여기로
C:\work\Vision AI\VisionApp\thirdparty\opencv_480\build\x64\vc16\bin에 있는 dll파일 5개를 C:\work\Vision AI\VisionApp\Build\x64에 복붙하기

