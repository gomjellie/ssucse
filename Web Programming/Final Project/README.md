
# 커뮤니티 서비스 만들기

실행: 서버
```sh
cd ./server && node app.js
```

실행: 프론트

```sh
cd ./front && npm start
```
## 기본 기능 구성 (총 40점)

(10점) 사용자 등록 / 로그인 / 로그아웃 (/)

(10점) 소개 페이지 (/about) - static한 HTML 페이지

(10점) 게시판 (/board) - 읽기, 쓰기, 수정, 삭제

    - 제목, 작성자, 작성일, 본문, (...hashtag)

(10점) 사진 갤러리 (/gallery) - 읽기, 쓰기, 수정, 삭제

    - 사진, 작성자, 작성일, (...hashtag)

## 추가 기능 (총 10점)

사용자 간의 메시지 전달 기능
    
    - (2점) 사용자에게 메시지를 전송하고, 전달받은 메시지를 메시지 함에서 확인 (/msg/:id)

게시판의 검색 기능

    - (2점) 게시글의 본문 검색
    - (2점) 작성자 ID로 검색

게시판과 갤러리의 hashtag 기능

    - (2점) 게시판에서 hashtag 기반으로 게시글 검색
    - (2점) 갤러리에서 hashtag 기반으로 사진 검색

## 평가 관련 안내

기능 구현 여부에 따라 50점 만점으로 평가

심미적인 부분에 대해서는 별도 점수 부여 X

아래 사이트들은 단순 참고용

    - https://getbootstra.com/
    - https://material.angular.io/
    - https://material-ui.com/

## 안내 사항

(필수) Mongo DB 사용

    - 결과물 제출 시 (DB 파일까지 같이 압축하여 제출)
    - 참고: mongodump

(권장) Express + 템플릿 엔진 (Jade, pug, nunjucks, ...)

(참고) MEAN stack 혹운 MERN stack 사용 가능
    
    - MongoDB + Express.js + ... + Node.js
    - Angular 또는 React

## 권장 진행 순서

1) Express + passport로 로그인 기능 구현

2) 소개 페이지 route 구현

3) 기본 게시판 기능 구현 (hashtag를 제외한 기능들)

    - 쓰기 -> 삭제 -> 수정

4) 기본 사진 갤러리 기능 구현 (hashtag를 제외한 기능들)

    - (힌트) multer 활용

5) 추가 기능 구현

    - 메시지 전달, 검색, hashtag

## 제출 방법

Myclass에 소스코드 + DB dump 파일 업로드

    - 참고한 소스가 있을 경우 반드시 주석으로 출처 명시

제출 기한: 12월 18일 (금) 23:59
