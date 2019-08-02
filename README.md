# arp_spoof

## ARP(Address Resolution Protocol)
arp는 3계층 프로토콜로써 IP주소를 인접한 장치간의 통신을 위한 주소인 Mac Address와 대응시키기 위한 프로토콜이다.

arp 요청을 받으면 arp header에 자신의 맥주소를 채워 넣어
패킷을 보낸곳으로 다시 보낸다.
패킷을 보낸쪽과 받은쪽 모두 arp header에 있는 내용을 바탕으로 arp table을 만들어
다음 통신에 사용하게 된다.

### arp header
arp의 헤더에는 다음과 같은 정보들이 들어간다.

| 필드 | 크기 | 비고 |
|:---:|:---:|:---:|
| Hardware Type | 16bit | 이더넷은 1 |
| Protocol Type | 16bit | IP는 0x0800 |
| Hardware Length | 8bit | mac주소의 길이는 6byte |
| Protocol Length | 8bit | Ip주소의 길이는 4byte |
| Opcode | 16bit | 아래의 설명 참고 |
| Sender Mac | 48bit | 보내는 장치의 Mac주소 |
| Sender IP | 32bit | 보내는 장치의 IP주소 |
| Target Mac | 48bit | 받는 장치의 Mac주소(요청때는 0으로 비워둔다) |
| Target IP | 32bit | 받는 장치의 IP주소 |

opcode는 다음과 같이 있다.

- 0x0001 (arp request) : 맥주소를 알려줄 것을 요청한다. Who has (IP)?
- 0x0002 (arp reply) : 맥주소를 패킷에 담아 보낸다. (IP) is at (MAC).
- 0x0003 (rarp request) : 아이피를 알려줄 것을 요청한다. Who has (MAC)?
- 0x0004 (rarp reply) : 아이피를 패킷에 담아 보낸다. (MAC) is at (IP)

여기서 한가지 의문이 있다. Ethernet header에도 source와 destination이 있는데 굳이 arp에도 
sender mac과 target mac이 있어야할까?  

Ethernet header에 있는 mac address는 통신을 위한 정보이다.  
즉 arp table을 갱신하기 위한 정보가 아니다.  
소포를 예로 들면 보내는 사람과 받는 사람이 적힌 종이일 뿐인 것이다.  
실제로 arp table을 갱신하기 위한 정보는 arp라는 소포안에 들어있는 것이다.  

### arp spoofing 
arp를 통해 각 장치들은 어떤 장치가 어떤 ip를 가지고 있는지 알 수 있으며
이를 통해 만들어진 arp table을 이용해 통신을 하게 된다.  
하지만 arp에 거짓된 정보가 들어있다면 어떻게 될까?  
arp table은 arp를 통해 갱신되기 때문에 거짓된 정보가 arp에 들어있다 하더라도 arp table은 갱신된다.  
이러한 arp의 약점을 이용한 공격이 바로 arp spoofing이다.  

arp spoofing은 특정한 사용자의 장치에 게이트웨이의 arp table을 해커의 컴퓨터의 mac주소로 오염시키는 것으로 
이렇게 되면 사용자의 장치를 게이트웨이라고 착각하여 해커의 컴퓨터로 패킷을 보내게 된다.  
해커는 게이트웨이와 피해자의 장치 사이에서 패킷을 보고 변조할 수 있게 된다. (MITM공격)

arp table을 오염시키는 방법은 간단하다.  
arp header 에 sender ip 필드에 게이트웨이의 아이피를 넣고 sender mac에 자신의 컴퓨터의 맥주소를 적는다.  
target mac과 target ip는 오염시킬 장비의 주소를 적고 유니캐스트로 패킷을 3초마다 보내면 된다.  