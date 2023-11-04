class Node: #연결리스트에 들어갈 객체(노드)정보 class 정의
  def __init__(self, data): #초기화
      self.data = data #노드속 값
      self.next = None #다음 노드를 가르킬 포인터
      self.prev = None #이전 노드를 가르킬 포인터

class doubleLL: #이중 연결리스트 클래스 정의
  length = 0
  def __init__(self): #초기화
      self.head = None #헤드 포인터 설정
      self.tail = None #테일 포인터 설정

  def addNode(self, data): #값 추가
      newNode = Node(data) #추가할 노드에 값(data) 넣기
      if self.head == None: #헤드가 비어있을 경우
          self.head = newNode
          self.tail = newNode
          self.length += 1
      else:
          nowNode = self.head  #끝을 위한 탬색 노드 생성
          while nowNode.next: #탐색노드를 리스트의 끝까지 이동
              nowNode = nowNode.next # 다음 노드로 이동
          nowNode.next = newNode # 현재노드(가장 끝노드)의 다음으로 newnode 연결
          newNode.prev = nowNode #newnode의 앞노드로 nownode 지정
          self.tail = newNode # newnode를 테일로 업데이트
          self.length += 1

  def printfront(self):
    nowNode = self.head
    print("head <=>", end="")
    while nowNode:
      print(nowNode.data, end=" <=> ")
      nowNode = nowNode.next
    print("tail")
    
  def printprev(self):
    nowNode = self.tail
    print("tail <=>", end="")
    while nowNode:
      print(nowNode.data, end=" <=> ")
      nowNode = nowNode.prev
    print("head")

  def getlength(self):
    return self.length

print("연결리스트에 추가할 값의 수를 입력해주세요")
a = int(input())
doublelink = doubleLL()

for i in range(a):
  b = int(input())
  doublelink.addNode(b)

doublelink.printfront()
doublelink.printprev()
print("이중 연결리스트의 길이 :", doublelink.getlength())
