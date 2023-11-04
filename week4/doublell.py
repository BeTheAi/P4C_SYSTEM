class Node: #연결리스트에 들어갈 객체(노드)정보 class 정의
  def __init__(self, data): #초기화
      self.data = data #노드속 값
      self.next = None #다음 노드를 가르킬 포인터
      self.prev = None #이전 노드를 가르킬 포인터

class doubleLL: #이중 연결리스트 클래스 정의
  length = 0 #리스트의 길이 변수
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

  def printfront(self): #head 에서 부터 출력
    nowNode = self.head  #탐색 노드 생성
    print("head <=> ", end="") 
    while nowNode:    #none이 아닐떄 까지 반복
      print(nowNode.data, end=" <=> ") # 노드 출력
      nowNode = nowNode.next #다음 노드로 이동
    print("tail")

  def printprev(self):  #tail에서 부터 출력
    nowNode = self.tail  # 탐색 노드 생
    print("tail <=> ", end="") 
    while nowNode:    #none이 아닐때 까지 반복
      print(nowNode.data, end=" <=> ") # 노드 출력
      nowNode = nowNode.prev # 이전 노드로 이동
    print("head")

  def getlength(self):
    return self.length  # 길이 반환

  def deletelastnode(self): # 가장 끝(tail)쪽 노드 삭제
    nowNode = self.tail #탐색 노드(tail에서시작)생성
    if self.length == 1: # 길이가 1인경우
      self.head = None # head와 tail none으로 변경
      self.tail = None
      self.length -= 1 #길이 줄이기
    else: 
      nowNode.prev.next = None  # 길이가 2인경우, 현재노드(가장 끝노드)의 앞 노드의 다음을 none으로 설정
      self.tail = nowNode.prev # tail이 현재 노드의 전노드로 설정
      self.length -= 1 # 길이 감소
    
      
#테스트 코드
print("연결리스트에 추가할 값의 수를 입력해주세요")
a = int(input())
doublelink = doubleLL()

for i in range(a):
  b = int(input())
  doublelink.addNode(b)

doublelink.printfront()
doublelink.printprev()
print("이중 연결리스트의 길이 :", doublelink.getlength())
doublelink.deletelastnode()
doublelink.printfront()
doublelink.printprev()
print("이중 연결리스트의 이 :", doublelink.getlength())
