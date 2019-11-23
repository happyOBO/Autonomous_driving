<h1> Zumi Arduino

Zumi 구동을 제어하는 Arduino 이다.  Motor의 속력과 Buzzer, LED, IR 모두 제어가능하다.  현재  IR을 이용해 라인트레이서를 구현하였다. 



- 기본적인 함수 설명은 코드에 // 주석 표시로 설명을 적어 놓았다.

- 우리 Zumi 구성에 필요 없을 것 같은 함수 및 코드들은 /**/ 주석처리 하였다.

<h2> 코드 설명

> **void AutoTracking()** 

​	라인트레이서 구현 함수

> digitalWrite(IR_EMIT_PIN,HIGH);

​	IR값을 항상 읽어 들이기 위해 항상 IR_EMIT_PIN을 켜준다. 

>   digitalWrite(MUX_S0, LOW);
>   digitalWrite(MUX_S1, HIGH);
>   digitalWrite(MUX_S2, LOW);

​	RIGHT_IR 값을 받아들이기 위한 코드  //010 = 3

> s1 = analogRead(MUX_OUTPUT);

​	여기서 s1값은 RIGHT_IR의 value 

>   s1 = map(s1, 45, 850, 0, 100);

​	s1값을 0~100값 사이로 정규화 해준다. (45, 850값은 직접 max, min 함수를 통해 찾아낸 값)

​	s2값도 s1값처럼 반복 (s2=LEFT_IR=100=4)

>  normal = s1*(-1) + s2;
>
>  setMotorsToSpeed(50-normal,50+normal); 

​	Motors의 기본 속도를 50으로 두고 (모터의 바퀴를 굴리기 위한 최소한의 값)  Zumi의 회전을 

​	위한 Normal 값을 왼쪽 오른쪽 모터 기본속도에 빼주고 더해준다.



<h2> 추가 구현

컴퓨터에서 보내는 Value값을 통해 Zumi Arduino의 State를 결정하기 위하여  ROS를 통한 Value값을 받아들이 기위해 ROS통신 Node를 개발하며 동시에 상황에 따른 기능(Stop, Start,left turn,Right turn)들을 추가적으로 구현 할 것이다.  

 
