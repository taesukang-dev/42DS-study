#include "maxheap.h"

Heap*	createHeap(int maxElementCount)
{
	Heap	*temp;

	temp = calloc(1, sizeof(Heap));
	temp->pElement = calloc(maxElementCount, sizeof(HeapNode));
	return temp;
}

int insertMaxHeapNode(Heap* hList, HeapNode element) // 삽입
{
	int	i;

	if (isMaxHeapFull(hList))
		return (FALSE);
	i = hList->currentElementCount; // 현재 Node 개수 저장
	while ((i != 0) && element.key > hList->pElement[i / 2].key) // 만약 부모노드가 element 보다 크다면 반복문을 멈춘다.
	{
		hList->pElement[i] = hList->pElement[i / 2]; // 부모노드를 자식 노드로 내려준다.
		i = i / 2;
	}
	hList->pElement[i] = element; // 마지막으로 남는 자리에 element를 할당한다.
	hList->currentElementCount += 1;
	return TRUE;
}

HeapNode	popMaxHeapNode(Heap* hList) // root node 반환
{
	HeapNode	root, temp;
	int			i, parent, child;

	root = hList->pElement[0]; // Root node
	i = hList->currentElementCount;
	temp = hList->pElement[i - 1]; // 가장 마지막 노드
	hList->currentElementCount -= 1; // root 노드가 삭제되었으므로 한 개 뺀다.
	parent = 0; // Root
	child = 1; // child
	while(child <= hList->currentElementCount)
	{
		if((child < hList->currentElementCount) && hList->pElement[child].key < hList->pElement[child + 1].key) child += 1; // 만약 child + 1 이 더 크다면 부모는 child + 1이 될 수 있게 한다.
		if (temp.key >= hList->pElement[child].key) break; // temp가 더 크다면 부모에 Temp를 할당할 수 있게 한다.
		hList->pElement[parent] = hList->pElement[child]; // 자식을 부모로 올려준다.
		parent = child;
		child *= 2; // index 값을 다음 자식으로 변경한다.
	}
	hList->pElement[parent] = temp; // 남은 자리에 temp를 할당한다.
	return root;
}

void deleteMaxHeap(Heap* hList)
{
	free(hList->pElement);
	hList->pElement = NULL;
	free(hList);
	hList = NULL;
}

int isMaxHeapFull(Heap* hList)
{
	return (hList->currentElementCount == hList->maxElementCount);
}

int	getMaxHeapLength(Heap* hList)
{
	return (hList->currentElementCount);
}

int main()
{
	Heap	*temp = createHeap(10);
	HeapNode	buf;

	buf.key = 8;
	insertMaxHeapNode(temp, buf);
	buf.key = 10;
	insertMaxHeapNode(temp, buf);
	buf.key = 4;
	insertMaxHeapNode(temp, buf);
	buf.key = 2;
	insertMaxHeapNode(temp, buf);
	buf.key = 12;
	insertMaxHeapNode(temp, buf);
	buf.key = 6;
	insertMaxHeapNode(temp, buf);
	buf.key = 20;
	insertMaxHeapNode(temp, buf);
	// buf.key = 100;
	// insertMaxHeapNode(temp, buf);
	// buf.key = 100;
	// insertMaxHeapNode(temp, buf);
	// buf.key = 100;
	// insertMaxHeapNode(temp, buf);

	for(int i = temp->currentElementCount; i > 0; i--)
		printf("%d ", temp->pElement[i - 1].key);
	buf = popMaxHeapNode(temp);
	printf("\n%d\n", buf.key);
	for(int i = temp->currentElementCount; i > 0; i--)
		printf("%d ", temp->pElement[i - 1].key);
	return 0;
}