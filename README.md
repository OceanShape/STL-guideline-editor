# STL-guideline-editor
Edit STL model using guideline.


### 환경 구성 방법
1. `Visual Studio 2019` 설치
2. `Windows`용 `Qt` 설치
    - `Qt Framework` 공식 홈페이지에서 `Qt Creator` 계정 생성
    - 인스톨러 다운로드 및 실행: [https://www.qt.io/download-thank-you?hsLang=en](https://www.qt.io/download-thank-you?hsLang=en)
    - 계정과 회사 이름을 작성하고, 다음 단계로 진행
    - 사용자 지정 설치를 선택하고, `Qt 5.15.2`, `Qt designer`, `Qt debugging for windows`만 체크하여 설치 진행
3. `Visual Studio`에 `Qt` 애드온 추가
    - 확장 → 확장관리
    - `qt` 키워드로 `Qt Visual Studio Tools` 항목 검색
    <img src="https://user-images.githubusercontent.com/42532724/158069722-fc222891-0d31-4f7e-a4b1-90310c92b41f.png" width="50%" height="50%">

    - ‘다운로드’를 눌러 설치를 예약한 뒤 `Visual Studio` 종료
    - `VSIX Installer` 창이 나타나면, `Modify` 선택
    - 설치가 완료되면, `Visual Studio` 재실행
    - 확장 → `QT VS Tools` → `Qt Versions` 선택
    - `add new Qt version` 항목에서, `qmake.exe`를 찾아 해당 버전의 Qt 라이브러리 등록
        - 이전 단계에서 설치한 `Qt` 라이브러리 디렉토리의 `bin` 폴더 안에 있음
