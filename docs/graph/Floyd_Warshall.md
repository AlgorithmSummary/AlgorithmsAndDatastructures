<!DOCTYPE markdown>
# Floyd–Warshall 알고리즘

## 1. 유래
- **Robert Floyd**(1962)와 **Stephen Warshall**(1962)의 업적을 합쳐 이름 붙여진 알고리즘입니다.
  - Warshall은 원래 그래프의 **전이 폐쇄(transitive closure)** 를 구하는 알고리즘을 발표했고,
  - Floyd는 **모든 쌍 최단 경로(all-pairs shortest path)** 문제에 이를 확장했습니다.
- 때로는 **Roy–Floyd–Warshall 알고리즘** 이라고도 불리는데, 이는 C. S. Roy(1959)의 기여를 포함한 명칭입니다.

## 2. 사용되는 상황
1. **모든 쌍 최단 경로** 를 구해야 할 때
   - 유향 또는 무향 그래프에서,
   - 가중치가 양수·음수(단, 음수 사이클 없음)일 때
2. 그래프의 **임의 두 정점** 사이의 최단 거리 정보를 한 번에 구해야 할 때
3. **동적 프로그래밍** 연습용 예제로 자주 활용
4. 음수 간선이 있어도 잘 작동하므로 벨만–포드 알고리즘을 여러 번 돌리는 것보다 효율적일 때

## 3. 정의

### 3.1. 문제 정의
- 정점 집합 <code>V = {1, 2, …, n}</code>과 가중치 함수 <code>w(i, j)</code>가 정의된 간선들의 그래프가 주어질 때,
- 모든 쌍 <code>(i, j)</code>에 대해 최단 경로 길이 <code>d(i, j)</code>를 구합니다.

### 3.2. 점화식 (Dynamic Programming)
- 중간에 사용할 수 있는 정점 집합을 <code>{1, 2, …, k}</code>까지로 제한했을 때의 최단 거리를  
  <code>D<sup>(k)</sup>[i][j]</code>라 정의하면,  
  <br>
  <code>D<sup>(k)</sup>[i][j] = min( D<sup>(k-1)</sup>[i][j], D<sup>(k-1)</sup>[i][k] + D<sup>(k-1)</sup>[k][j] )</code>
- 초기 조건 (k=0)  
  <br>
  <code>
  D<sup>(0)</sup>[i][j] = 0
 if i = j  
    w(i, j)    if (i, j)∈E  
    &infin;    otherwise
  </code>

### 3.3. 의사코드 (Pseudocode)
```text
// n: 정점 개수
// dist[i][j]: i→j 직접 간선 가중치 (없으면 ∞), dist[i][i] = 0
for k = 1 to n:
    for i = 1 to n:
        for j = 1 to n:
            if dist[i][j] > dist[i][k] + dist[k][j]:
                dist[i][j] = dist[i][k] + dist[k][j]
```

## 4. 시간복잡도 계산

- 내부에 **세 번** 중첩된 for-loop가 등장:  
  <code>k = 1…n,    i = 1…n,    j = 1…n</code>
- 각 반복마다 상수 시간(덧셈·비교·대입)이 소요되므로  
  <br>
  <code>T(n) = n × n × n × O(1) = O(n<sup>3</sup>)</code>
- 따라서 **시간복잡도**는 **O(n³)** 입니다.

## 부가 정보

- **공간복잡도**:  
  기본적으로 n×n 크기의 행렬을 사용하므로 **O(n²)**
- **음수 사이클 탐지**:  
  최종 <code>dist[i][i] &lt; 0</code>인 경우, 음수 사이클이 존재함을 의미
- **변형**:  
  - 최단 경로뿐 아니라, 경로 복원 정보를 추가해 실제 경로도 출력 가능  
  - 전이 폐쇄(transitive closure)와 최단 경로를 동시에 처리하기도 함
