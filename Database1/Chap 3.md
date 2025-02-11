
# SQL 1

SQL은 관계형 데이터베이스의 랭귀지

사용자와 데이터베이스 시스템사이에 의사소통을 위해서 사용함.

관계형데이터 베이스에서 가장 대표적이고 표준적인 SQL이 있다.

## Subtopics

오늘의 주제들

### Database Language

데이터베이스 언어의 역할이 무엇이고 어떤 종류가 있는가?

데이터베이스 랭귀지를 기능적 측면에서 아래와 같이 3가지로 나눈다.

- DDL (data definition language)
- DML (data manipulation language)
- DCL (data control language)

### DML

DML에는 4가지 기능이 있다.

- select
- insert
- delete
- update

### Null Values

칼럼의 값이 Null 값을 가질 수 있다.

Null값이 왜 필요하고 Null 값이 포함된 연산을 어떻게 처리할지 다룬다.

## 3.1 Database Language

## Database Language

DB system은 사용자가 DBMS에게 명령을 표현할 수 있는 방식이 필요하다.

기능적 관점에서 DB language를 3가지로 나누면 DDL, DML, DCL인데

- DDL: schema
- DML: select, insert, update delete
- DCL: tranjection, session, security, authorization

객체가 표현되는 방식에 따라서 아래 2개로 나눈다.

DCL은 3장에서 다루지 않을것임. db2과목에서 다룸.

- Procedural (절차적)
- Non-procedural (declarative)

## Data Definition Language (DDL)

DDL은 Scehema와 관련이 있습니다.

스키마 조작에 관련된 역할을 수행합니다.

대표적으로 Create Table, 스키마를 생성하는 명령어.

교수를 생성한다?

```sql
Create table professor(pID char(5), name varchar(20));
```

attribute (속성, 필드이름), domain (타입), integrity constraints (제약조건) 을 기술한다.

이런 정보들을 전달하면 DDL compiler가 테이블을 만들어준다.

## Data Manipulation Language (DML)

DB System에 존재하는 데이터를 access하고 조작하는 규약.

- 데이터 검색 (select)
- 삽입/삭제/업데이트

DML에 해당하는 Language를 질의어 (쿼리 랭귀지)라고 한다.

## Data Control Language (DCL)

Control에 관련된 명령어들

- Transaction 시작/끝
- 세션 시작/끝
- 백업/복원
- 권한 빌려주고(grant)/회수(revoke)
- 계정 관리
- 등등..

### 트랜젝션

쿼리를 받은 DBMS는 내부적으로 transaction을 생성한다.

transaction start 와 end사이에서 쿼리가 처리된다. (쿼리는 transaction 단위로 처리된다)

그 중간에 다른 쿼리가 들어오면 또다른 transaction을 생성해서 처리하게 된다.

### 세션

한 유저에의한 연속적 질의를 처리하기위해 dbms가 세션을 만들어서 처리한다.

## Procedural vs Declarative

### 절차적 언어

- 관계대수, C, C++, 대부분의 언어

어떤것을, 어떻게 얻는지 명시해줘야 한다. (what, how)

~테이블에서 ~를 프로젝트하고 ~하고 해서 ~, ~필드를 얻는다 이렇게 명시해줘야함.

### 선언적 언어 (비절차적 언어)

SQL, Lisp, 

어떻게 데이터를 얻을지 정보를 제공하지 않아도 된다. what만 주면됨

~에서 ~를 얻는다 이것만 명시하면됨. 

더 사용하기 쉽지만 컴퓨터 시스템이 처리하기 더 어렵다.

## 관계형 데이터베이스 언어

### 순수언어 (이론적 언어, 구현되지 않음)

- 관계대수
- 튜플 관계 해석
- 도메인(타입) 관계 해석

### 실제 사용되는 언어(유저)

- SQL
- QUEL
- LDL 


## SQL 살펴보기

SQL 은 Structured Query Language의 약자이다.

가장 대표적인 관계형 언어

기능적 측면에서 DDL, DML, DCL 로 구성됨.

데이터베이스 세계에서 사실상 표준이다.

## SQL 역사

1970년에 IBM이 만들었다.

ISO 표준 SQL들

- SQL-86, SQL-89
- SQL-92 (SQL2)
- SQL:1999 (SQL3)
- SQL:2003, SQL:2006, SQL:2008
- SQL:2011, SQL:2016

상업용 db에서는 대부분 sql2의 기능에 각기다른 자신만의 기능혹은 이후의 표준들이 더해져있는 형태다.

# 3.2 DDL SQL

## SQL Data Definition Language (DDL) SQL

relation 사이의 관계를 표현함. 각각의 스키마 생성.

- 도메인(타입)이 있어야한다.
- `Integrity constraints` 필요 (null 처리명시, 참조 무결성)
- 인덱스
- 물리적 저장 구조
- Authorization, security (DDL에 있다고 보기도 한다)

## Domain Types in SQL

gpa를 표현한다면 실수를 써야한다.

지원하는 타입들

- char(n)
- varchar(n)
- int
- smallint
- numeric(p, d): precision p, d digits
- real, double precision
- float(n)

## Create Table

스키마를 만들때 사용하는 명령어

Create table ${테이블이름}
(칼럼이름, 도메인타임,
 칼럼이름, 도메인타임,
 (integrity-constraint)
)

## Create Table Example

```sql
Create table professor(
    pID char(5),
    name varchar(20) not null,
    majName varchar(20),
    salary numeric(8,2)
);

// Insert into professor values ('10', 'Lee', 'CS', 7500);

```

## Integrity Constraints

- not null: 널값을 못갖는다
- primary key (A1, .., An)
  - 키는 중복이 없어야한다, null이면 안된다.
- foreign key (A1, .., An) references R
  - 다른 테이블 R을 참조한다
  - e.g) foreign key (majName) references department


## 대학교 데이터베이스 생성 예시

```sql
Create table student (
    ...
    check gender in ('F', 'M') // gender로 F 혹은 M 만 허용
);
```

```sql
Create table course (
    cID char(5) primary key,
)
```

```sql
Create table teaches (
    pID char(5),
    cID ...,
    semester ...,
    year ...,
    classroom ...,
    primary key (pID, cID, semester, year), // primary key로 4개 튜플이 필요한 이유
    foreign key (pID) references professor,
    foreign key (cID) references course,
    foreign key (classroom) references room,
)
```

primary key로 4개 튜플이 필요한 이유 : pID, cID, semester, year 를 전부 조합해서 사용해야 유일해짐.

## Drop/Alter Table

테이블 생성: create
생성된 테이블을 변경: alter
더 사용하지않는 테이블 제거: drop

Drop table student; 라고하면 `데이터 딕셔너리`에서 student 스키마를 삭제한다.

Alter table statement

- Alter table r add A D;
  - 테이블 r에 D라는 도메인을 갖는 칼럼 A를 추가
  - 새 속성은 널값을 갖을것임
- Alter table r drop A;
  - r 테이블에서 A칼럼을 제거

## DROP vs DELETE

- Drop table student;
  - 테이블과 내용물(튜플들) 전부 제거
- Delete from student;
  - 학생에서 모든 튜플을 제거.(데이터들)
  - 그러나 스키마는 그대로 남아있음 

# 3.3 DML SQL

## DML SQL

DML 핵심 4가지 기능

- Select
- Insert
- Delete
- Update

select: 검색한다
insert: 튜플을 테이블에 추가
delete: 조건을 만족하는 튜플들을 찾아서 삭제한다
update: 조건을 만족하는 튜플을 찾아서 특정한 칼럼을 업데이트한다.

## 삽입

```sql
Insert into course values ('437', 'Advanced Databases', 'CS', 4);
```

course 테이블에 새 튜플 ('437', 'Advanced ...', 'CS', 4)를 추가한다.

```sql
Insert into professor select * from professor;
```

select 를 먼저 하고 이후에 insert수행함

## 삭제

```sql
Delete from professor;
```
조건이 없기때문에 professor 튜플을 전부 삭제

```sql
Delete from professor where deptName='EE';
```
전자공학과 교수 전부 삭제

```sql
- Delete from professor where deptName in (select deptName from department where building = 'Vission Hall');
```
vission hall에 있는 학과를 찾고 그 학과인 교수를 삭제

```sql
Delete from professor where salary < (select avg(salary) from professor);
```

연봉의 평균값을 구한후 그 값보다 salary가 작은 교수를 제거.
- 평균값은 한번만 구한다. (삭제할때마다 업데이트되지 않는다)

# 업데이트

연봉 7000이상은 3% 인상 나머지는 5%인상

```sql
Update professor set salary = salary * 1.03 where salary > 7000;
Update professor set salary = salary * 1.05 where salary <= 7000;
```

위의 코드는 중복된 임금인상이 있을수 있음 따라서 아래와 같이 해야함

```sql
Update professor
set salary = case
             when salary <= 7000 then salary * 1.05
             else salary * 1.03
             end;
```

모든학생의 이수학점을 업데이트하기

```sql
Update student S
set S.totalCredit =
      (select sum(credit)
      from takes natural join course
      where S.sID=takes.sID and grade <> 'F' and grade is not null
      );

Update student
set totalCredit = 0
where totalCredit is null;
```

takes table

| sID | cID | year | semester | year |
| --- | --- | ---  | ---      | ---- |

course table

| cID | title | deptName | credit |
| --- | ---   | -------  | -----  |



1. natural join 한다.

takes 테이블과 and course 테이블의 natural join table

공통되는 칼럼은 한번만 쓴다(cID)

| sID | cID | year | semester | year | title | depthName | credit |
| --- | --- | ---  | ---      | ---- | ----  | ---       | ---    |

2. student S.sID 와 sID가 같고 grade 가 F가 아닌것들만 뽑는다.

3. credit을 합계내서 totalCredit을 업데이트한다.

# 3.4 Select SQL Statement

## Select 절

### select 다음에는 attribute-list 가 온다.

attribute 는 관계대수에서 project에 대응된다. 즉 모든 칼럼을 뽑느것이 아니라 특정 칼럼만 뽑음.

결과 테이블은 해당 칼럼만 존재한다.

### attribute-list 자리에 * 를 사용하면 모든 attribute 를 가져온다.

```sql
Select * from ${table_name}
```

### select 절은 arithmetic 표현을 포함할 수 잇다.

```sql
Select pID, salary/12 from professor;
```

연봉을 12로 나눠서 가져옴. 즉 월급을 가져올 수 있음.

### SQL은 튜플의 중복을 허용한다.

한 테이블에서도 중복된 튜플을 허용한다.

앞서서 2장에서 배울때 관계형 데이터 모델에서는 튜플의 중복을 허용하지 않는다고 했는데, 어떻게 된것인가?

여기서 얘기하는 SQL은 관계형 데이터 모델의 확장된 버전이기 때문에 허용한다.

지금부터 다룰 모든 SQL은 테이블, 결과테이블에서 중복된 튜플이 존재 할 수 있다.

### distinct 키워드

중복된 튜플을 허용하지 않기 위해서는 distinct 키워드를 사용한다.

```sql
Select distinct deptName from professor;
```

위 쿼리의 결과 테이블

| deptName |
| ---      |
|  CS      |
|  EE      |
|  ...     |


### all 키워드

all은 default로 설정된다. (all을 안써도 all로 동작)

```sql
Select all deptName from professor;
```

위 쿼리의 결과 테이블 (중복을 허용함)
| deptName |
| :--: |
| CS |
| CS |
| EE |
| EE |
| .. |

## where 절

where절은 `조건`을 표현하기위해 존재한다. 

관계대수에서 select pair 절에 대응됨. (sigma p 에서 p)

CS학과에서 연봉이 8000이상인 교수이름 찾기

```sql
Select name from professor where deptName = 'CS' and salary > 8000;
```

### and or not 을 사용해서 조건을 표현 할 수 있다.

not (salary > 8000) 이런 표현이 가능함.

위 예제에서 and가 쓰임.

## from 절

from절에는 relation list가 온다. 

관계대수에서 cartesian product 에 대응됨.

```sql
Select * from professor, teaches;
```

위 질의를 처리할때 professor 테이블과 teaches를 cartesian product함.

professor의 칼럼과 teaches의 칼럼이 전부 포함되며 

공통되는 칼럼명은 p.칼럼명, t.칼럼명 과 같이 구분되어서 생성된다.

대부분의경우 두개이상의 테이블이 오는경우 where절이 온다.

## SQL 실행 모델

질의문을 어떻게 처리하는가?

- select
- from
- where
- groupby
- order by
- having

논리적으로 어떻게 처리되는가? db system이 실제적으로 어떻게 처리하느냐는 또다른 문제이다 (최적화)

논리적으로 어떻게 처리되는지를 다룰것임.

1. 각 테이블에서 튜플을 하나 뽑는다 (from 절)

2. 뽑은 튜플을 where절로 검사한다

3. 만약 true면 결과 테이블에 넣음

1, 2, 3을 튜플이 더 안뽑힐때까지 반복

group by, having은 나중에 설명함. 끝.

