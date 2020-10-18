ZumiGamma : 로스를 이용한 자율주행 응급차량 만들기
==================

## Overview

  ROBOLINK사의 zumi로봇([로보링크주소](https://github.com/leggedrobotics/darknet_ros))을 이용하여 ROS에 기반한 자율주행 로봇을 개발한다.
  
  **contributors:** 안하일, 홍성우, 김건기, 조정민

  zumi는 다음과같은 부품들로 구성이 되어있다.  

- Raspberrypi zero  
- Zumi board  
- pi cam  
- LCD  
- battery

### 세부 시나리오 설명

- line tracing을 통해 지정맵의 도로를 구별하여 주행한다.
- traffic sign 및 color를 인식하여 교통법규를 준수한다.
- 사람이나 차량 등 물체가 본 차량 앞에 존재시 멈춘다.
- 특정한 상황으로 인해 Emergency Mode를 작동시킬 수 있다.
  - 도로에서 주행을 하되, 앞에 차량이 있을시에 비켜서 갈 수 있다.
  - traffic sign을 무시하고 주행한다.

[![Video Label](http://img.youtube.com/vi/u1tr6ZiykoM/0.jpg)](https://youtu.be/u1tr6ZiykoM)
