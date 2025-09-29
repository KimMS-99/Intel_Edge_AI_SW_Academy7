# 노드/토픽 확인과 속도 명령 퍼블리시

```bash
# ROS 마스터/파라미터 서버/통신 중계 시작 (가장 먼저 실행)
$ roscore 

# 현재 실행 중인 모든 ROS 노드 목록 확인
$ rosnode list

# 현재 존재하는 모든 ROS 토픽 목록 확인
$ rostopic list
```

```bash
# rosrun: 패키지 안의 실행 노드를 실행하는 명령
# turtlesim 패키지의 시뮬레이터 노드 실행 (파랑 화면 + 거북이)
$ rosrun turtlesim turtlesim_node

# 키보드(화살표)로 거북이를 조종하는 텔레옵 노드 실행
$ rosrun turtlesim turtle_teleop_key
```

```bash
# /turtle1/cmd_vel 토픽으로 퍼블리시되는 속도 명령(Twist 메시지) 내용 실시간 출력
$ rostopic echo /turtle1/cmd_vel

# /turtle1/pose 토픽으로 퍼블리시되는 거북이의 자세/위치(Pose) 실시간 출력
$ rostopic echo /turtle1/pose

# 모든 토픽을 자세히 표시(+ 각 토픽의 퍼블리셔/서브스크라이버 정보까지)
$ rostopic list -v
```

```bash
# 퍼블리셔 예시 1) 한 번만(-1) 속도 명령 퍼블리시
# geometry_msgs/Twist 형식: -- '[linear_x, y, z]' '[angular_x, y, z]'
# => x=0.5 m/s 전진, 회전 없음
$ rostopic pub -1 /turtle1/cmd_vel geometry_msgs/Twist -- '[0.5,0.0,0.0]' '[0.0,0.0,0.0]'
```

```bash
# 퍼블리셔 예시 2) 1Hz(-r 1)로 반복 퍼블리시
# => x=0.5 m/s 전진하면서 z=1.0 rad/s로 회전
$ rostopic pub  /turtle1/cmd_vel geometry_msgs/Twist -r 1 -- '[0.5,0.0,0.0]' '[0.0,0.0,1.0]'
```

```bash
# /turtle1/cmd_vel 토픽의 실제 퍼블리시 주기(Hz) 측정
# 출력 예: average rate: 1.000  => 1Hz로 잘 퍼블리시 중
$ rostopic hz /turtle1/cmd_vel
```

터틀봇 3 

```bash
# (터틀봇3 실기 적용) 로봇 구동 기본 토픽은 /cmd_vel
# 예시 1) 한 번만 속도 명령 퍼블리시: x=0.05 m/s 전진, z=1.0 rad/s 회전
$ rostopic pub -1 /cmd_vel geometry_msgs/Twist -- '[0.05,0.0,0.0]' '[0.0,0.0,1.0]'

# 예시 2) 1Hz로 반복 퍼블리시: x=0.1 m/s 전진, z=0.5 rad/s 회전
$ rostopic pub /cmd_vel geometry_msgs/Twist -r 1 -- '[0.1,0.0,0.0]' '[0.0,0.0,0.5]'
```

```bash
# 터틀봇 목적지 좌표값 출력
$ roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/map.yaml

# 네비게이센 실행
$ rostopic echo /move_base/goal
```