# 1강 (1)

# 1. Introduction To Database

네 안녕하십니까

오늘은 1장에 대해서 강의를하겠습니다.

1장에서는 데이터베이스에 대한 소개를 다루고있는데요
데이터베이스에 대해서 본격적으로 다루기 전에 데이터베이스가 무엇이고 어떻게 활용하는지 아는게 중요하다고 생각이 듭니다.

그래서 1장에서는 데이터베이스에대한 소개를 다루는데

자 먼저 강의를 시작하기전에 숭실대학교 컴퓨터학부에서는 데이터베이스를 어떤식으로 강의를 하느냐에 대해서 간략하게 얘기를 하도록 하겠습니다.

우리가 보통 데이터베이스는 어떻게 생겼다 라고 얘기할때 보통 이런 그림을 그리게 됩니다.

(원통형 그림)

맨 아래쪽에는 실세계의 데이터를 만약에 관계형이라고하면 테이블형으로 존재하게 됩니다. 

실 세계의 데이터를 저장하고있는곳 그것을 DB라고 합니다. 그리고 맨위에는 유저가 있을수있겠죠.

또는 이 유저는 직접 쿼리를 작성을해서 원하는 데이터를 가져올수도 있구요 아니면 중간에 애플리케이션의 도움을 받아서

유저가 이 어플리케이션에 최소한의 정보를 주고 애플리케이션이 쿼리를 만들어서 이 쿼리를 DBMS에 전달을 하기도 하죠.

그러면 이 쿼리는 어디에 전달이 되느냐, 중간에 있는 DBMS라는 시스템에 전달이 됩니다.

그러면 이 DBMS는 사용자의 쿼리를 받아서 조건에 맞는 데이터를 검색하거나 삭제하거나 갱신하거나 하겠죠.

그러면 이 DBMS는 사용자의 질의를 처리하기 위해서 당연히 DB에 접근을 하게됩니다. 

그래서 이 사이에 data I/O가 당연히 발생하게 되겠죠.

그래서 이런 과정을 거쳐서 사용자의 질의에대한 결과를 만드는 것이죠.

자 그래서 일반적으로 데이터베이스 시스템이라고하면 간략하게 설명하면 이렇게 되겠죠.

그래서 우리 컴퓨터학부에서는 데이터베이스시스템을 크게 2가지로 나누게 됩니다.

이런쪽(user->app->DBMS)을 다루는것을 DB1이라고하고 이 중간쪽(DBMS)은 DB2에서 다루게 됩니다.

DB1에서는 이런부분이기 때문에 즉 뭐냐하면 데이터베이스에 대한 정의를 바탕으로해서 실세계에 존재하는 그런 데이터를 사용자가

데이터베이스에 저장하기 위해서는 어떻게 해야되나, 아니면 내가 원하는 데이터를 검색하기 위해서는 어떤 데이터베이스 랭귀지를 사용을 할수가 있느냐

어떤식으로 데이터베이스 쿼리를 사용해야되느냐 이런것을 다루는 것이죠.

그리고 만약에 우리가 관계형 데이터베이스를 쓰고있다면 실세계의 데이터를 관계형 데이터베이스에 저장하기위해서는 데이터 모델링이라는것을 해야되는데

이 모델링을 어떻게 하느냐 그런것에 대해서 공부를하게됩니다.
그러면 DB2에서는 무엇을하느냐, 이런 요청들이 들어왔을때 실질적으로 DBMS에서는 어떤일을 하느냐 라는 겁니다.

여기서는 일단 질의를 처리를 해줘야되니까 쿼리 프로세싱을 해줘야겠죠. 

그리고 질의는 트랜잭션이라는걸로 변형이된는데 
트랜잭션 매니지먼트를 해줘야하고, 그 다음에 데이터에대한 I/O를 담당해줘야합니다. 그리고 데이터베이스에대해서 복구도 필요하겠죠.

이것 말고도 엄청나게 많습니다. 그래서 이것들이 실질적으로 어떻게 처리되느냐 그것을 배우는게 DB2입니다.

DB1에서는 db가 무엇이냐, 관계형디비 rdbms는 뭐냐, 데이터모델링에대한 내용, 데이터베이스 랭귀지 뭐가있냐 이런것에 대해서 다루게 됩니다.

혹시 여러분들이 DBMS에 대해서 공부를 하고싶다면 다음학기에 DB2라는 과목을 수강하면 되겠습니다.

그래서 일단 DB1, DB2로 나눠서 이런것들을 강의한다 라고 알려드렸습니다.

이걸 바탕으로해서 내가 원하는 것을 집중적으로 공부했으면 ~~합니다.

# Subtopics

- Databases
- Data Abstraction and Data Model
- Database Systems

1장에서 다루는 토픽들은 뭐가있냐 그런것인데요.

데이터베이스. 데이터베이스란 무엇이냐 그것이죠. 그것에 대해서 간략한 얘기를 할것이구요.

그다음에 데이터 모델에 대해서 얘기를 할겁니다. 우리가 데이터베이스를 얘기를 할때 크게 관계형 데이터베이스와 객체지향 데이터베이스를

사용할수있는데 그때 데이터베이스 안에 실세계 데이터를 저장을 해야겠죠

예를들면 학생 데이터가 있다라면, 이걸 관계형 데이터베이스에 어떤식으로 표현해서 저장할꺼냐 이거죠

그래서 데이터를 어떤식으로 표현할것인가 그겁니다. 관계형 데이터베이스에서는 어떤식으로 표현하죠?

테이블. 형식으로 표현을 합니다 또는 이거 relation이죠? 테이블이라고 부르기도하구요

이런식으로 표현을 한다 라는겁니다. 표현. 그렇다면 표현하는 방법이 뭐가있느냐 라는 것이죠? 그런 이런 방법 툴을 뭐라고부르냐면

데이터베이스 모델이라고합니다. 구별해서 간략하게 살펴보도록하고요.

그리고 이앞에 나오는건 database abstraction이 될텐데 자 실제적으로 데이터베이스 시스템은 사용자가 다 다루기에는 덩치가 엄청나게 크고

복잡합니다. 따라서 이렇게 복잡한 시스템을 다 이해를 해야지만 사용자가 데이터베이스를 사용을 할 수 있다 라고 하면 그 데이터베이스를

사용할 사람은 아무도 없겠죠. 그래서 그 복잡한 시스템을 감춰주는게 필요할겁니다.

그래서 유저 레벨에따라서, 초보자가 있을수 있겠죠, 그리고 중급, 고급. 각각의 사람들이 데이터베이스를 바라볼때
이런 dbms가 있구요 이렇게 유저가 이렇게 이런 그림을 그릴수 있겠죠.

이 초보자가 바라볼때 전체적인 시스템을 바라볼때 어느정도 보여줘야되냐 중급자, 고급자가 바라볼때 어디까지 보여줘야되냐.
예를들어 초보자가 바라볼때는 이 dmbs - db에 대해서 전혀 보여주지 않아도 되겠죠. 만약에 보여준다고하면 이정도레벨, 예를들면 쿼리를

어떻게 작성해야되냐, 이런 정도만 알려주면 되겠고요. (테이블형식)

자 그렇지만 고급 사용자같은경우 그렇지 않죠. 

전체 그림에대한 즉 이 dbms내부에대한 정보까지 알 필요가 있습니다.

그 정도에 대한 그 정보를 제공을 해줘야 된다는거겠죠.

전체적인 시스템에 대해서 시스템에 대한 정보를 감춘다라는 의미에서 abstraction.

아까도 말했듯이 초보자 같은경우에는 많은 정보를 감춰야 될것이구요 고급은 그렇지 않죠.

그래서 abstraction level을 두게 됩니다. 이 레벨을 둬서 각 사용자마다 어느정도에 대한 시스템 정보를 줘야될것인가 결정을 한다는 것이구요.

그 다음 데이터베이스 시스템 이부분이 되겠습니다.

예 그럼 먼저 데이터베이스란 무엇인가에대해서 살펴보겠습니다. (슬라이드 넘김)

# DB, DBMS, DBS

## DB is a collection of data

자 첫번째 토픽으로 데이터베이스죠. 데이터베이스란 무엇인가 그것인데.

자 일반적으로 데이터베이스를 공부를 할때 몇가지 용어가 등장을 합니다 그래서 우리가 보통

## In practice, those terms are used interchangeably!

데이터베이스라고 하고 어떤사람은 db, dbms, dbs라 하는데요 이게 여기보면 맨 마지막 문장이 있죠. 특별한 경우가 아니라면 이것들은 다 같은 의미로 사용이됩니다.

문맥에 따라서 이런것들이 조금씩 달라질수가 있습니다.

예를 들면 db라고하면 데이터에 대한 컬렉션이라고 되어있죠. 

실세계의 데이터를 관계형데이터베이스라고 한다면 테이블형식으로 표현을 할텐데 이렇게 테이블형식으로 표현된 데이터의 집합이라고 할 수 있습니다.

만약에 관계형 디비라고하면 예를 들면 학생에 대한 정보를 저장하는 테이블, 교수에대한 테이블, 교과목에대한 테이블이 있겠죠. 

## DBMS is a collection of software that not only allows us to define, construct, manipulate databases but also provides a number of desirable functionalities (data independence, data sharing, recovery, security, etc.)

그다음에 dbms라는 용어는 이를 풀어서 얘기하면 database management system이라고 할 수가 있습니다. 이거는 아까 우리 그 그림에서 중간에 dbms가 있다고 얘기를 했었죠 이걸 지칭을 합니다.

이건 뭐냐고하면 소프트웨어의 집합이라고 할 수 있습니다.

그래서 아까도 얘기했듯이 dbms의 기능이 여러가지가 있습니다. 쿼리 프로세싱, 트랜잭션 관리, 버퍼 매니지먼트, 페이지 I/O, 등등 여러가지가 있는데 이것들을 관리하는 소프트웨어의 집합이라고 할 수 있습니다.

## DBS (Database System) = DB + DBMS

그다음 보통 데이터베이스시스템(dbs)라고하면 이 두개 db + dbms 의 결합이라고 할 수가 있죠. 이 두개를 합쳐서 데이터베이스시스템이라고 한다 이겁니다.

그다음 여기(DBMS위에)에 뭐가있냐면 당연히 유저가 있겠죠.

그래서 아까도 얘기를 했듯이 일반적으로 이 용어들 같은 의미로 사용이 된다 할 수 있겠습니다.

# Database applications are ubiquitous!

- Database applications include
 - Banking: transactions
 - Airlines: reservations, schedules
 - Universities: registration, grades, classes
 - Sales: customers, products, purchases
 - Online retailers: order tracking, stock, payment
 - Manufacturing: production, inventory, orders, supply chain
 - Human resources: employee records, salaries, tax deductions
- Database touch all aspects of our lives!

그다음 자 데이터베이스 애플리케이션들은 유비쿼터스하다 이거죠.

즉, 우리의 일상생활에 많은 영향을 끼친다라는 것이죠.

우리 일상에 데이터베이스를 기반하고 있지 않은 애플리케이션이 있을까요?

그런게 어플리케이션 찾아보는게 쉽지는 않을겁니다.

예를 들어 뱅킹 서비스, 비행기 표같은거 예약할때 다 밑에는 데이터베이스 시스템이 있을거구요. ...(예시 더 설명함)

따라서 데이터베이스는 우리 생활에 엄청난 영향을 끼친다는것이 되겠습니다.

# University Database Example

- University maintain a variety of data on students, courses, staffs, etc.
- Application program examples
 - Add new students, instructors, and courses
 - Register students for courses, and generate class rosters
 - Assign grades to students, and generate transcripts
 - Maintain salaries for professors and staffs, manage ... etc.

아... 뭐 유니버시티 데이터베이스라해서 아까도 말했듯 학교에서 데이터를 관리를 한다 이거죠.

구체적으로 학생에대한 정보, 교과목에대한 정보, 성적에 대한 정보, 그다음 관계에 대한 정보.

어떤 교수가 어떤강의를 언제 강의를 했다 이런것을 관계에대한 정보라고 할 수 있습니다.

그리고 에 예, 이런 데이터베이스 위에서 동작을 하는 애플리케이션 프로그램들이 존재를 해야겠죠.

예를 들어 숭실대학교 같은 경우에 세인트 라는게 있는데, 이를 통해서 예를 들면 어떤 학생이 입학을 하게되면 그 학생을 데이터베이스에 추가 할 수도 있구요, 강사도 마찬가지고, 코스 등록 등등...

그 다음에 성적표를 만들어내는 그런 기능이 ...

그래서 이러한 기능들을 담고있는 프로그램들이 있을겁니다.
이런 기능이 필요하다 라는거죠(머지 ㅋㅋ??!)

# Advantages of DBMSs (1/2)

- Data abstraction
- Easy accessing data
 - Database language support
 - User interfaces
- Controlled data redundancy and inconsistency
- Integrity constraint (IC) enforcement
 - With file systems, ICs become buried in program code rather than being stated explicitly
 - With DBMS, easy to enforce ICs as well as add/update/delete ICs

그다음 우리가 데이터베이스를 사용을 할때 어떤 장점이 있냐는 거죠

이런 장점을 비교할때 우리가 파일시스템을 사용할때와 비교하는데
이를 비교함으로써 dbms의 장점이 엄청나게 많다라는것을 강조하고있습니다.

어떤 장점이있느냐 data abstraction, 아까도 얘기를 했었죠. 사용자의 수준에 따라서

사용자한테 보여지는 정보를 다르게 할 수 있다라는것이죠.

그다음 데이터 엑세싱을 아주 쉽게 할 수 있다 라는겁니다.

유저가.... dbms가 있고요 여기에(아래) db가 있습니다. 

그랬을때 여 db안에 존재하는 아주 많은 데이터중에 어떤 조건을 만족하는 데이터를 찾고싶을때 유저가 어떻게 해야되느냐 라는거죠?

바로 쿼리를 작성을 하면됩니다. 

관계형데이터베이스라면 SQL이라는 언어를 통해서 쿼리를 작성을 할 수 있구요 그러면 이 쿼리를 dbms한테 전달하면 그 내부에서 이거를 처리를 하겠죠. 아주 복잡한 과정을 거쳐서 그런다음에 그 결과를 사용자한테 전달을 하겠죠. 또는 이 중간에 application을 둘수 있겠죠.

그러면 더 간단하게 사용을 할 수 있습니다. 왜냐면 이 애플리케이션이 쿼리를 만들어줘요 그래서 아주 쉽게 사용할 수 있다라는 장점이 있다 라는거죠.

그다음에 데이터 redundancy를 방지를 할 수 있다는겁니다.

따라서 이 inconsistency도 방지를 할 수 있다는겁니다.

예를 들어서 똑같은 학생을 두번 저장하면 안되겠죠.

데이터베이스를 사용하면 그런걸 방지를 할 수 있구요 반면에 파일시스템을 사용을한다면 학생파일을 관리할때 같은 학생이 존재하는 여러 파일을 만들 수가 있다 그게 뭐냐면 데이터 redundency인데. 그리고 inconsistency 이거는 데이터베이스를 사용하는 가장 중요한 특징, 기능이라고 할 수 있는데.

데이터베이스를 사용하는 가장 중요한 목적이 뭐냐하면 항상 consistency를 보장을 받기 위한겁니다.

예를 들면 실세계에 학생이있는데 그 학생에대한 주소와 정보를 관리할때 데이터베이스를 쓰죠

그 학생에 대한 정보는 일치를 해야되는데 inconsistency는 발생하면 안됩니다 예를 들면 이 학생의 성적이 A인데 디비에 B가 저장되있다 이러면 안되겠죠 이런경우 inconsistency가 발생했다고 합니다.

dbms를 쓰면 이런 inconsistency를 방지를 할 수 있다는거죠.

자 만약에 데이터 redundancy가 발생을 한다면, 

학생 데이터가 여러곳에 있는데 만약 그 학생에 대한 업데이트가 발생했을때 한쪽에만 업데이트를 해준다면 inconsistency가 발생할 수가 있죠. 

그 이유가 뭐냐면 데이터 redundancy때문인거고.

그렇지만 dbms는 data redundancy를 방지를 할 수 있기 때문에 그로 인해서 발생하는 inconsistency도 방지를 할 수 있다는 겁니다.

그다음에 integrity constraint를 강화를 할 수 있다는 것인데요.

자 우리 실세계에서 예를 들면 아까 학생 데이터를 계속 얘기를 했었는데,

학생은 어떤 정보를 갖고있죠? 학번 학년, 등 이 학년이라는건 어떻게 되죠? 반드시 1, 2, 3, 4 이런값만 가져야되죠? 그런것을 integrity constraint라고 합니다. 또 예를 들면 age는 반드시 0보다 커야된다 이런것이되겠죠.

실세계에는 아주 많은 integrity constraint가 존재합니다. 그래서 당연히 이런것들을 체크를 해야된다. 그래서 이런것들이 필요한데 만약에 우리가 파일시스템을 쓴다고하면 이런 integrity constraint를 체크하는 코드들을 다 찾아서 그걸 바꿔줘야 합니다. 

예를들면 은행의 정책이 바뀌어서 잔고가 마이너스가 될수도 있게 바뀐다면 그 해당코드를 바꿔서 다 바꿔줘야합니다. 그렇지만 데이터베이스를 써서 관리를하면 이 integrity constraint를 한줄로 표현할 수 있는데 그것만 바꿔주면 됩니다. 

뭐 예, 이것에 대한 얘기는 차후에 강의를 할테니까 그때가서 다시 얘기를 하겠습니다.

어쨋든 integrity constraint를 보장하는것이 아주 쉽다라는것이구요.

# Advantages of DBMSs (2/2)

- Atomicity of updates
 - For example, transfer of funds from one account to another should either be completed or not happend at all (**all or nothing**)
- Concurrent access by multiple users
 - Uncontrolled concurrent accesses can lead to inconsistencies
 - Think about two people reading a balance (say 100) and updating it by withdrawing money (say 100 each) at the same time
- Data security
- Data backup and recovery

## Atomicity of updates

자 그다음 또 다른 장점으로는 뭐라고 그러냐면 atomicity라고 합니다. 이건 번역을할때 원자성이라고 할 수 있는데

이게 뭔뜻이죠, 원자라는것은 더이상 깰수없는 이런건데, 물론 현대 과학에는 그렇지 않죠 어쨋든 사전적인 의미로서 더이상 깰 수 없는 그런 뜻을 갖고 있습니다.

그래서 보통 우리가 이런 이런 얘기를 많이 씁니다. **all or nothing**

그래서 이런 개념에 해당하는게 atomicity라고 할 수 있습니다.

이런게 언제 발생하냐면 업데이트 할때 발생하는데 여기서 예가, 계좌를 다른 계좌로 이체하는 과정에서 failure가 발생할 수 있죠. A계좌에 100이라는 돈이 있습니다.

이걸 B계좌로 transfer합니다. B계좌는 현재 0입니다.

이게 정상적으로 수행이 되면 A=50, B=50이 있어야겠죠. 

만약에 정상적으로 처리되지 않더라도 A=100, B=0이여야되는데 

이게 중간에 실패해서 A=50, B=0이 되면 안되겠죠. 

반드시 A, B의 합이 100이되어야 한다 라는겁니다.

그래서 All or nothing. 즉 all이라는건 완벽하게 수행된경우, nothing이라는건 처리하기 전상태 이경우(A=100, B=50)가 되겠죠.

실세계에서 이런일들은 아주 중요하죠. DBMS를 쓰면 이런일들을 아주 쉽게 보장받을 수 있습니다.

## Concurrent acces by multiple users

그다음은 concurrency인데 동시성이라고 볼 수 있겠습니다.

여러명이 동일한 데이터에 대헤서 접근 할 수 있습니다. 

유저 원 유저 투, 이런 유저들이 동시에 뭘 할 수 있다는거죠. 

여러명의 유저가 A라는 계좌에 대해서 돈을 찾는다고 하면 A계좌에는 100이 있습니다. 

이사람은 20을 찾고 싶고 저사람은 30을 찾고싶습니다. 

정상적으로 처리가되면 A는 50이 남아있어야겠죠. 

근데 A에 70이 남은 결과가 나오면 안되겠죠. 근데 DBMS를 쓰면 이를 간단하게 보장 받을 수 있습니다.

이러면에서 DBMS가 파일시스템에 비해 유리하다.

## Data security

## Data backup and recovery

또다른면에서 보안, 백업, 리커버리가 아주 쉽게 동작시킬 수가 있다 라는것이고 

또 한번 얘기하면 파일시스템에서는 이런것들을 구현하기 위해서 아주 많은 것들을 해줘야한다는것이죠.

그래서 이런 여러가지 dbms가 갖는 장점이있다 이겁니다.

# File Systems

- A file system is usually a part of an operating system (for example, "filesystem" in Unix), and theoretically users can manage their data with a file system
 - Users utilize systems calls such as open, close, read, write, and lseek in Unix
 - when we use file systems to manage databases, we are likely to have a set of different data files and different application programs
 - All functionalities of DBMSs are then on users responsibility

자 반면에 파일시스템같은 경우에는 dbms가 갖는 장점을 갖기 위해서는 아주 복잡한 일들을 해야된다 이거죠

그래서 데이터를 관리하기위해서 순수하게 파일시스템을 사용하게된다면 복잡한 데이터같은경우는 불가능 할 수도 있겠습니다. 그래서 우리는 이런것들을 잘 다룰 수 있는 DBMS를 쓰면 편리하게 이런 기능을 해결 할 수 있다 라는게 되겠습니다.
