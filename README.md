# basic-socket-programming-2024
:computer:IoT 개발자과정 소켓프로그래밍 리포지토리:globe_with_meridians:

## :white_check_mark:1일차
### 1. 네트워크 프로그래밍 이해
- 서버 소켓의 생성과정
    - 소켓 생성 : socket함수 호출
        - domain : 프로토콜 체계
        - type : 소켓 데이터 전송방식
        - protocol : 통신에 사용되는 프로토콜

    ```c
    #include <sys/socket.h>
    int socket(int domain, int type, int protocol);
    ```
    - IP주소와 포트번호 할당 : bind함수 호출
    
    ```c
    #include <sys/socket.h>
    int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
    ```
    - 연결요청 가능상태로 변경 : listen함수 호출

    ```c
    #include <sys/socket.h>
    int listen(int sockfd, int backlog);
    ```
    - 연결요청에 대한 수락 : accept함수 호출

    ```c
    #include <sys/socket.h>
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    ```
- 클라이언트 소켓의 생성과정
    - connect함수 호출

    ```c
    #include <sys/socket.h>
    int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
    ```

### 2. 리눅스기반 파일조작
- 리눅스에서의 소켓조작과 파일조작이 동일, 윈도우는 파일과 소켓을 구분지음
- 파일 디스크립터(File Descripter) : 운영체제가 만든 파일 또는 소켓의 지칭을 편히 하기 위해 부여된 숫자
    - 0 : 표준입력(Standard Input)
    - 1 : 표준출력(Standard Output)
    - 2 : 표준에러(Standard Error)
- 파일 열기
    - 데이터를 읽거나 쓰기 위해 파일을 여는 경우
        - path : 파일 이름 및 경로
        - flag : 파일 오픈모드
            - O_CREAT : 필요하면 파일 생성
            - O_TRUNC : 기존 데이터 전부 삭제
            - O_APPEND : 기존 데이터 보존하고, 뒤에 이어서 저장
            - O_RDONLY : 읽기 전용으로 파일 오픈
            - O_WRONLY: 쓰기 전용으로 파일 오픈
            - O_RDWR : 일기, 쓰기 겸용으로 파일 오픈

    ```c
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    int open(const char *path, int flag);
    ```
- 파일 닫기
    - 파일은 사용 후 반드시 닫아줘야 함
        - fd : 닫고자하는 파일 또는 소켓의 파일 디스크립터
    
    ```c
    #include <unistd.h>
    int close(int fd);
    ```
- 파일에 데이터 쓰기
    - write() : 파일에 데이터를 출력(전송)하는 함수
        - fd : 데이터 전송대상을 나타내는 파일 디스크립터
        - buf : 전송할 데이터가 저장된 버퍼의 주소값
        - nbytes : 전송할 데이터의 바이트 수
    
    ```c
    #include <unistd.h>    
    ssize_t write(int fd, const void * buf, size_t nbytes);
    ```
- 파일에 저장된 데이터 읽기
    - read() : 데이터를 입력(수신)하는 함수
    
    ```c
    #include <unistd.h>
    ssize_t read(int fd, void *buf, size_t nbytes);
    ```

### 3. 소켓의 프로토콜과 데이터 전송특성
- 프로토콜 : 컴퓨터 상호간의 대화에 필요한 통신규약
    - 예를들어, 두 사람이 전화를 통해 대화를 하기로 했다면 두 사람의 대화에 사용한 프로토콜은 전화임
- socket함수 매개변수 이해
    - 프로토콜 체계 : PF_INET(IPv4 인터넷 프로토콜 체계), 아직은 IPv4만 사용
    - 소켓의 타입 : 소켓의 데이터 전송방식
        - 연결지향형 소켓(SOCK_STREAM)
            - TCP 소켓 생성, 잃어버리면 안되는 데이터를 전송할 경우
            - 데이터 손실x, 전송 순서대로 데이터 수신, 전송되는 데이터 경계 존재x
        - 비연결지향형 소켓(SOCK_DGRAM)
            - UDP 소켓 생성, 잃어버려도 되는 데이터를 전송할 경우
            - 빠른 전송, 데이터 손실 우려, 한 번 전송할 때의 크기 제한, 전송되는 데이터 경계 존재
    - 하나의 프로토콜 체계 안에서 데이터 전송방식이 동일한 프로토콜이 둘 이상 존재하는 경우에 세번째 인자 사용(일반적으론 0)

### 4. 소켓에 할당되는 IP주소와 포트번호
- IP(Internet Protocol) : 인터넷상에서 데이터를 송수신할 목적으로 컴퓨터에게 부여하는 값
- 포트번호 : 프로그램상에서 생성되는 소켓을 구분하기 위해 소켓에 부여되는 번호, 실행되는 프로그램을 뜻함
    - 하나의 운영체제 내에서 동일한 포트번호 중복할당x
- IPv4 주소체계
    - 네트워크 주소와 호스트 주소로 나뉨
    - 주소의 형태에 따라 A,B,C,D,E 클래스로 분류
    [ipv4](https://raw.githubusercontent.com/guswlrla/basic-socket-programming-2024/main/images/ipv4_2.png)





빅 엔디안 -> 상위바이트의 값을 작은 번지수
리틀 엔디안 -> 상위바이트의 값을 큰 번지수

## :white_check_mark:2일차
INADDR_ANY-> 자동으로 서버가 갖고잇는 ip를 할당시켜줌

네트워크 4계층

TCP서버 함수호출 순서 외우기
소- 소켓생성
말- 소켓주소할당
리-연결요청 대기상태
아-연결허용
read/write-데이터송수신
close-연결종료

연결요청하는 서버소켓
연결요청이후 데이터주고받을수잇는 클라이언트 소켓

TCP 클라이언트 함수호출 순서
socket()
connect()
read()/write()
close()

## 3일차
udp는 데이터경계가 잇기에 보내는 수만큼 반복함 (sendto함수 통해서,,,)

도메인네임 ,dns서버

## 4일차
좀비프로세스 소멸
wait함수 사용
waitpid함수 사용
    signal함수
    sigaction함수

## 5일차
- send & recv 입출력 함수
윈도우 리눅스 차이x
send함수와 recv함수 마지막 매개변수에는 데이터 송수신시 옵션정보가 전달됨-> 종류들 정리
MSG_OOB : 긴급메시지 전송, 긴급메시지라는 표시만 줌, 속도가 빠르거나 경로가 빠른 건 아님~
urgent pointer는 긴급메시지의 다음번 위치를 가리킴
offset 개념
차트14 스루함
16-1 넘어감

## 6일차
멀티프로세스 -> fork 기억
멀티플렉싱? -> select 기억
멀티스레드 -> 멀티프로세스랑 멀티스레드랑 비슷한데 스레드가 자원을 덜 사용

17-2
변하는 순간->엣지타입(low에서 high는 라이징엣지, 반대는 폴링엣지)
변한 결과값(high, low) -> 레벨타입
쓰레드 개념

뮤텍스
세마포어


