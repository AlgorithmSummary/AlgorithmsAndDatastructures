# 깊이 우선 탐색 (DFS / Depth-First Search)

## 1. 유래/아이디어
- 한 경로를 **가능한 깊게** 진행하다가 더 갈 곳이 없으면 **백트래킹**으로 되돌아가는 탐색.
- 재귀 호출 또는 **명시적 스택**으로 구현 가능.

## 2. 사용되는 상황
- **사이클 탐지**, **위상 정렬**(DAG), **연결 성분** 파악.
- DFS 방문/완료 시각(`tin/tout`) 기반 **간선 분류**(tree/back/forward/cross).
- **단절점/단절선(bridge)**, **SCC(강한 연결 성분)**의 핵심 루틴.

## 3. 정의
### 3.1 문제 정의
- 입력: 정점 `V = {0..n-1}`, 간선 `E` (유향/무향), (선택) 시작 정점 `s` 또는 전체 정점 순회.
- 출력: 방문 순서, (선택) `tin/tout`, `parent`, 간선 분류, 위상 순서 등.

### 3.2 점화식 / 핵심 전개
- 방문 규칙(재귀):
  - `u` 방문 시작 → 모든 이웃 `v`에 대해
    - `v` 미방문이면 `parent[v]=u`로 재귀(트리 간선)
    - `v` 방문 중(재귀 스택 내)이면 **back edge** (유향 그래프 사이클 존재의 증거)
- 불변식:
  1) `tin[u] < tin[v] < tout[v] < tout[u]`이면 `v`는 `u`의 서브트리.  
  2) 유향 그래프에서 **back edge 존재 ⇔ 사이클 존재**.

### 3.3 의사코드
```text
// 0-based, adjacency list adj[0..n-1]
global time := 0
DFS(n, adj):
  create arrays visited[0..n-1]:=false, tin[0..n-1], tout[0..n-1], parent[0..n-1]:=-1
  for u in 0..n-1:
    if not visited[u]:
      dfs_visit(u)

dfs_visit(u):
  visited[u] := true
  tin[u] := ++time
  for v in adj[u]:
    if not visited[v]:
      parent[v] := u
      dfs_visit(v)           // tree edge (u→v)
    else:
      // 유향: v가 아직 완료 전(스택 내)이면 back edge (사이클)
      // 무향: v != parent[u]면 사이클의 증거 (중복 간선 주의)
      skip
  tout[u] := ++time

// 위상 정렬(DAG): 종료 시점 역순(큰 tout부터)으로 나열
```

## 4. 시간·공간 복잡도
- 시간: `O(n + m)` (정점/간선 각각 상수 횟수 방문)
- 공간: `O(n)` (visited/parent/tin/tout + 재귀 스택 또는 명시적 스택)
- 특수 케이스:
  - **위상 정렬**은 DAG에서만 가능(Back edge 발견 시 불가).
  - **무향 사이클 판정**: `v != parent[u]`인 이미 방문한 이웃 발견 시.
  - **대규모 입력**: 재귀 깊이 한계 → 반복형(스택) DFS 권장.

## 5. 구현 팁 & 실수 포인트
- **재귀 한도**: 큰 그래프에서 스택 오버플로 가능 → 반복 DFS 또는 언어별 재귀 한도 조정.
- 유향/무향에 따른 **간선 분류 조건**을 분명히 분기.
- 여러 컴포넌트가 있을 수 있으므로 **전체 정점 루프**에서 미방문 시작.
- 위상 정렬은 **완료 시각 역순**(또는 재귀 복귀 시 push, 마지막에 reverse).
- 무향 그래프에서 `parent` 체크 누락 시 **거짓 사이클** 판정 위험.

## 6. 예제 입력/출력 (선택)
- 유향 DAG: `n=6`, `E={0→1,0→2,1→3,2→3,3→4,4→5}`
- DFS(사전식 인접 순서 가정):
  - 가능한 위상 순서 예: `0,2,1,3,4,5` (구현/순서에 따라 다양)
  - `tin/tout`는 구현에 따라 달라지며, 서브트리 포함성은 `tin/tout`로 판정.

## 7. 참고/출처(선택)
- Cormen, T. H., Leiserson, C. E., Rivest, R. L., and Stein, C., *Introduction to Algorithms*, **4th ed.**, MIT Press, 2022. (개념·정당성은 본 문서에서 자체 서술로 재작성)

## To Be Continued
- **Topological Sort**: DFS 종료 시각 역순으로 DAG의 선형화.  
- **SCC (Kosaraju/Tarjan)**: 역그래프 + 두 번의 DFS 또는 low-link 기반 1-pass.  
- **Bridge/Articulation**: DFS의 `tin/low`를 이용한 단절선/단절점 탐지.  
- **Euler Tour/Tree Flattening**: `tin/tout`로 서브트리를 구간으로 표현, LCA/세그먼트와 결합.
