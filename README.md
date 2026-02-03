# ROS2 RL-Vision-LLM 프로젝트

이 저장소는 **C/C++**로 구현된 ROS2 기반 프로젝트로, **강화학습(Reinforcement Learning)**, **비전 AI(Computer Vision)**, 그리고 **대형 언어 모델(LLM)** 인터페이스를 통합한 예제입니다.

## 프로젝트 개요

이 프로젝트는 ROS2 프레임워크에서 세 가지 최신 AI 기술을 결합합니다:

- **강화학습(RL)**: 자율 의사결정을 위한 Q-러닝 기반 에이전트
- **비전 AI**: 객체 검출, 특징 추출 및 추적을 위한 컴퓨터 비전 모듈
- **LLM 인터페이스**: 명령 해석 및 텍스트 생성을 위한 자연어 처리

## 아키텍처

### 구성 요소

1. **강화학습 모듈** (`reinforcement_learning.cpp`)
   - Q-러닝 구현
   - 상태-행동 가치 추정
   - 탐험-활용(ε-greedy) 전략을 통한 정책 최적화

2. **비전 AI 모듈** (`vision_ai.cpp`)
   - 객체 검출
   - 이미지로부터 특징 추출
   - 객체 추적 기능

3. **LLM 인터페이스 모듈** (`llm_interface.cpp`)
   - 자연어 명령 처리
   - 텍스트 생성 및 임베딩
   - 상태 특징으로부터 동작 해석

4. **메인 노드** (`main.cpp`)
   - 세 모듈 통합
   - 퍼블리셔/서브스크라이버를 포함한 ROS2 노드
   - 실시간 처리 루프

## 빌드 방법

### 사전 요구사항

- ROS2 (Humble, Iron 또는 Rolling 권장)
- C++17 호환 컴파일러
- CMake 3.8 이상

### 빌드 안내

```bash
# ROS2 환경 설정 (배포판 이름으로 교체)
source /opt/ros/<ros2-distro>/setup.bash

# 패키지 빌드
colcon build --packages-select ros2_rl_vision_llm

# 워크스페이스 환경 설정
source install/setup.bash
```

> 참고: Windows 환경에서는 PowerShell 스크립트나 ROS2 Windows 설치 지침을 따르세요.

## 노드 실행

### 기본 실행

```bash
# 메인 노드 실행
ros2 run ros2_rl_vision_llm rl_vision_llm_node
```

### Launch 파일 사용

```bash
# Launch 파일로 실행 (권장)
ros2 launch ros2_rl_vision_llm rl_vision_llm.launch.py

# 로그 레벨 변경
ros2 launch ros2_rl_vision_llm rl_vision_llm.launch.py log_level:=debug
```

## 토픽(Topics)

### 구독(Subscribe) 토픽

- `/camera/image_raw` (sensor_msgs/Image): 비전 처리용 카메라 입력
- `/voice_command` (std_msgs/String): 자연어 명령 입력

### 발행(Publish) 토픽

- `/cmd_vel` (geometry_msgs/Twist): 로봇 제어를 위한 속도 명령
- `/system_status` (std_msgs/String): 시스템 상태 업데이트

## 사용 예시

### 명령 전송

```bash
# 음성(텍스트) 명령 전송
ros2 topic pub /voice_command std_msgs/String "data: 'move forward'"

# 정지 명령 전송
ros2 topic pub /voice_command std_msgs/String "data: 'stop'"
```

### 상태 모니터링

```bash
# 시스템 상태 확인
ros2 topic echo /system_status

# 속도 명령 확인
ros2 topic echo /cmd_vel
```

## 구현 상세

### 강화학습
- Q-러닝 알고리즘을 사용하여 의사결정 수행
- 상태-행동 값(Q-table) 유지
- ε-greedy 탐험 전략 구현

### 비전 AI
- 카메라 이미지를 처리하여 객체 검출 수행
- RL 에이전트를 위한 고차원 특징 추출
- 객체 추적 기능 제공

### LLM 인터페이스
- 자연어 명령을 처리
- 의미적 이해를 위한 텍스트 임베딩 생성
- 상태 특징을 바탕으로 로봇 동작 해석

## 개발 구조

```
ros2_rl_vision_llm/
├── CMakeLists.txt
├── package.xml
├── include/
│   └── ros2_rl_vision_llm/
│       ├── reinforcement_learning.hpp
│       ├── vision_ai.hpp
│       └── llm_interface.hpp
└── src/
    ├── main.cpp
    ├── reinforcement_learning.cpp
    ├── vision_ai.cpp
    └── llm_interface.cpp
```

## 라이선스

Apache License 2.0

## 향후 개선 사항

- TensorFlow 또는 PyTorch 같은 딥러닝 프레임워크 통합
- 고성능 객체 검출 모델(YOLO, R-CNN 등) 적용
- Transformer 기반 LLM 통합
- 다중 에이전트 강화학습
- 실제 로봇 플랫폼과의 통합
