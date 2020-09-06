
# Lecture1-B-Introduction

였습니다...

의 제목이 이거라 했었죠.

# 1. Computer Abstractions and Technology

1장에는 13개의 챕터가 있습니다.

```text
1.1 Instroduction (RED)
1.2 Eight Great Ideas in Computer Architecture (Strong)
1.3 Below Your Program (weak)
1.4 Under the Covers (weak)
1.5 Technologies for building Processors and Memory (weak)
1.6 Performance (Strong)
1.7 The Power Wall (weak)
1.8 The Sea Change: The Switch from Uniprocessors to Multiprocessors (weak)
1.9 Real Stuff: Benchmarking the Intel Core i7 (weak)
1.10 Fallacies and pitfalls (weak)
1.11 Concluding Remarks (weak)
1.12 Historical Perspective and Further Reading (Strong)
1.13 Exercises (weak)
```
이렇게 흐리게(weak) 한거는 다루지 않을 부분이고 진하게 되있는것은 강의에서 다루는 부분이고 빨간색은 이번강의 렉쳐1에서 다루는 부분입니다.

책의 모든 부분에서 뒷부분에 Real Stuff, Fallacies and Pitfalls, Concluding Remarks, Historical Perspective and Further Reading, Exercises 이런 부분이 있습니다.

어느 챕터든지 다 있는데 거의 강의에서는 다루지 못할것 같습니다.

이책이 한학기에 강의하기에는 분량이 좀 많은건데 한학기에 마쳐야 하기때문에 그렇습니다.

# Computer Architecture

어,, 컴퓨터 아키텍쳐 . 컴퓨터 구조

가 무엇이냐.

## Instruction Set Architecture (ISA)

프로그래머한테 보이는 부분. Instruction Set이 다음강의에서 나올 부분이라 설명이 안된 부분이기는 하지만

컴퓨터 동작을 이해하고 설명하는데 가장 핵심이 되는게 명령어 입니다.

그 명령어들 기능들 중에서 사용자에게 보이는 부분.

## Those aspects of the instruction set available to programmers, independent of the hardware on which the instruction set was implemented

실제로 그게 하드웨어가 어떻게 구현되었냐와 상관없이.. (영어 읽음)

실제로 전자회로로 어떻게 만들었느냐는 제외하고 사용자에게 어떻게 보이느냐.

사용자가 사용을 할때 얘는 32비트 + 32 비트 연산을 할 수 있다. 얘는 곱하기를 한번에 처리할 수 있다. 

아니다. 이 프로세서는 그런게 안되서 루프를 여러번 돌리고 해야된다.

사인x를 하드웨어가 직접 해주냐. 아니면 소프트웨어로 처리를 해야되느냐. 이런부분.

**사용자에게 영향을 미치는부분만을 아키텍쳐라고 합니다.**

밑에 어떻게 되어있느냐는 과거에는 **Organization**이라고 했는데 요즘은 **Implementation**이라고 합니다.

그니까 하드웨어의 동작, 하드웨어 중에서도 로우레벨은 제외하고 사용자에게 보이는 부분, 상위 레벨만 아키텍쳐라고 한다. 그러는데

우리 책도 그렇고, 우리책 이름이 organization design입니다. 요새는 잘 구분 안합니다. 우리 책도 그렇고 대부분의 책이 상위레벨 하위레벨 다 다루는데 주로 상위레벨 치중해서 다룬다.

## The term computer architecture was first used in 1964 by Gene Amdahl, G. Anne and ... of IBM System/360

그런데 architecture라는 말은 1964년에 IBM에 과학자들이 처음에 설계를 하면서 사용하기 시작했습니다.

보통 구조라고하면 건축이죠. 보통 구조라고하면 organization, structure라는 말을하는데 특이하게 architecture라는 말을 썻습니다.

그게 지금까지 내려오고 있어요.

어,, Instruction Set Arhitecture ISA 라는 말이있는데, 이게 원래 줄여서 Architecture라고 하는데 줄이기전에 ISA입니다.

그냥 Architecutre라고 하면 건축이 되니까 ... 긴한데 보통 Architecture라고 하죠.

## IBM system/360 was a family of computers

IBM 360이 최초의 Family 개념이 도입된 컴퓨터다.

이전의 컴퓨터들은 보통 컴퓨터가 개발이 되었다 하면 거기서 끝입니다. 

더 좋은 기종을 만들었다 하면 그전의 컴퓨터에서 돌아가던 기계어 프로그램이 돌아가지 않는, 호환성이 없는 그런것이였습니다.

그래서 IBM에서 이걸 개발하면서 Family 개념을 적용을 했어요.

기본적으로 Architecture는 같다. 명령어 같고. 하드웨어 기본 기능이 같습니다.

프로그램에서 보이는 기능은 같아요. 그러니까 다른모델

360의 다른모델에서 작성한 기계어 프로그램이 돌아갈 수 있다.

같은 기계어 프로그램을 돌릴수 있는 여러개의 모델이다 해서 Family라는 말을 썻습니다.

그러면서 Architecture와 Organization(implementation) 이 분리된거죠.

여기에 속한 처음엔 5개의 모델이였는데 그것이 Architecture는 같지만 Organization이 다른 그런얘기죠.

여러가지 얘기를 했지만 컴퓨터 아키텍쳐라는것은 컴퓨터 하드웨어의 특성중에서

프로그래머에게 보이는 상위레벨을 얘기한다.

그밑에꺼는 organization,  implementation이라고하는데 사실 요새는 잘 구분하지 않는다.

# Architecture vs Implementation

두가지 비교하는것.

요새는 잘 구분하지 않는다고는 했지만.

## Instruction set architecture (= Architecture)

Architecture는 하드웨어하고 소프트웨어 중에서 최 하층의 소프트웨어 그것들간의 인터페이스가 됩니다.

컴퓨터 시스템이 무엇을 하느냐는 것이고

## Implementation (=Organization = Microarchitecture)

임플리멘테이션이라는것은 컴퓨터가 어떻게 처리하느냐,

구체적인 처리방식, 하드웨어의 로우레벨을 얘기합니다.

그래서 위에있는것(아키텍쳐)은 명령어 레지스터 메모리 입출력 등등등 이런것이 포함이 되고

이거(임플리먼테이션)은 그것보다 아래층에서 전자회로를 어떻게 만드느냐

어떤 반도체 소자를 쓰느냐 그것이 되지요.

우리가 잘 아는 펜티엄, 인텔 코어 i5, i7이런 시리즈들을 본다면 

이거는 아키텍쳐로 본다면 한개입니다. IA-32 근데 구현은 여러개입니다.

구체적으로 들어가면(구현)은 달라지게 되는거죠.

# Abstraction Layers in Modern Systems

- Application
- Algorithm
- PL
- OS/VM
- ISA
- Microarchitecture
- Gates/Register-Transfer Level (RTL)
- Circuits
- Devices
- Physics

여러 개층이 있는데 제일 밑에 물리학,, 뭐 더 밑에 화학이 있죠.

그다음에 physics 그사이에 전자가 어떻게 움직이고... 전류가 흐르고 하는것들. 

그것을 이용해서 device를 만들면 반도체 IO들, 뭐 트랜지스터그런게 되죠.

그 만들어진 디바이스들을 이용해서 어떻게 만드느냐 에따라서 기능이 달라지죠 그것들이 전자회로

여기까지 우리는 배우지 않습니다. 전자공학과에서 배우죠.

그 위에서 게이트, ... 그위에 마이크로 아키텍쳐, 그리고 아키텍쳐.

그다음부터는 소프트웨어죠.

이 소프트웨어와 하드웨어의 경계선에 있는것이 아키텍쳐다 이렇게 얘기를 합니다.

# 1.1 Introduction

대충 넘김

# Five Classic Components

프로세서, 메모리, 입력, 출력

프로세서는 다시 나눠서 Control, Datapath

이렇게 5개의 구성요소가 있다.

컴퓨터가 프로그램을 실행하려면 메모리에 있는 명령어를 컨트롤로 가져와서 

컨트롤에서 그 명령어를 해독하고

거기에 따라서 컴퓨터의 다른부분이 뭐를할지 지시를 합니다. 그래서 컨트롤이라 하죠

예전에 컨트롤 유닛이라고 했는데 그냥 요즘은 컨트롤이라고 합니다.

그래서 그 명령어를 실행하고

그 실행하는 과정에서 데이터패스 이 안에 alu가 있고요...

이런 다른 장치들이 명령어 실행에 참여를 하게되지요.

명령어 실행이 끝나면 다음 명령어를 가져와서 보구요.

이 명령을 실행하려면 너는 뭐하고 너는 뭐하고 이걸 지시를 합니다.

또 이 명령을 실행을하면 또 다음 명령을 가져옵니다.

이것을 한없이 반복하는것이 프로세서입니다.

그것이... 나중에 다 설명을 할것이지만.

프로세서는 컨트롤과 데이터패스로 구성이 되고

컨트롤안에는 중요한것이 여러가지 있지만 그중에서 중요한 요소로

프로그램 카운터 pc라는것과 instruction decoder라는 것이 있습니다.

datapath에는 register와 alu라는것이 있고.

그리고 메모리에는 instruction(프로그램)이 있고, 데이터가 들어가있고.

그래서 프로그램 실행을 하려면 메모리에서 명령어를 읽어와야 합니다.

근데 이 메모리에 들어가있는 수많은 명령어중에서 어떤 명령어를 실행할 것인가를 알아야겠죠.

그 정보를 가지고있는데 이 Program Counter (PC) 입니다.

얘가 다음번에 실행할 명령어의 주소를 가지고 있습니다. (일종의 포인터)

그래서 이 PC가 메모리로 보내지면, 메모리에서 명령어를 읽어서 보내게됩니다.

그러면 여기서 Instruction Decoder에서 해독을 하게 됩니다.

해독을해서 그것을 읽어서 실행을 하려면 뭐를 해야하냐. 여기 각각 

ALU에 무슨 명령을 보낼 수도 있고, 레지스터에다가...

레지스터는 CPU프로세서 안에있는 조그만 기억장치입니다.

메모리에 모든 내용이 들어있고 그중에서 자주 사용하는것만 레지스터에 있다 생각하면됩니다. 나중에 다시 설명을 합니다.

여기 각 장치에 제어 신호를 보내서 그것을 실행하게 되지요.

어, 그래서 첫단계는 ... (메모장 켜서 타이핑 보여줌)

## 1. Instruction fetch

첫단계는. 메모리에서 Instruction을 읽어오는건데

Instruction fetch라고 하고, 앞으로도 많이 들을 내용입니다.

## 2. Instruction decode

그리고 두번째. 읽어온 명령어를 해독하고, 이게 무슨 명령어냐.

## 3. Instruction execution

그다음 세번째 해독해서 무슨 명령인지 알았으면 이것을 실행하고.

아,, execute하기 위해서는 control에서 여러가지 제어 신호를 보내서 하게되지요.

그리고 끝나면 다시 1번으로 돌아가고 이걸 반복하는겁니다.

근데 이 과정에서 다음명령어를 실행하기위해서 pc가 메모리로 보내져야겠죠.

근데 아까 그 주소가 그대로있으면 계속 그 명령어만 가져올테니까.

한번 할때마다 증가해야 겠지요.

그래야 다음 명령어를 가져올테니까.

그래서 한번할때마다 증가해야되니까 카운터라는 이름이 붙은겁니다.

근데 과거에는 명령어하나가 주소하나에 들어가고 그랬는데

나중에 보면 알겠지만, 지금은 명령어 길이가 하나씩 증가하는게아니라 4씩 증가합니다.

이건 MIPS의 경우. 물론, 펜티엄같은 경우 명령어 종류가 달라져요

암튼 꼭 1은 아니지만, 아무튼 이 값이 증가해서 다음 명령을 가르키게

이렇게 해놓습니다. 그래야 이 명령이 끝난다음에 다시 올라가서 새로운 명령을 가져오죠.

이걸 반복하는게 프로세서다.

(Five Classic Components 슬라이드로 돌아옴)

다섯개 장치를 봤구요. 그 위에는 컴파일러를 비롯해 OS등등이 있지요.

그래서 하드웨어와 소프트웨어 사이의 인터페이스, 그 인터페이스 역할을 하는게 명령어 입니다.

그래서 이게 돌아가는걸 보고 성능이 얼마가 되느냐, 성능평가를 하는게 되겠지요.

# Intel Pentium

(펜티엄 칩셋 그림보여줌)

이것은 인텔의 펜티엄 칩입니다. 나중에 다시와서 보겠습니다.

여기 Instruction Fetch, Instruction Decode, Brench Prediction Logic,

이런부분이 Control에 해당되는 부분이고,

Superscaler Integer execution 정수 실행하는 부분

복잡한 명령어 지원하는부분, 실수 처리하는부분 이런부분이 Datapath에 해당 되구요

이부분은 캐시메모리입니다. 나중에 보게 될거고.

이번학기 강의하는 도중에 여러번 다시와서 이걸 보게 될겁니다.

# AMD Barcelona Processor

이건(펜티엄) 싱글코어지요 요즘은 칩하나에 프로세서가 여러개 들어있습니다.

이거 하나가 아까본 펜티엄에 해당되는 프로세서고요. 

그런것들이 core1, core2, core3, core4 4개가 칩하나에 들어가있다.

# Apple A5 chip in iPad 2

이거는 애플 아이패드에서 사용하는 칩인데 ...

# 2^x vs 10^y

2의 10승은 1024이고 killo는 1000이고 2%만큼 차이가 있습니다.

이걸 구별하기 위해서 우리 책에서는 i를 넣었습니다. 

이런 i가 붙은 표시가 나오면 2의 몇승인거고 없으면 10의 승인거다 이렇게 보면 되겠습니다.

i가 안붙은건 SI prefix라고 하고 i가 붙은건 IEC prefix라고 합니다 (ISO/IEC 80000 standard)

보통 이런걸 잘 안쓰는데 우리책에서는 구분하기 위해서 나오니까 알아두길 바랍니다.

첫번째 강의는 여기서 마치겠습니다.
