
#include "index.h"
#include <stdio.h>

/**
 * ������4�������ľ���
 */
struct Rect rects[] = {
	{0, 0, 2, 2},		// xmin, ymin, xmax, ymax (for 2 dimensional RTree)
	{5, 5, 7, 7},
	{8, 5, 9, 6},
	{7, 1, 9, 2},
};

/**
 * ��ȡ���εĸ���
 */
int nrects = sizeof(rects) / sizeof(rects[0]);	

/**
 * �������������Σ���Ҫ������������������е����е��Ӽ�
 */
struct Rect search_rect = {
	{6, 6, 10, 6},
};

/**
 * �Լ�����Ļص�����
 */
int MySearchCallback(int id, void* arg) 
{
	printf("�ҵ�һ������ľ��Σ�id: %d\n", id-1);
	return 1;
}

/**
 * MAIN ����
 */
int main()
{
	struct Node* root = RTreeNewIndex();	/* �������ڵ� */
	int i, nhits;
	
	printf("���ݾ��εĸ��� = %d\n", nrects);
	
	for(i=0; i<nrects; i++)
	{
		/**
		 * �ֱ����е��Ӿ��ζ����룬�����γ�R��
		 *
		 * ���������ݾ��� + ÿ�����η���һ��id + root + level��ʼ������0 
		 */
		RTreeInsertRect(&rects[i], i+1, &root, 0);
	}

	/**
	 * ���濪ʼsearchһ������( ��Ȼһ����Ҳ�У�����:(1,1,1,1)��һ������ľ��� )
	 *
	 * ע�������root��ע���������յ�root������Ľ���R��֮����ڵ�root��
	 *           search_rect����������
	 *           MySearchCallback���ص�����
	 *           ���Ӳ��� = 0
	 */
	nhits = RTreeSearch(root, &search_rect, MySearchCallback, 0);
	
	printf("�ҵ� %d ����������ݾ��Σ�\n", nhits);

	return 0;
}