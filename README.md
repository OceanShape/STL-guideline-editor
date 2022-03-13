# STL-guideline-editor
Edit STL model using guideline.


### 환경 구성 방법
1. git clone을 통해, [https://github.com/OceanShape/STL-guideline-editor.git](https://github.com/OceanShape/STL-guideline-editor.git) 리포지토리 다운로드
2. 비주얼 스튜디오 설치
    - 버전: 비주얼 스튜디오 19(최신 버전)
3. 비주얼 스튜디오 환경에 Qt 라이브러리 설치
    - Qt 프레임워크 공식 홈페이지에서 Qt 크리에이터 계정 생성
    - 인스톨러 다운로드: [https://www.qt.io/download-thank-you?hsLang=en](https://www.qt.io/download-thank-you?hsLang=en)
    - 인스톨러 실행
    - 계정 입력 후, 다음 단계 진행
        - 회사 이름은 Korea University Research & Business Foundation으로 지정
    - Qt 5.15.2, Qt designer, Qt debugging for windows만 체크하여 설치 진행
4. Visual Studio에서 Qt애드온 추가
    - 확장→확장관리
    - qt 키워드로 Qt Visual Studio Tools 항목 검색
    <img src="https://user-images.githubusercontent.com/42532724/158069722-fc222891-0d31-4f7e-a4b1-90310c92b41f.png" width="50%" height="50%">

    - ‘다운로드’를 눌러 설치를 예약한 뒤 Visual Studio 종료
    - VSIX Installer 창이 나타나면, Modify 선택
    - 설치가 완료되면, Visual Studio 구동
    - 확장 → QT VS Tools → Qt Versions 선택
    - <add new Qt version> 항목에서, qmake.exe를 찾아 해당 버전의 Qt 라이브러리 등록
        - 위에서 설치한 Qt 라이브러리 디렉토리의 bin 폴더 안에 있음

