# 너비 우선 탐색 (BFS / Breadth-First Search)

## 1. 유래/아이디어
- 시작 정점에서 **간선 수가 적은 경로(레벨)**부터 차례로 확장하는 탐색. FIFO 큐(`queue`)를 사용해 `0, 1, 2, ...` 레벨 순서로 방문한다.
- 무가중치 그래프에서 **최단 거리(간선 수 기준)**를 보장한다.

## 2. 사용되는 상황
- 무가중치 또는 모든 간선 가중치가 동일한 그래프의 **최단 경로** 계산.
- **최소 단계/최소 이동 횟수**가 핵심인 문제(격자형 미로, 확산/전염 시뮬, 불/토마토 등).
- **이분 그래프 판정**(레벨의 짝/홀 기반 2-컬러링).
- **다중 시작점 전파**(multi-source)—여러 출발지에서 동시에 퍼짐.

## 3. 정의
### 3.1 문제 정의
- 입력: 정점 집합 `V = {0..n-1}`, 간선 집합 `E`, 시작 정점 `s`(또는 시작 정점들의 집합 `S`). (인덱스는 **0 기반**)
- 출력: 각 정점까지의 **최단 간선 수** `dist[v]`와 (선택) 경로 복원용 `parent[v]`.

### 3.2 점화식 / 핵심 전개
- 레벨 `k`에 속한 모든 정점 `u`의 이웃 `v`에 대해 `v`가 미방문이면 `dist[v] = dist[u] + 1`로 설정하고 레벨 `k+1`에 편성한다.
- 불변식: 
  1) 큐에서 빠지는 순간의 `dist[u]`는 최종 확정.  
  2) `dist`는 비감소 순으로 큐에 들어간다.

### 3.3 의사코드
```text
// 0-based, adjacency list adj[0..n-1]
BFS(n, adj, s):
  create array dist[0..n-1] := INF
  create array parent[0..n-1] := -1
  create array visited[0..n-1] := false
  create queue Q
  visited[s] := true; dist[s] := 0; Q.push(s)

  while Q not empty:
    u := Q.front(); Q.pop()
    for v in adj[u]:
      if not visited[v]:
        visited[v] := true         // 중복 enq 방지: push 직전에 표시
        dist[v] := dist[u] + 1
        parent[v] := u
        Q.push(v)

// Multi-source: 초기 for each s in S: visited[s]=true, dist[s]=0, Q.push(s)
```

## 4. 시간·공간 복잡도
- 시간: `O(n + m)` (각 정점·간선을 최대 1회 처리)
- 공간: `O(n)` (visited/dist/parent/큐)
- 특수 케이스:
  - **도달 불가**: `dist[v] == INF`.
  - **0/1 가중치**는 0-1 BFS(`deque`)로 `O(n + m)` 유지.
  - **양수 가중치 일반**은 Dijkstra 필요.

## 5. 구현 팁 & 실수 포인트
- 방문 체크는 **큐에 넣을 때**(`visited[v] = true`) 수행(중복 삽입 방지).
- 무향 그래프는 `a-b` 양방향을 모두 `adj`에 추가.
- 격자 BFS는 `(dx, dy)` 고정 배열과 **범위/장애물 체크**를 인접 처리 직전에 수행.
- 경로가 필요하면 `parent`를 반드시 기록하고, 목표 `t`에서 부모를 역추적 후 **뒤집기**.
- 이분 그래프 판정: `color[v] = dist[v] % 2`로 인접 색 동일 여부 검사.

## 6. 예제 입력/출력 (선택)
- 그래프(무향): `n=6`, `E = {(0,1),(0,2),(1,3),(2,3),(3,4),(4,5)}`
- `s=0`에서 BFS
- 기대 결과:
  - `dist = [0,1,1,2,3,4]`
  - 가능한 최단 경로 예: `0 → 1 → 3 → 4 → 5`

## 7. 참고/출처(선택)
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., and Stein, C., *Introduction to Algorithms*, **4th ed.**, MIT Press, 2022. (개념·정당성은 본 문서에서 자체 서술로 재작성)

## To Be Continued
- **0-1 BFS**: 가중치가 {0,1}인 경우의 최단 경로(덱 기반).  
- **Dijkstra**: 양의 가중치 일반 그래프 최단 경로(우선순위 큐).  
- **Tree BFS×2**: 트리 지름 계산(임의 정점에서 최장 거리 정점 A, 다시 A에서 최장 거리 B).  
- **Bipartite Check**: BFS 기반 2-컬러링의 충돌 검사로 불이분성 판정.
